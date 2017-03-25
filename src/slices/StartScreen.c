#include "snes.h"

#include "scenes.h"
#include "res.h"

//static enum SCENE_STATE state = SCENE_STATE_INIT;

static volatile int exit_mode = 0;
static unsigned char brightness = 0;

static int a = 10, b = 0;

static int watch_dog = 0;


static char hdma_text_table[] = {
		0x7F, 0x13,
		0x1D, 0x13,
		0x38, 0x17,
		0x0F, 0x12,
		0x00,
};

static char blahdma_bg_table[] = {
		0x10, 0x00, 0x00, 0x5f, 0x53,
		0x10, 0x00, 0x00, 0x5f, 0x53,
		0x10, 0x00, 0x00, 0x3f, 0x4b,
		0x10, 0x00, 0x00, 0x1f, 0x47,
		0x10, 0x00, 0x00, 0xff, 0x3e,
		0x10, 0x00, 0x00, 0xdf, 0x36,
		0x10, 0x00, 0x00, 0xbf, 0x2e,
		0x10, 0x00, 0x00, 0x9f, 0x2a,
		0x10, 0x00, 0x00, 0x7f, 0x22,
		0x10, 0x00, 0x00, 0x5f, 0x1a,
		0x10, 0x00, 0x00, 0x5f, 0x16,
		0x10, 0x00, 0x00, 0x3f, 0x0e,
		0x10, 0x00, 0x00, 0x3f, 0x0e,
		0x10, 0x00, 0x00, 0x3f, 0x0e,
		0x10, 0x00, 0x00, 0x3f, 0x0e,
		0x10, 0x00, 0x00, 0x3f, 0x0e,
		0x00,
};

unsigned char hdma_bg_table[] = {
		0x10, 0x00, 0x00, 0x5f, 0x53,
				0x10, 0x00, 0x00, 0x5f, 0x53,
				0x10, 0x00, 0x00, 0x3f, 0x4b,
				0x10, 0x00, 0x00, 0x1f, 0x47,
				0x10, 0x00, 0x00, 0xff, 0x3e,
				0x10, 0x00, 0x00, 0xdf, 0x36,
				0x10, 0x00, 0x00, 0xbf, 0x2e,
				0x10, 0x00, 0x00, 0x9f, 0x2a,
				0x10, 0x00, 0x00, 0x7f, 0x22,
				0x10, 0x00, 0x00, 0x5f, 0x1a,
				0x10, 0x00, 0x00, 0x5f, 0x16,
				0x10, 0x00, 0x00, 0x3f, 0x0e,
				0x10, 0x00, 0x00, 0x3f, 0x0e,
				0x10, 0x00, 0x00, 0x3f, 0x0e,
				0x10, 0x00, 0x00, 0x3f, 0x0e,
				0x10, 0x00, 0x00, 0x3f, 0x0e,
				0x00,
};




