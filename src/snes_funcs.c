/* sh@sighup.ch */

#include <snes.h>
#include <res.h>

struct oam_low_table oam_table_A[128];
unsigned short oam_table_B[16];

short rgbToSnes(unsigned char r, unsigned char g, unsigned char b) {
	return (b/8 * 1024 + g/8 * 32 + r/8);
}

void setDisp(unsigned char brightness) {
	INIDISP = brightness;
}

void setPal(unsigned char i, unsigned short c) {
	CGADD = i;
    CGDATA = (char)(c);
    CGDATA = (char)(c >> 8);
}

/* DMA code, probably to be rewritten in assembler */
static unsigned char _dmaChannelArm;
static unsigned char _hdmaChannelArm;

void initDMATransfer(void) {
	_dmaChannelArm = 0;
}

void initHDMATransfer(void) {
	_hdmaChannelArm = 0;
}

void addDMAChannel(unsigned char channel,
		unsigned char dest,
		unsigned char srcbank,
		unsigned short srcaddr,
		unsigned short size,
		enum DMA_MODES mode) {

	unsigned char co = channel * 16;	// channel offset

	_dmaChannelArm |= 1 << channel;

	__REGB__(0x4301 + co) = (unsigned char)dest;
	__REGB__(0x4302 + co) = (unsigned char)srcaddr;
	__REGB__(0x4303 + co) = (unsigned char)(srcaddr >> 8);
	__REGB__(0x4304 + co) = srcbank;

	__REGB__(0x4305 + co) = (unsigned char)size;
	__REGB__(0x4306 + co) = (unsigned char)(size >> 8);
	__REGB__(0x4307 + co) = 0x0;

	__REGB__(0x4300 + co) = (unsigned char)mode;
}

void addHDMAChannel(unsigned char channel,
		unsigned char dest,
		unsigned char srcbank,
		unsigned short srcaddr,
		unsigned short size,
		enum DMA_MODES mode) {

	unsigned char co = channel * 16;	// channel offset

	_hdmaChannelArm |= 1 << channel;

	__REGB__(0x4301 + co) = (unsigned char)dest;
	__REGB__(0x4302 + co) = (unsigned char)srcaddr;
	__REGB__(0x4303 + co) = (unsigned char)(srcaddr >> 8);
	__REGB__(0x4304 + co) = srcbank;

	__REGB__(0x4305 + co) = (unsigned char)size;
	__REGB__(0x4306 + co) = (unsigned char)(size >> 8);
	__REGB__(0x4307 + co) = 0x0;

	__REGB__(0x4300 + co) = (unsigned char)mode;
}

void startHDMATransfer() {
	DMA_HMAIN_CTRL = _hdmaChannelArm;
	_hdmaChannelArm = 0;
}

void startDMATransfer() {
	DMA_MAIN_CTRL = _dmaChannelArm;
	_dmaChannelArm = 0;

	// busy wait for dma completion
	//while(DMA_MAIN_CTRL);
}

void clearAllDMA(void) {
//	printsnes("clear dma\n");
	DMA_HMAIN_CTRL = 0x0;
	DMA_MAIN_CTRL = 0x0;
}


/* debug functions */
void printsnes(char* str) {
	while(*str != 0) {
			NOCASHDEBUGREG = *str++;
	}
}

void createWindow(char x1, char x2, char y1, char y2) {
	//char hdmaTable[5] = { y1, 0x0, y2, 0x0, 0x0 };

	// transfer..
}

void loadSpriteResources(char* sprites, short lenght, short target) {

}

void regWriteW(short addr, short value) {
	*(volatile short*)(addr) = value;
}

/*
void setSpriteSlow(unsigned char spriteNum, struct sprite_desc* sprite) {

	unsigned char tmp;
	unsigned char tmpNum = spriteNum % 4;
	unsigned short tmp2;

	// next
	OBJADDR = spriteNum * 4;
	OBJDATA = sprite->x;
	OBJDATA = sprite->y;
	OBJDATA = spriteNum * 8;
	OBJDATA = 0x30;

	OBJADDR = 0x100 + spriteNum;
	tmp = OBJDATAR;
	OBJADDR = 0x100 + spriteNum;

	tmp &= ~(0x7 << tmpNum);
	tmp |= (((sprite->size << 1) | (sprite->x & 0x100) >> 8)) << tmpNum;

	OBJDATA = tmp;
}

void setSpritePending(unsigned char spriteNum, struct sprite_desc* sprite) {

	//unsigned char tmp;
//	unsigned char tmpNum = spriteNum % 4;
//	unsigned short tmp2;

//	struct oam_low_table* tmpA = oam_table_A[spriteNum * sizeof(struct oam_low_table)];

	// next
//	tmpA->x = sprite->x;
//	tmpA->y = sprite->y;
//	tmpA->tile = spriteNum * 8;
//	tmpA->attr = 0x30;

	//OBJADDR = 0x100 + spriteNum;
	//tmp = OBJDATAR;
	//OBJADDR = 0x100 + spriteNum;

	//tmp &= ~(0x7 << tmpNum);
	//tmp |= (((sprite->size << 1) | (sprite->x & 0x100) >> 8)) << tmpNum;

	//OBJDATA = tmp;
}
*/

