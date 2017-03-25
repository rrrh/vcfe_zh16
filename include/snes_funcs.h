#ifndef __SNES_FUNCS_H__
#define __SNES_FUNCS_H__

extern struct oam_low_table oam_table_A[128];
extern unsigned short oam_table_B[16];

void setDisp(unsigned char brightness);
void setPal(unsigned char i, unsigned short c);

void initDMATransfer(void);
void initHDMATransfer(void);

void startDMATransfer(void);
void startHDMATransfer(void);

void clearAllDMA(void);

void addDMAChannel(unsigned char channel,
		unsigned char dest,
		unsigned char srcbank,
		unsigned short srcaddr,
		unsigned short size,
		enum DMA_MODES mode);

void addHDMAChannel(unsigned char channel,
		unsigned char dest,
		unsigned char srcbank,
		unsigned short srcaddr,
		unsigned short size,
		enum DMA_MODES mode);

void printsnes(char* str);

void snes_print_char(char c);
void snes_print_short(short s);
void snes_print_int(int i);

#define LOAD_RESOURCE(name, bank, clrAddr, clrSize, picAddr, picSize, mapAddr, mapSize) { \
	initDMATransfer(); \
	{ CGADD = clrAddr; VMADD = picAddr; \
		addDMAChannel(0, 0x18, bank, (short)&res_pic_##name, picSize, DMA_MODE_SHORT); \
		addDMAChannel(1, 0x22, bank, (short)&res_clr_##name, clrSize, DMA_MODE_BYTE_TWICE); \
	} startDMATransfer(); \
	initDMATransfer(); \
	{ VMADD = mapAddr; \
		addDMAChannel(2, 0x18, bank, (short)&res_map_##name, mapSize, DMA_MODE_SHORT); \
	} startDMATransfer(); \
}

#define LOAD_RESOURCE_MAP(name, bank, picAddr, picSize, mapAddr, mapSize) { \
	initDMATransfer(); \
	{ VMADD = picAddr; \
		addDMAChannel(0, 0x18, bank, (short)&res_pic_##name, picSize, DMA_MODE_SHORT); \
	} startDMATransfer(); \
	initDMATransfer(); \
	{ VMADD = mapAddr; \
		addDMAChannel(2, 0x18, bank, (short)&res_map_##name, mapSize, DMA_MODE_SHORT); \
	} startDMATransfer(); \
}

#define LOAD_RESOURCE_SPRITE(name, bank, clrAddr, clrSize, picAddr, picSize) { \
	initDMATransfer(); \
	{ CGADD = clrAddr; VMADD = picAddr; \
		addDMAChannel(0, 0x18, bank, (short)&res_pic_##name, picSize, DMA_MODE_SHORT); \
		addDMAChannel(1, 0x22, bank, (short)&res_clr_##name, clrSize, DMA_MODE_BYTE_TWICE); \
	} startDMATransfer(); \
}


#define LOAD_RESOURCE_RAW(name, bank, picAddr, picSize) { \
	initDMATransfer(); \
	{ VMADD = picAddr; \
		addDMAChannel(7, 0x18, bank, (short)&name, picSize, DMA_MODE_SHORT); \
	} startDMATransfer(); \
}

#define LOAD_RESOURCE_CLR(name, bank, clrAddr, clrSize) { \
	initDMATransfer(); \
	{ CGADD = clrAddr; \
		addDMAChannel(0, 0x22, bank, (short)&name, clrSize, DMA_MODE_BYTE_TWICE); \
	} startDMATransfer(); \
}

#define LOAD_FROM_ROM(name, bank, clrAddr, clrSize) { \
	initDMATransfer(); \
	{ CGADD = clrAddr; \
		addDMAChannel(0, 0x22, bank, (short)&name, clrSize, DMA_MODE_BYTE_TWICE); \
	} startDMATransfer(); \
}

void calculateRotScale(unsigned char angle, int x, int y, int scale_x, int scale_y);
void memset(void* dst, char val, int size);
unsigned char random(void);

void regWriteW(short addr, short value);

#endif