#define LOAD_RESOURCE2(name, bank) { \
	initDMATransfer(); \
	{ CGADD = 0x00; VMADD = 0x0000; \
		addDMAChannel(0, 0x18, bank, (short)&res_pic_##name, 14400, DMA_MODE_); \
		addDMAChannel(1, 0x22, bank, (short)&res_clr_##name, 512, DMA_MODE_BYTE_TWICE); \
	} startDMATransfer(); \
	initDMATransfer(); \
	{ VMADD = 0x4000; \
		addDMAChannel(2, 0x18, 0x42, (short)&res_map_##name, 16384, DMA_MODE_SHORT); \
	} startDMATransfer(); \
}

static int init(enum SCENE_STATE state, void* param) {

	int i = 0;
	char A, A1;

	signed short sin, cos;
		int sin_offset;
		int cos_offset;

	VMAINC = 0x80;

	//printsnes("init startup scene\n");


	initDMATransfer();
	{ VMADD = 0x0000;
		addDMAChannel(3, 0x19, 0x43, (short)&res_pic_startup7, 14400, DMA_MODE_BYTE);
	} startDMATransfer();



	VMAINC = 0x00;
	initDMATransfer();
	{ VMADD = 0x0000;
		addDMAChannel(5, 0x18, 0x43, (short)&res_map_startup7, 16384, DMA_MODE_BYTE);
	} startDMATransfer();


	VMAINC = 0x80;


	CGADD = 0x00;
	CGDATA = 0x22;
	CGDATA = 0x22;


	BG1SC = 0x00;

	BG12NBA = 0x00;
	BG34NBA = 0x00;

	BGMODE = 0x07;

	TM = TM_BIT_BG1 | TM_BIT_OBJ;
	TS = 0x0;

	M7A = 0;
	M7A = 1;
	M7B = 0x01;
	A = MPYH;
	A1 = MPYM;

	sin_offset = a;
	sin = (&sin_table_s)[sin_offset % 256];
	cos = (&sin_table_us)[(sin_offset + 64) % 256];

	calculateRotScale(a, 128, 40, 512 + sin * 2, 512 + sin * 2);

	BG1V0FS = -60;
	BG1V0FS = 0xFF;
	BG1H0FS = 0;
	BG1H0FS = 0;

	exit_mode = 0;
	watch_dog = 0;

	state = SCENE_STATE_FADE_IN;
	return state;
}


static int nmi(enum SCENE_STATE state, void* param) {
	signed short sin, cos;
	int sin_offset;
	int cos_offset;

	static int i = 0;

	char A, A1, B, B1;

//	initDMATransfer();


	switch(state) {
		case SCENE_STATE_INIT:

			state = SCENE_STATE_FADE_IN;

		case SCENE_STATE_FADE_IN:

			brightness++;

			initDMATransfer();
			{ CGADD = 0x00;
				addDMAChannel(4, 0x22, 0x43, (short)&res_clr_startup7, 256, DMA_MODE_BYTE_TWICE);
			} startDMATransfer();

			MOSAIC = ~(brightness >> 2) << 4 | 0x1;
			//COLDATA = 0x20 | (brightness >> 2) & 0x1F;

			setDisp(brightness >> 2 & 0xF);
			if(brightness == 0x03F) {
				//printsnes("switch to RUNNING");
				return SCENE_STATE_RUNNING;
			}
		case SCENE_STATE_RUNNING:
			//M7D = 1 + b++;
			//M7D = 0x00;//a++;


			a++;
			//a++;
			//M7A = 1 + a++;
			//M7A = 0x00;

			sin_offset = a;
			sin = (&sin_table_s)[sin_offset % 256];
			cos = (&sin_table_us)[(sin_offset + 64) % 256];

			calculateRotScale(a, 128, 40, 512 + sin * 2, 512 + sin * 2);
			//calculateRotScale(a, 0, 0, a, a);


			// MPYL,M,H are multiply results
			// M7A,B,C,D matrix elements
			/*
			 * [ A, B ]   [ X ]
			 * [      ] * [   ]
			 * [ C, D ]   [ Y ]
			 *
			 */

			/*M7A = 0;
			M7A = 1;
			M7B = -sin;
			A = MPYH;
			A1 = MPYM;

			M7A = 0;
			M7A = 1;
			M7B = cos;
			B = MPYH;
			B1 = MPYM;
*/
	//		oam_table_A[0].x = sin;
	//		oam_table_A[0].y = cos;

	//		oam_table_A[1].x--;
//			oam_table_A[1].y += 2;

		//	oam_table_A[2].x--;
			//		oam_table_A[2].y += 2;

				//	oam_table_A[3].x--;
					//		oam_table_A[3].y += 2;

		/*	i = 205;

				// next
				oam_table_A[0].x = 224 - ((&sin_table_s)[(i + 64) % 256]);
				oam_table_A[0].y = 80 - (&sin_table_s)[(i + 0) % 256] / 2;
				oam_table_A[0].tile = 0x00;
				oam_table_A[0].attr = 0x30;

				oam_table_A[1].x = 224 - (&sin_table_s)[(i + 89) % 256];
				oam_table_A[1].y = 80 - (&sin_table_s)[(i + 25) % 256] / 2;
				oam_table_A[1].tile = 0x08;
				oam_table_A[1].attr = 0x32;

				oam_table_A[2].x = 224 - (&sin_table_s)[(i + 114) % 256];
				oam_table_A[2].y = 80 - (&sin_table_s)[(i + 50) % 256] / 2;
				oam_table_A[2].tile = 0x80;
				oam_table_A[2].attr = 0x34;

				oam_table_A[3].x = 224 - (&sin_table_s)[(i + 139) % 256];
				oam_table_A[3].y = 80 - (&sin_table_s)[(i + 75) % 256] / 2;
				oam_table_A[3].tile = 0x88;
				oam_table_A[3].attr = 0x36;

				oam_table_A[4].x = 224 - (&sin_table_s)[(i + 164) % 256];
				oam_table_A[4].y = 80 - (&sin_table_s)[(i + 100) % 256] / 2;
				oam_table_A[4].tile = 0x00;
				oam_table_A[4].attr = 0x30;
	*/
			// FIXME: add watchdog
			watch_dog++;
			if(exit_mode || watch_dog > 3000) {
			//	printsnes("switch to FADE OUT");
				state = SCENE_STATE_FADE_OUT;
			}
			break;
		case SCENE_STATE_FADE_OUT:
			brightness--;

			MOSAIC = ~(brightness >> 2) << 4 | 0x1;
			//COLDATA = 0x20 | ~(brightness >> 2) & 0x1F;
			setDisp(brightness >> 2 & 0xF);
			if(brightness == 0) {
				clearAllDMA();

			//	printsnes("switch to EXHIBIT");
				state = SCENE_STATE_EXHIBIT_MODE;
				exit_mode = 0;
			}

			break;
		default:
			break;
	}

//	OBJADDR = 0x00;
//	addDMAChannel(7, 0x04, 0, oam_table_A, 512, DMA_MODE_BYTE);

//	startDMATransfer();


//	initHDMATransfer();
//	addHDMAChannel(2, 0x21, 0, hdma_bg_table, 8, DMA_MODE_SHORT_TWICE);
//	startHDMATransfer();

	initHDMATransfer();
	addHDMAChannel(2, 0x21, 0, hdma_bg_table, sizeof(hdma_bg_table), DMA_MODE_SHORT_TWICE);
	startHDMATransfer();

	return state;
}

static int run(enum SCENE_STATE state, void* param) {



	switch(state) {
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

static int handle_key(enum SCENE_STATE state, void* param) {
	key_state *key = (key_state*)param;

	if(key->val & 0x1000) {
		exit_mode = 1;
	} else {
		//printsnes("ignored\n");
	}
}

static int irq(enum SCENE_STATE state, void* param) {

}

static int sync(enum SCENE_STATE state, void* param) {

}

typedef struct StartScreenParams {
	int a;
	int b;
	int c;
} StartScreenParams;

static StartScreenParams params = {
	1,
	2,
	3,
};

static Functions funcs = {
	init,
	nmi,
	run,
	irq,
	sync,
	handle_key,
	0,
};

Scene StartScreen = {
	&funcs,
	&params,
	100,
	1000,
	1100,
	0,
};


