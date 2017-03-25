#include "snes.h"

#include "scenes.h"
#include "res.h"

extern unsigned frame_start;
extern unsigned int frame_count;

static unsigned short bgColor = 0x0;

static char *next;

extern unsigned short text_table[32][32];

static unsigned short cycle_pal[16];
static short current_exhibit = 0;
static int last_exhibit = 0;
static int update_exhibit = 0;

static char current_text_scroll = 0;
static char max_text_scroll = 0;

static int watch_dog = 0;

static char brightness = 0;
static volatile int exit_mode = 0;

static void print_bg(char* text, int col, int row) {
	char* c = text;
	int i = 0;
	for (; *c != '\0'; c++) {
		text_table[row][col++] = 1024 | *c - 32;
	}
}

static void load_text_bg(char* text) {
	char* c = text;
	int row = 0;
	int col = 0;
	int i = 0;
	for (; *c != '\0' && row < 32; c++) {
		if (*c == '^' || col == 32) {
			row++;
			col = 0;
		}

		if (*c != '^') {
			text_table[row][col++] = 4096 | *c - 32;
		}
	}

	max_text_scroll = (row > 8 ? row - 4 : 4) * 8;
}

static char* load_text_bg_line(char* text, char first) {
	char* c = text;
	char done = 0;
	char* tmp;

	static int row = 0;
	static int col = 0;

	if (first) {
		row = 0;
	}

	for (col = 0; col < 32; col++) {
		if (first == 2) {
			text_table[row][col] = 5120;
		} else if (done == 1) {
			text_table[row][col] = 5120;
		} else if (*c == '^') {
			tmp = ++c;
			text_table[row][col] = 5120;
			done = 1;
			max_text_scroll = (row + 1) > 8 ? (row + 1) - 4 : 4 * 8;
		} else if (*c == '\0') {
			return 0;
		} else {
			text_table[row][col] = 5120 | *c++ - 32;
		}
	}

	row++;

	return tmp;
}

static void clear_text_bg(void) {
	int i = 0;
	int j = 0;
	for (i = 0; i < 32; ++i) {
		for (j = 0; j < 32; ++j) {
			text_table[i][j] = 1024;
		}
	}
}

static char hdma_text_table[] = { 0x7F, 0x4, 0x12, 0x4, 0x3b, 0x0, 0x04, 0x4,
		0x00, };

static char hdma_bg_table[] = { 0x10, 0x00, 0x00, 0x5f, 0x53, 0x10, 0x00, 0x00,
		0x3f, 0x4b, 0x10, 0x00, 0x00, 0x1f, 0x47, 0x10, 0x00, 0x00, 0xff, 0x3e,
		0x10, 0x00, 0x00, 0xdf, 0x36, 0x10, 0x00, 0x00, 0xbf, 0x2e, 0x10, 0x00,
		0x00, 0x9f, 0x2a, 0x10, 0x00, 0x00, 0x7f, 0x22,
//		0x10, 0x00, 0x00, 0x5f, 0x1a,
		//	0x10, 0x00, 0x00, 0x5f, 0x16,
		//	0x10, 0x00, 0x00, 0x3f, 0x0e,
		//	0x10, 0x00, 0x00, 0x3f, 0x0e,
		0x80, 0x00, 0x00, 0x3f, 0x0e, 0x00, };
unsigned char Altair_8800_bg_table[] = { 0x10, 0x00, 0x00, 0x7e, 0x85, 0x10,
		0x00, 0x00, 0x7c, 0xe5, 0x10, 0x00, 0x00, 0x7c, 0xab, 0x10, 0x00, 0x00,
		0x7c, 0xb4, 0x10, 0x00, 0x00, 0x70, 0xbf, 0x10, 0x00, 0x00, 0x34, 0xbf,
		0x10, 0x00, 0x00, 0x15, 0x1f, 0x10, 0x00, 0x00, 0x15, 0xdf, 0x0E, 0x00,
		0x00, 0x16, 0x9f, 0x01, 0x00, 0x00, 0x00,
		0x00
//,0x10, 0x00, 0x00, 0x17, 0x3f
//,0x10, 0x00, 0x00, 0x17, 0xbf
//,0x10, 0x00, 0x00, 0x17, 0xf9
//,0x10, 0x00, 0x00, 0x17, 0xec
		, 0x40, 0x00, 0x00, 0x1f, 0x47, 0x01, 0x00, 0x00, 0x00, 0x00, 0x31,
		0x00, 0x00, 0x17, 0xbf, 0x0 };

