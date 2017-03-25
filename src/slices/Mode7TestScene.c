#include "snes.h"

#include "scenes.h"
#include "res.h"

static enum SCENE_STATE state = SCENE_STATE_INIT;


#define LOAD_RESOURCE2(name, bank) { \
	initDMATransfer(); \
	{ CGADD = 0x00; VMADD = 0x0000; \
		addDMAChannel(0, 0x18, bank, (short)&res_pic_##name, 12224, DMA_MODE_); \
		addDMAChannel(1, 0x22, bank, (short)&res_clr_##name, 512, DMA_MODE_BYTE_TWICE); \
	} startDMATransfer(); \
	initDMATransfer(); \
	{ VMADD = 0x4000; \
		addDMAChannel(2, 0x18, 0x42, (short)&res_map_##name, 16384, DMA_MODE_SHORT); \
	} startDMATransfer(); \
}

static void init(void* param) {

	int i = 0;
	char A, A1;

	VMAINC = 0x80;


	initDMATransfer();
	{ VMADD = 0x0000;
		addDMAChannel(0, 0x19, 0x43, (short)&res_pic_startup7, 9216, DMA_MODE_BYTE);
	} startDMATransfer();

	initDMATransfer();
	{ CGADD = 0x00;
		addDMAChannel(1, 0x22, 0x43, (short)&res_clr_startup7, 256, DMA_MODE_BYTE_TWICE);
	} startDMATransfer();

	//VMAINC = 0x00;
	initDMATransfer();
	{ VMADD = 0x0000;
		addDMAChannel(2, 0x18, 0x43, (short)&res_map_startup7, 16384, DMA_MODE_BYTE);
	} startDMATransfer();


	//VMAINC = 0x00;

	OBJSEL = 0xA2;

	// move all sprites off screen
	OBJADDR = 0x100;
	for(; i < 32 ; ++i) {
		OBJDATA = 0xFF;
	}

	for(i = 0; i < 128 ; i++) {
		oam_table_A[i].x = 0x20; // off screen enough.
		oam_table_A[i].y = i;
		oam_table_A[i].tile = 0;
		oam_table_A[i].attr = 0;
	}

	// base -> X: 256, Y: 110
	i = 0;

	// next
	oam_table_A[0].x = 224 - ((&sin_table_s)[(i + 64) % 256] / 2);
	oam_table_A[0].y = 80 - (&sin_table_s)[(i + 0) % 256] / 2;
	oam_table_A[0].tile = 0x00;
	oam_table_A[0].attr = 0x30;

	oam_table_A[1].x = 224 - (&sin_table_s)[(i + 96) % 256] / 2;
	oam_table_A[1].y = 80 - (&sin_table_s)[(i + 32) % 256] / 2;
	oam_table_A[1].tile = 0x08;
	oam_table_A[1].attr = 0x32;

	oam_table_A[2].x = 224 - (&sin_table_s)[(i + 128) % 256] / 2;
	oam_table_A[2].y = 80 - (&sin_table_s)[(i + 64) % 256] / 2;
	oam_table_A[2].tile = 0x80;
	oam_table_A[2].attr = 0x34;

	oam_table_A[3].x = 224 - (&sin_table_s)[(i + 160) % 256] / 2;
	oam_table_A[3].y = 80 - (&sin_table_s)[(i + 96) % 256] / 2;
	oam_table_A[3].tile = 0x88;
	oam_table_A[3].attr = 0x36;

	oam_table_A[4].x = 224 - (&sin_table_s)[(i + 192) % 256] / 2;
	oam_table_A[4].y = 80 - (&sin_table_s)[(i + 128) % 256] / 2;
	oam_table_A[4].tile = 0x00;
	oam_table_A[4].attr = 0x30;

	oam_table_A[5].x = 224 - (&sin_table_s)[(i + 224) % 256] / 2;
	oam_table_A[5].y = 80 - (&sin_table_s)[(i + 160) % 256] / 2;
	oam_table_A[5].tile = 0x08;
	oam_table_A[5].attr = 0x32;

	initDMATransfer();
	OBJADDR = 0x00;
	addDMAChannel(1, 0x04, 0, oam_table_A, 512, DMA_MODE_BYTE);
	startDMATransfer();

	OBJADDR = 0x100;
	OBJDATA = 0xAA;
	OBJDATA = 0xFE;

	LOAD_RESOURCE_SPRITE(test_join, 0x45, 0x80, 128, 0x4000, 8192);

	CGADD = 0x00;
	CGDATA = 0x22;
	CGDATA = 0x22;

//	VMAINC = 0x00;
//	initDMATransfer();
//	{ VMADD = 0x4000;
//		addDMAChannel(2, 0x18, 0x42, (short)&res_pic_head_gerade, 4096, DMA_MODE_SHORT);
//	} startDMATransfer();

//	initDMATransfer();
//	{ CGADD = 0x80;
//		addDMAChannel(1, 0x22, 0x42, (short)&res_clr_alpaca7, 32, DMA_MODE_BYTE_TWICE);
//	} startDMATransfer();
//
//	VMAINC = 0x00;
//	initDMATransfer();
//	{ VMADD = 0x5000;
//		addDMAChannel(2, 0x18, 0x47, (short)&res_pic_head_links, 4096, DMA_MODE_BYTE);
//	} startDMATransfer();
//
//	VMAINC = 0x00;
//	initDMATransfer();
//	{ VMADD = 0x6000;
//		addDMAChannel(2, 0x18, 0x47, (short)&res_pic_head_rechts, 4096, DMA_MODE_BYTE);
//	} startDMATransfer();


	BG1SC = 0x00;

	BG12NBA = 0x00;
	BG34NBA = 0x00;

	M7SEL = 0x00;

	CGSWSEL = 0x02;
	CGADSUB = 0x1;

	M7A = 0x80;
	M7A = 0x00;

	M7B = 0x00;
	M7B = 0x00;

	M7C = 0x00;
	M7C = 0x00;

	M7D = 0x80;
	M7D = 0x00;

	M7X = 0x80;
	M7X = 0x00;

	M7Y = 0x3F;
	M7Y = 0x00;


	//CGADD = 0x00;
	//CGDATA = 0x40;
	//CGDATA = 0x00;

	W12SEL = 0x00;
	WOBJSEL = 0x00;

	TWM = 0x0;

	BGMODE = 0x07;

	TM = 0x11;
	TS = 0x0;

	NMITIMEN = 0x81; // nmi

	W12SEL = 0x1;

	WH0 = 0;
	WH1 = 255;


	M7A = 0;
	M7A = 1;
	M7B = 0x01;
	A = MPYH;
	A1 = MPYM;

	//printsnes("B: ");
	//snes_print_short(((short)A << 8) | (short)A1);
	//printsnes(" ");

	//BG1H0FS = 10;

	//OBJSEL = 0x82;

/*		OBJADDRL = 0x0;
		OBJADDRH = 0x0;
		OBJDATA = 0x80;
		OBJDATA = 0x80;
		OBJDATA = 0x00;
		OBJDATA = 0x30;
		OBJDATA = 0x80;
		OBJDATA = 0x80;
		OBJDATA = 0x08;
		OBJDATA = 0x30;

		OBJADDRL = 0x00;
		OBJADDRH = 0x01;
		OBJDATA = 0xA;
		OBJDATA = 0x0;
*/
	state = SCENE_STATE_FADE_IN;
}

//char brightness  = 0;

static unsigned char a = 10, b = 0;
static void nmi(void* param) {
	signed char sin, cos;
	int sin_offset;
	int cos_offset;

	static int i = 0;

	char A, A1, B, B1;

	initDMATransfer();

	switch(state) {
		case SCENE_STATE_FADE_IN:
			setDisp(0xF);
			//if(brightness > 0xF)
			state = SCENE_STATE_RUNNING;
			printsnes("switch to RUNNING");
			break;
		case SCENE_STATE_RUNNING:
			//M7D = 1 + b++;
			//M7D = 0x00;//a++;


			calculateRotScale(a, 70, 30, 1, 0x100);
			a++;
			//a++;
			//M7A = 1 + a++;
			//M7A = 0x00;

			sin_offset = a;
			sin = (&sin_table_us)[sin_offset];
			cos = (&sin_table_us)[(sin_offset + 64) % 256];


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

			i = 205;

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


			break;
		case SCENE_STATE_FADE_OUT:
			//setDisp(brightness-- & 0xF);
			break;
		case SCENE_STATE_NOP:
		default:
			break;
	}

	OBJADDR = 0x00;
	addDMAChannel(7, 0x04, 0, oam_table_A, 512, DMA_MODE_BYTE);

	startDMATransfer();
}

static void run(void* param) {
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

static void irq(void* param) {

}

static void sync(void* param) {

}

typedef struct BasicTestSceneParams {
	int a;
	int b;
	int c;
} BasicTestSceneParams;

static BasicTestSceneParams params = {
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
	0,
};

Scene Mode7TestScene = {
	&funcs,
	&params,
	100,
	1000,
	1100,
	&state,
};


