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

static void initial_load() {

}

static short framebuffer[32 * 4];

setPixel(int x, int y, char r) {
	short base = 0x1000;

	short val = 0x0;

	int x1 = x / 16;
	int y1 = y / 16;

	int x2 = x % 16;
	int y2 = y % 16;

	int baseAddr = base + y1 * 32 + y2 + x1;

	VMADDL = baseAddr & 0xFF;
	VMADDH = baseAddr >> 8;

	val = framebuffer[baseAddr - 0x1000];
	val |= ((r & 0x1) << x2) | (((r & 0x2) >> 1) << 8 + x2);
	framebuffer[baseAddr - 0x1000] = val;
	VMDATAL = (val & 0xFF);
	VMDATAH = (val >> 8);

	baseAddr += 8;

	VMADDL = baseAddr & 0xFF;
	VMADDH = baseAddr >> 8;

	val = framebuffer[baseAddr - 0x1000];
	val |= ((r & 0x4) >> 2) << x2;
	framebuffer[baseAddr - 0x1000] = val;

	VMDATAL = (val & 0xFF);
	VMDATAH = (val >> 8);
}
//
//void evolve(void *u, int w, int h)
//{
//	unsigned (*univ)[w] = u;
//	unsigned new[h][w];
//
//	for_y for_x {
//		int n = 0;
//		for (int y1 = y - 1; y1 <= y + 1; y1++)
//			for (int x1 = x - 1; x1 <= x + 1; x1++)
//				if (univ[(y1 + h) % h][(x1 + w) % w])
//					n++;
//
//		if (univ[y][x]) n--;
//		new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
//	}
//	for_y for_x univ[y][x] = new[y][x];
//}
//
//void game(int w, int h)
//{
//	static unsigned univ[][w];
//	for_xy univ[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
//}

//	while (1) {
//		show(univ, w, h);
//		evolve(univ, w, h);
//		usleep(200000);
//	}
//}
//

static int init(enum SCENE_STATE state, void* param) {
	int i = 0;

	setPal(0, 0xFFFF);
	setDisp(0xF);

	BGMODE = 0x3;

	CGSWSEL = 0x1;

	TM = 0x1;

	BG12NBA = 0x1;
	BG1SC = 0x00;

	VMAINC = 0x80;

	for(; i < 32; i++) {
		VMADDL = i & 0xFF;
		VMADDH = i >> 8;
		printsnes(".");
		VMDATAL = i & 0xFF;
		VMDATAH = i >> 8;
	}

	printsnes("hellooooo\n");

	//VMDATA = 0xFFFF;
	//VMDATA = 0xFFFF;
	//VMDATA = 0xFFFF;

	return SCENE_STATE_FADE_IN;
}

static int nmi(enum SCENE_STATE state, void* param) {
	int r1;
	int r2;
	int r3;

	switch (state) {
	case SCENE_STATE_INIT:
		state = SCENE_STATE_FADE_IN;
	case SCENE_STATE_FADE_IN:

		r1 = random();
		r2 = random();
		r3 = random();

		setPixel(r1 % 8, r2 % 8, r3 & 0x7);

	case SCENE_STATE_RUNNING:
		break;
	case SCENE_STATE_FADE_OUT:
		break;
	case SCENE_STATE_NOP:
	default:
		break;
	}

	return state;
}

static int run(enum SCENE_STATE state, void* param) {
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

static int irq(enum SCENE_STATE state, void* param) {

}

static int sync(enum SCENE_STATE state, void* param) {

}

static int handle_key(enum SCENE_STATE state, void* param) {
	key_state *key = (key_state*) param;
}

typedef struct DemoViewParams {
	int a;
	int b;
	int c;
} DemoViewParams;

static DemoViewParams params = { 1, 2, 3, };

static Functions funcs = { init, nmi, run, irq, sync, handle_key, 0, };

Scene DemoView = { &funcs, &params, 70, 300, 350, };

