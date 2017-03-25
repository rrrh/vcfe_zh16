#ifndef __RES_H__
#define __RES_H__

extern unsigned short res_clr_8x8_4bpp_tile;
extern unsigned short res_pic_8x8_4bpp_tile;

extern unsigned short res_clr_128x8_4bpp_tile;
extern unsigned short res_pic_128x8_4bpp_tile;
extern unsigned short res_map_128x8_4bpp_tile;

extern unsigned short res_clr_128x8_2bpp_tile;
extern unsigned short res_pic_128x8_2bpp_tile;
extern unsigned short res_map_128x8_2bpp_tile;

extern unsigned short res_clr_128x8_4bpp_tile;
extern unsigned short res_pic_128x8_4bpp_tile;
extern unsigned short res_map_128x8_4bpp_tile;

extern unsigned short res_clr_128x8_8bpp_tile;
extern unsigned short res_pic_128x8_8bpp_tile;
extern unsigned short res_map_128x8_8bpp_tile;

extern unsigned short res_clr_digital_pdp8_256x96;
extern unsigned short res_pic_digital_pdp8_256x96;
extern unsigned short res_map_digital_pdp8_256x96;

extern unsigned short res_clr_font;
extern unsigned short res_pic_font;
extern unsigned short res_map_font;

extern unsigned short res_clr_test_screen;
extern unsigned short res_pic_test_screen;
extern unsigned short res_map_test_screen;

extern unsigned short res_clr_sprites;
extern unsigned short res_pic_sprites;

extern unsigned short res_clr_font_16x16_4bpp;
extern unsigned short res_pic_font_16x16_4bpp;

extern unsigned short res_clr_next_icon;
extern unsigned short res_clr_sz_next_icon;
extern unsigned short res_pic_next_icon;

extern unsigned short res_pic_test_join;
extern unsigned short res_clr_test_join;

extern unsigned char res_snd_code;

// computer pics large

extern unsigned short  res_clr_font;
extern unsigned short  res_pic_font;

extern unsigned short res_clr_001;
extern unsigned short res_pic_001;
extern unsigned short res_map_001;

extern unsigned short res_clr_mac;
extern unsigned short res_pic_mac;
extern unsigned short res_map_mac;

extern unsigned short res_clr_border;
extern unsigned short res_pic_border;
extern unsigned short res_map_border;

extern unsigned short res_clr_zero;
extern unsigned short res_clr_bg_pal;

extern unsigned short res_clr_bg_pal_pet2001;

extern unsigned short res_clr_startup7;
extern unsigned short res_pic_startup7;
extern unsigned short res_map_startup7;

extern unsigned short res_pic_pet2001;
extern unsigned short res_clr_pet2001;
extern unsigned short res_map_pet2001;

extern unsigned short res_pic_apple_macintosh;
extern unsigned short res_clr_apple_macintosh;
extern unsigned short res_map_apple_macintosh;

extern unsigned short res_pic_pet2001_label;
extern unsigned short res_clr_pet2001_label;

extern unsigned short res_clr_pet2001_border;

extern unsigned char  MAC_size;
extern unsigned char  MAC_sc_offset;
extern unsigned short  MAC_pic;
extern unsigned short  MAC_clr;
extern unsigned short  MAC_map;
extern unsigned char  PET2001_size;
extern unsigned char  PET2001_sc_offset;
extern unsigned short  PET2001_pic;
extern unsigned short  PET2001_clr;
extern unsigned short  PET2001_map;

extern unsigned short res_clr_logos;
extern unsigned short res_pic_logos;

extern signed char res_sin_table;

extern signed char sin_table_s;
extern unsigned char sin_table_us;

extern unsigned short text_table[32][32];

// vram are !word! addresses...
#define VRAM_CHAR_SLOT0		0x0000		// 0
#define VRAM_CHAR_SLOT1		0x1000		// 4k
#define VRAM_CHAR_SLOT2		0x2000		// 8k
#define VRAM_CHAR_SLOT3		0x3000		// 12k
#define VRAM_CHAR_SLOT4		0x4000		// 16k
#define VRAM_CHAR_SLOT5		0x5000		// 20k
#define VRAM_CHAR_SLOT6		0x6000		// 24k
#define VRAM_CHAR_SLOT7		0x7000		// 28k

#define VRAM_SC_SLOT0		0x0000		// 0
#define VRAM_SC_SLOT1		0x0400		// 1k
#define VRAM_SC_SLOT2		0x0800		// 2k
#define VRAM_SC_SLOT3		0x0C00		// 3k

typedef struct exhibit {
	char bank;
	char sc;
	short size;
	const short *pic;
	const short *map;
	const short *clr;
	char** text;
} exhibit;

extern struct exhibit exhibits[22];

const int NUM_OF_EXHIBITS = sizeof(exhibits) / sizeof(struct exhibit);

#include "header.h"

#endif