static void initial_load() {

}

void loadExhibit(struct exhibit* new_exhibit) {
	initDMATransfer();

	VMADD = 0x0;
	CGADD = 0x0;

	BG1SC = new_exhibit->sc;

	//snes_print_short(new_exhibit->clr);
	addDMAChannel(5, 0x22, 0x44, new_exhibit->clr, 32, DMA_MODE_BYTE_TWICE);
	addDMAChannel(6, 0x18, new_exhibit->bank, new_exhibit->pic,
			new_exhibit->size, DMA_MODE_SHORT);

	startDMATransfer();

	LOAD_RESOURCE_RAW(text_table, 0, 0x7000, 32 * 32 * 2);

//	while(DMA_MAIN_CTRL);
	current_text_scroll = 0;
}

static int init(enum SCENE_STATE state, void* param) {
	int i = 0;

	brightness = 0;

	LOAD_RESOURCE_MAP(border, 0x4A, 0x6000, 0x1000, 0x7800, 2048);
	LOAD_RESOURCE_RAW(res_pic_font, 0x4A, 0x5000, 1536);

	BG1SC = 0x14;
	BG2SC = 0x78;
	BG3SC = 0x70;

	BG12NBA = 0x60;
	BG34NBA = 0xC5;

	W12SEL = 0x00;
	WOBJSEL = 0x00;

	TWM = 0;

	BG1H0FS = -40;
	BG1H0FS = 0xFF;

	BG1V0FS = 14;
	BG1V0FS = 0xFF;

	BG2H0FS = 0x - 1;
	BG2H0FS = 0xFF;

	BGMODE = 0x01;

	TM = TM_BIT_BG1 | TM_BIT_BG2 | TM_BIT_BG3;
	TS = 0;

	W12SEL = 0x0;
	W34SEL = 0x2;

	WH0 = 0;
	WH1 = 255;

	cycle_pal[0] = 0x0000;

	for (i = 0; i < 15; i++) {
		cycle_pal[i + 1] = ((short*) &res_clr_bg_pal_pet2001)[i];
	}


	CGADD = 0x31;
	CGDATA = 0x1F;
	CGDATA = 0xFF;

	clear_text_bg();
	load_text_bg(*((exhibits + current_exhibit)->text));
	update_exhibit = 0;

	loadExhibit(exhibits + current_exhibit);

	CGADD = 0x11;
	CGDATA = 0x00;
	CGDATA = 0x00;

	watch_dog = 0;

	return SCENE_STATE_FADE_IN;
}

