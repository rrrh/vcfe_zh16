#ifndef __SNES_H__
#define __SNES_H__

#include "snes_regs.h"
#include "snes_funcs.h"
#include "snes_consts.h"

extern unsigned short oam_table_B[16];

struct oam_low_table {
	unsigned char x;
	unsigned char y;
	unsigned char tile;
	unsigned char attr;
};

struct oam_high_table {
	unsigned int xn0 	: 1;
	unsigned int p0		: 1;
	unsigned int xn1	: 1;
	unsigned int p1 	: 1;
	unsigned int xn2 	: 1;
	unsigned int p2 	: 1;
	unsigned int xn3 	: 1;
	unsigned int p3 	: 1;
};

#endif