void calculateRotScale(unsigned char angle, int x, int y, int scale_x, int scale_y) {
	int sin_index = angle;
	int cos_index = ((sin_index + 64) % 256);

	int sin = (&sin_table_s)[sin_index];
	int cos = (&sin_table_s)[cos_index];

	int sin_scaled = (&sin_table_s)[sin_index];


	char A, B, C, D;
	char A1, B1, C1, D1;

	sin_scaled >>= 6;

	//snes_print_char(sin-128);
	//printsnes("\n");

	//sin -= 128;
	//cos -= 128;


	//cos = cos >> 1;
	//sin = sin >> 1;

	// MPYL,M,H are multiply results
	// M7A,B,C,D matrix elements
	/*
	 * [ A, B ]   [ X ]
	 * [      ] * [   ]
	 * [ C, D ]   [ Y ]
	 *
	 */

	M7X = x & 0xFF;
	M7X = x >> 0xFF;

	M7Y = y & 0xFF;
	M7Y = y >> 0xFF;


	//snes_print_char(sin_scaled >> 2);
	//printsnes("\n");

	M7A = (char)scale_x & 0xFF;
	M7A = scale_x >> 8;
	M7B = cos;
	A = MPYH;
	A1 = MPYM;

	M7A = (char)scale_x & 0xFF;
	M7A = scale_x >> 8;
	M7B = sin;
	B = MPYH;
	B1 = MPYM;

	M7A = (char)(scale_y & 0xFF);
	M7A = scale_y >> 8;
	M7B = -(sin);
	C = MPYH;
	C1 = MPYM;

	M7A = (char)scale_y & 0xFF;
	M7A = scale_y >> 8;
	M7B = cos;
	D = MPYH;
	D1 = MPYM;

	M7A = A1; M7A = A;
	M7B = B1; M7B = B;
	M7C = C1; M7C = C;
	M7D = D1; M7D = D;
}

static void puth(char n)
{
    static const char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    NOCASHDEBUGREG = hex[n & 0xF];
}

void snes_print_char(char c) {
	puth(c >> 4);
	puth(c & 0xF);
}

void snes_print_short(short s) {
	puth(s >> 12);
	puth((s >> 8) & 0xF);
	puth((s >> 4) & 0xF);
	puth(s & 0xF);
}

void snes_print_int(int i) {
	puth(i >> 28);
	puth((i >> 24) & 0xF);
	puth((i >> 20) & 0xF);
	puth((i >> 16) & 0xF);

	puth((i >> 12) & 0xF);
	puth((i >> 8) & 0xF);
	puth((i >> 4) & 0xF);
	puth(i & 0xF);
}

void memset(void* dst, char val, int size) {
	int i = 0;
	char* tmp = (char*)dst;
	for(; i < size; ++i) {
		*tmp = val;
	}
}

unsigned char random(void) {
	static unsigned char index = 0;

	static const unsigned char lookup[256] = { 123, 151, 59, 114, 30, 28, 204,
			181, 103, 173, 39, 183, 206, 62, 253, 155, 0, 190, 51, 243, 66, 245,
			241, 91, 248, 207, 211, 2, 94, 108, 81, 246, 148, 132, 153, 159,
			167, 79, 17, 88, 176, 73, 251, 121, 41, 70, 71, 150, 219, 45, 252,
			129, 154, 227, 42, 249, 182, 157, 160, 109, 231, 136, 12, 201, 6,
			93, 203, 165, 125, 215, 234, 4, 137, 210, 149, 229, 97, 186, 60,
			197, 217, 106, 111, 49, 40, 220, 218, 77, 89, 37, 130, 174, 208,
			145, 57, 23, 29, 180, 124, 53, 98, 240, 214, 104, 254, 25, 105, 46,
			115, 171, 198, 188, 242, 122, 64, 152, 147, 48, 187, 162, 107, 221,
			24, 76, 230, 52, 184, 85, 35, 131, 5, 44, 169, 202, 156, 7, 205, 72,
			33, 32, 31, 9, 222, 216, 38, 179, 16, 168, 239, 166, 163, 142, 90,
			13, 83, 178, 138, 95, 195, 20, 113, 192, 177, 54, 135, 68, 200, 141,
			133, 84, 1, 212, 67, 102, 193, 80, 69, 140, 86, 139, 78, 244, 194,
			144, 175, 119, 118, 247, 47, 134, 10, 158, 112, 50, 196, 228, 22,
			143, 27, 223, 63, 146, 164, 18, 232, 213, 170, 224, 36, 191, 101,
			161, 99, 126, 55, 21, 74, 58, 238, 34, 237, 92, 185, 128, 11, 56,
			236, 110, 120, 100, 87, 233, 3, 15, 189, 209, 250, 19, 199, 96, 117,
			8, 172, 127, 65, 43, 116, 226, 14, 82, 225, 61, 26, 75, 235 };
	index = lookup[index];
	return index;
}