static int nmi(enum SCENE_STATE state, void* param) {

	int arm_hdma = 0;
	int r;

	clearAllDMA();
	initDMATransfer();

	// update cycle pal
	CGADD = 0x20;
	addDMAChannel(3, 0x22, 0, cycle_pal, 32, DMA_MODE_BYTE_TWICE);
	startDMATransfer();

	switch (state) {
	case SCENE_STATE_INIT:
		INIDISP = INIDISP | 0x80;
		NMITIMEN = 0x01; // nmi disable

		loadExhibit(exhibits + current_exhibit);

		INIDISP = INIDISP & ~0x80;
		NMITIMEN = 0x81; // nmi enable

		state = SCENE_STATE_FADE_IN;
	case SCENE_STATE_FADE_IN:
		brightness++;

		MOSAIC = ~(brightness >> 2) << 4 | 0x1;
		COLDATA = 0x20 | (brightness >> 2) & 0x1F;

		setDisp(brightness >> 2 & 0xF);
		if (brightness == 0x03F) {
			state = SCENE_STATE_RUNNING;
		}

		exit_mode = 0;
	case SCENE_STATE_RUNNING:
		BG3V0FS = 0x6B + current_text_scroll;
		BG3V0FS = 0;
		BG3H0FS = 0x - 12;
		BG3H0FS = 0xFF;

		if (watch_dog++ == 3000) {
			current_exhibit++;
			r = random() % (NUM_OF_EXHIBITS + 1);
			if (r == 0) {
				exit_mode = 1;
			} else {
				current_exhibit = r - 1;
			}
		}

		if (current_exhibit != last_exhibit || exit_mode) {
			state = SCENE_STATE_FADE_OUT;
			update_exhibit = 1;
			watch_dog = 0;
			//clearAllDMA();
		}

		break;
	case SCENE_STATE_FADE_OUT:
		brightness--;

		MOSAIC = ~(brightness >> 2) << 4 | 0x1;
		setDisp(brightness >> 2 & 0xF);

		if (brightness == 0) {
			if (exit_mode) {
				state = SCENE_STATE_START_SCREEN;
			} else {
				state = SCENE_STATE_INIT;
			}
		}
		break;
	case SCENE_STATE_NOP:
	default:
		break;
	}

	last_exhibit = current_exhibit;

	initHDMATransfer();
	addHDMAChannel(4, 0x2E, 0, hdma_text_table, sizeof(hdma_text_table),
			DMA_MODE_BYTE);
	addHDMAChannel(2, 0x21, 0, Altair_8800_bg_table,
			sizeof(Altair_8800_bg_table), DMA_MODE_SHORT_TWICE);
	startHDMATransfer();

	return state;
}

static int run(enum SCENE_STATE state, void* param) {
	signed char sin, cos;
	int sin_offset;

	static int i = 0;

	int cos_offset;
	int j = 0;

	short tmp;

	if (frame_count % 10 == 0) {
		tmp = cycle_pal[15];
		for (j = 14; j > 0; j--) {
			cycle_pal[j + 1] = cycle_pal[j];
		}
		cycle_pal[1] = tmp;

		bgColor += 2;
	}

	switch (state) {
	case SCENE_STATE_FADE_IN:

		break;
	case SCENE_STATE_RUNNING:

		break;
	case SCENE_STATE_FADE_OUT:
		// FIXME: make this faster.
		if (update_exhibit && brightness < 40) {
			clear_text_bg();
			load_text_bg(*((exhibits + current_exhibit)->text));
			update_exhibit = 0;
		}

		break;
	case SCENE_STATE_NOP:
	default:
		break;
	}
}

static int irq(enum SCENE_STATE state, void* param) {

}

static int sync(enum SCENE_STATE state, void* param) {

}

static int handle_key(enum SCENE_STATE state, void* param) {
	key_state *key = (key_state*) param;

	watch_dog = 0;
	exit_mode = 0;

	if ((key->val & 0x0100) == 0x0100) {
		current_exhibit++;
		if (current_exhibit == NUM_OF_EXHIBITS) {
			current_exhibit = 0;
		}
	} else if ((key->val & 0x0200) == 0x0200) {
		current_exhibit--;
		if (current_exhibit < 0) {
			current_exhibit = NUM_OF_EXHIBITS - 1;
		}
	} else if ((key->val & 0x0400) == 0x0400) {
		if (current_text_scroll < max_text_scroll) {
			current_text_scroll++;
		}
	} else if ((key->val & 0x0800) == 0x0800) {
		if (current_text_scroll > 0) {
			current_text_scroll--;
		}
	} else if ((key->val & 0x2000) == 0x2000) {
		exit_mode = 1;
	} else {
	}
}

typedef struct ExhibitViewParams {
	int a;
	int b;
	int c;
} ExhibitViewParams;

static ExhibitViewParams params = { 1, 2, 3, };

static Functions funcs = { init, nmi, run, irq, sync, handle_key, 0, };

Scene ExhibitView = { &funcs, &params, 70, 300, 350, };

