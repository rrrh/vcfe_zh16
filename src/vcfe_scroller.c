/*
 * vcfe_scroller.c
 *
 *  Created on: 26 Oct 2016
 *      Author: hns
 */

#include <snes.h>
#include <res.h>

unsigned short text_table[32][32];

void vcfe_scroller_init(void) {
/*	int i;
	// clear the text buffer
	memset(text_table, 0x0, sizeof(text_table));

	//VMAINC = 0x80;

	initDMATransfer();
	CGADD = 0x80; VMADD = 0x4000; OBJADDR = 0x00;
	addDMAChannel(0, 0x22, 0x4A, &res_clr_logos, 32, DMA_MODE_BYTE_TWICE);
	addDMAChannel(1, 0x18, 0x4A, &res_pic_logos, 8192, DMA_MODE_SHORT);


	// Create a OAM entry

	for (i = 0; i < 128; i++) {
		oam_table_A[i].x = 0x20; // off screen enough.
		oam_table_A[i].y = 0x20;
		oam_table_A[i].tile = 0;
		oam_table_A[i].attr = 0;
	}

	// next
	oam_table_A[0].x = 0x8;
	oam_table_A[0].y = -0x2;
	oam_table_A[0].tile = 0x00;
	oam_table_A[0].attr = 0x30;

	oam_table_A[1].x = 0xB8;
	oam_table_A[1].y = 0xA8;
	oam_table_A[1].tile = 0x08;
	oam_table_A[1].attr = 0x32;

//	oam_table_A[2].x = 0x40;
//	oam_table_A[2].y = 0x40;
//	oam_table_A[2].tile = 0x200;
//	oam_table_A[2].attr = 0x32;

	for (i = 0; i < 16; i++) {
		oam_table_B[i] = 0xFFFF;
	}

	oam_table_B[0] = 0xFFFA;

	addDMAChannel(7, 0x04, 0, oam_table_A, 544, DMA_MODE_BYTE);
	startDMATransfer();

	OBJSEL = 0xA2;
	*/
}



