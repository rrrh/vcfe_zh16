#include "snes.h"

#include "scenes.h"
#include "res.h"

extern unsigned int frame_start;

static unsigned short bgColor = 0x0;

static enum SCENE_STATE state = SCENE_STATE_FADE_IN;

static unsigned short cycle_pal[16];

extern unsigned short text_table[32][32];

static void print_bg(char* text, int col, int row) {
	char* c = text;
	int i = 0;
	for (; *c != '\0'; c++) {
		text_table[row][col++] = *c - 32;
	}
}

static void init(void* param) {
	int i = 0;
	struct sprite_desc desc;

	printsnes("basicTestScene\n");

	LOAD_RESOURCE(001, 0x44, 0x0, 256, 0x0, 7904, 0xF000, 2048);
	LOAD_RESOURCE(border, 0x46, 0x10, 64, 0x6000, 0x1000, 0xD000, 2048);
	LOAD_RESOURCE_SPRITE(test_join, 0x45, 0x80, 128, 0x4000, 8192);
	LOAD_RESOURCE_RAW(res_pic_font, 0x46, 0x2000, 1536);
	//LOAD_RESOURCE_SPRITE(font, 0x46, 0x00, 16, 0x2000, 1536);
	/*        01234567890123456789012345678901 */
	print_bg("Jemand musste Josef K. ver-", 1, 5);
	print_bg("leumdet haben, denn ohne dass", 1, 6);
	print_bg("er etwas Boeses getan haette,", 1, 7);
	print_bg("wurde er eines Morgens ver-", 1, 8);
	print_bg("haftet. >>Wie ein Hund!<< ", 1, 9);
	print_bg("sagte er, es war, als sollte", 1, 10);
	print_bg("die Scham ihn ueberleben. Als", 1, 11);
	print_bg("Gregor Samsa eines Morgens", 1, 12);
	print_bg("aus unruhigen Traeumen", 1, 13);
	print_bg("erwachte, fand er sich in", 1, 14);
	print_bg("Jemand musste Josef K. ver-", 1, 15);
	print_bg("leumdet haben, denn ohne dass", 1, 16);
	print_bg("er etwas Boeses getan haette,", 1, 17);
	print_bg("wurde er eines Morgens ver-", 1, 18);
	print_bg("haftet. >>Wie ein Hund!<< ", 1, 19);
	print_bg("sagte er, es war, als sollte", 1, 20);
	print_bg("die Scham ihn ueberleben. Als", 1, 21);
	print_bg("Gregor Samsa eines Morgens", 1, 22);
	print_bg("aus unruhigen Traeumen", 1, 23);
	print_bg("erwachte, fand er sich in", 1, 24);
	print_bg("leumdet haben, denn ohne dass", 1, 25);
	print_bg("er etwas Boeses getan haette,", 1, 26);
	print_bg("wurde er eines Morgens ver-", 1, 27);
	print_bg("haftet. >>Wie ein Hund!<< ", 1, 28);
	print_bg("sagte er, es war, als sollte", 1, 29);
	print_bg("die Scham ihn ueberleben. Als", 1, 30);
	print_bg("Gregor Samsa eines Morgens", 1, 31);

	LOAD_RESOURCE_RAW(text_table, 0, 0x2400, 32 * 32 * 2);

	for (i = 1; i < 15; i++) {
		cycle_pal[i] = ((short*)&res_clr_bg_pal)[i-1];
	}

	//initDMATransfer();
	//CGADD = 0x00;
	//addDMAChannel(1, 0x22, 0x41, (short)&res_clr_mac, 512, DMA_MODE_BYTE_TWICE);
	//startDMATransfer();

	BG1SC = 0xF0;
	BG2SC = 0xD0;
	BG3SC = 0x24;

	BG12NBA = 0x60;
	BG34NBA = 0xC2;

	CGSWSEL = 0x02;
	CGADSUB = 0x1;

	CGADD = 0x00;
	CGDATA = 0x00;
	CGDATA = 0x00;

	W12SEL = 0x00;
	WOBJSEL = 0x00;

	TWM = 0x7;

	BG1H0FS = -12;
	BG1H0FS = 0xFF;

	BG1V0FS = -32;
	BG1V0FS = 0xFF;

	BGMODE = 0x01;

	TM = TM_BIT_BG1 | TM_BIT_BG3 | TM_BIT_BG2 | TM_BIT_OBJ;
	TS = 0x00;

	NMITIMEN = 0x81; // nmi

	W12SEL = 0x3;

	OBJSEL = 0xA2;

	WH0 = 0;
	WH1 = 255;

	// move all sprites off screen
	OBJADDR = 0x100;
	for (i = 0; i < 32; ++i) {
		OBJDATA = 0xFF;
	}

	// Create a OAM entry

	for (i = 0; i < 128; i++) {
		oam_table_A[i].x = 0x20; // off screen enough.
		oam_table_A[i].y = i;
		oam_table_A[i].tile = 0;
		oam_table_A[i].attr = 0;
	}

	// next
	oam_table_A[0].x = 0xA0;
	oam_table_A[0].y = 0x40;
	oam_table_A[0].tile = 0x00;
	oam_table_A[0].attr = 0x30;

	oam_table_A[1].x = 0x10;
	oam_table_A[1].y = 0x20;
	oam_table_A[1].tile = 0x08;
	oam_table_A[1].attr = 0x32;

	initDMATransfer();
	OBJADDR = 0x00;
	addDMAChannel(1, 0x04, 0, oam_table_A, 512, DMA_MODE_BYTE);
	startDMATransfer();

	OBJADDR = 0x100;
	OBJDATA = 0xAA;
	OBJDATA = 0xFE;

	snes_state.scene_state = SCENE_STATE_FADE_IN;
}

