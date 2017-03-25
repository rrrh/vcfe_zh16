/*
 * memory.c
 *
 *  Basic PPU memory management.
 *
 *  Created on: 07.08.2013
 *      Author: hns
 */

typedef struct BLOCK4K {

} block4k_t;

typedef struct BLOCK1K {

} block1k_t;

/*

 VRAM Layout:

 map data: 1k blocks
 sc data: 4k blocks
 obj data: 2x4k blocks (upper block relocatable to 0x0000, 0x1000, 0x2000 or 0x7FFF

 proposed layout:

 0k  to 24k BG  Data
 24k to 28k Obj Data
 28k to 32k Map Data

 */