char brightness = 0;

static void nmi(void* param) {

	frame_start = 1;

	initDMATransfer();

	switch (state) {
	case SCENE_STATE_FADE_IN:
		setDisp(brightness++ & 0xF);
		if (brightness > 0xF)
			state = SCENE_STATE_RUNNING;
		break;
	case SCENE_STATE_RUNNING:
		setPal(64, bgColor);
		BG3V0FS = bgColor >> 2;
		BG3V0FS = 0;

		// OBJADDR = 0x00;
		// OBJDATA = bgColor % 128;
		// OBJDATA = 0x40;

		//  MOSAIC = bgColor & 0xf0 | 0x1;

		//   WH0 = bgColor - 100;
		//  WH1 = bgColor;

		// i+= 2;

		// next

		// cycle palette

		CGADD = 0x10;
		addDMAChannel(5, 0x22, 0, cycle_pal, 32, DMA_MODE_BYTE_TWICE);

		break;
	case SCENE_STATE_FADE_OUT:
		//setDisp(brightness-- & 0xF);
		break;
	case SCENE_STATE_NOP:
	default:
		break;
	}

	// update obj ram

	OBJADDR = 0x00;
	addDMAChannel(7, 0x04, 0, oam_table_A, 512, DMA_MODE_BYTE);

	startDMATransfer();
}

static void run(void* param) {
	signed char sin, cos;
	int sin_offset;

	static int i = 0;

	int cos_offset;
	int j = 0;

	static int frame_count = 0;


	if (frame_start) {
		frame_count++;
		frame_start = 0;

		if(frame_count % 30) {
			for (j = 1; j < 15; j++) {
				cycle_pal[j] = cycle_pal[1 + ((j + 1) % 14)];
			}
		}

		bgColor += 2;
		setPal(0, bgColor);


		i += 2;


		oam_table_A[0].x = 224 - ((&sin_table_s)[(i + 64) % 256] / 3);
		oam_table_A[0].y = 80 - (&sin_table_s)[(i + 0) % 256] / 2;
		oam_table_A[0].tile = 0x00;
		oam_table_A[0].attr = 0x30;

		oam_table_A[1].x = 224 - (&sin_table_s)[(i + 89) % 256] / 3;
		oam_table_A[1].y = 80 - (&sin_table_s)[(i + 25) % 256] / 2;
		oam_table_A[1].tile = 0x08;
		oam_table_A[1].attr = 0x32;

		oam_table_A[2].x = 224 - (&sin_table_s)[(i + 114) % 256] / 3;
		oam_table_A[2].y = 80 - (&sin_table_s)[(i + 50) % 256] / 2;
		oam_table_A[2].tile = 0x80;
		oam_table_A[2].attr = 0x34;

		oam_table_A[3].x = 224 - (&sin_table_s)[(i + 139) % 256] / 3;
		oam_table_A[3].y = 80 - (&sin_table_s)[(i + 75) % 256] / 2;
		oam_table_A[3].tile = 0x88;
		oam_table_A[3].attr = 0x36;

		oam_table_A[4].x = 224 - (&sin_table_s)[(i + 164) % 256] / 3;
		oam_table_A[4].y = 80 - (&sin_table_s)[(i + 100) % 256] / 2;
		oam_table_A[4].tile = 0x00;
		oam_table_A[4].attr = 0x30;

		switch (state) {
			case SCENE_STATE_FADE_IN:

				break;
			case SCENE_STATE_RUNNING:

				break;
			case SCENE_STATE_FADE_OUT:

				break;
			case SCENE_STATE_NOP:
			default:
				break;
		}

	}
}

static void irq(void* param) {

}

static void sync(void* param) {

}

typedef struct BasicTestSceneParams {
	int a;
	int b;
	int c;
} BasicTestSceneParams;

static BasicTestSceneParams params = { 1, 2, 3, };

static Functions funcs = { init, nmi, run, irq, sync, 0, };

Scene basicTestScene = { &funcs, &params, 70, 300, 350, };

