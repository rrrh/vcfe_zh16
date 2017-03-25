#ifndef __SNES_REGS_H__
#define __SNES_REGS_H__

#include "snes_addresses.h"

extern unsigned int frame_count;

#define BASE_ADDR 0x2100

#define __REGB__(r) (*(volatile char*)((short)r))
#define __REGW__(r) (*(volatile short*)((short)r))

#define INIDISP				__REGB__(INIDISP_ADDR)

#define CGADD 				__REGB__(CGADD_ADDR)
#define CGDATA 				__REGB__(CGDATA_ADDR)

#define OBJSEL 				__REGB__(OBJSEL_ADDR)
#define OBJADDR				__REGW__(OBJADDRL_ADDR)
#define OBJADDRL			__REGB__(OBJADDRL_ADDR)
#define OBJADDRH			__REGB__(OBJADDRH_ADDR)
#define OBJDATA				__REGB__(OBJDATA_ADDR)
#define OBJDATAR			__REGB__(ROBJDATA_ADDR)
#define MOSAIC				__REGB__(MOSAIC_ADDR)

#define BG1SC 				__REGB__(BG1SC_ADDR)
#define BG2SC 				__REGB__(BG2SC_ADDR)
#define BG3SC 				__REGB__(BG3SC_ADDR)
#define BG4SC 				__REGB__(BG4SC_ADDR)

#define BG12NBA				__REGB__(BG12NBA_ADDR)
#define BG34NBA				__REGB__(BG34NBA_ADDR)

#define VMAINC				(*(char*)0x2115)

#define VMADD				__REGW__(VMADDL_ADDR)
#define VMADDL				__REGB__(VMADDL_ADDR)
#define VMADDH				__REGB__(VMADDH_ADDR)

#define VMDATA				__REGW__(VMDATA_ADDR)
#define VMDATAL				__REGB__(VMDATAL_ADDR)
#define VMDATAH				__REGB__(VMDATAH_ADDR)

#define M7SEL				__REGB__(M7SEL_ADDR)
#define M7A					__REGB__(M7A_ADDR)
#define M7B					__REGB__(M7B_ADDR)
#define M7C					__REGB__(M7C_ADDR)
#define M7D					__REGB__(M7D_ADDR)

#define M7X					__REGB__(M7X_ADDR)
#define M7Y					__REGB__(M7Y_ADDR)

#define BGMODE				__REGW__(BGMODE_ADDR)

#define BG1H0FS				(*(char*)0x210D)
#define BG1V0FS				(*(char*)0x210E)

#define BG2H0FS				(*(char*)0x210F)
#define BG2V0FS				(*(char*)0x2110)

#define BG3H0FS				(*(char*)0x2111)
#define BG3V0FS				(*(char*)0x2112)

#define BG4H0FS				(*(char*)0x2113)
#define BG4V0FS				(*(char*)0x2114)

#define CGSWSEL				__REGB__(CGSWSEL_ADDR)
#define CGADSUB			__REGB__(CGADDSUB_ADDR)
#define COLDATA				__REGB__(COLDATA_ADDR)

#define MPYL				(*(char*)0x2134)
#define MPYM				(*(char*)0x2135)
#define MPYH				(*(char*)0x2136)

#define DMA_0_CTRL 			(*(unsigned char*)0x4300)
#define DMA_0_DEST 			(*(unsigned char*)0x4301)
#define DMA_0_SRC 			(*(unsigned long*)0x4302)
#define DMA_0_SRC_BANK 		(*(unsigned char*)0x4304)
#define DMA_0_TFR_SIZE 		(*(unsigned long*)0x4305)
#define DMA_0_TFR_SIZE_HIGH (*(unsigned short*)0x4307)
#define DMA_0_DMA_CTRL		(*(unsigned int*)0x420B)
#define DMA_0_HDMA_CTRL		(*(unsigned int*)0x420C)

#define DMA_0_SRC_TEST 		(*(unsigned long*)0x4302)

/* bgb windowing */
#define W12SEL 				(*(unsigned char*)0x2123)
#define W34SEL 				(*(unsigned char*)0x2124)
#define WOBJSEL 			(*(unsigned char*)0x2125)

#define WH0 				(*(unsigned char*)0x2126)
#define WH1 				(*(unsigned char*)0x2127)
#define WH2 				(*(unsigned char*)0x2128)
#define WH3 				(*(unsigned char*)0x2129)

#define TWM 				(*(unsigned char*)0x212E)

/* mask settings */
#define WBGLOG 				(*(unsigned char*)0x212A)
#define WOBJLOG				(*(unsigned char*)0x212B)

/* main screen stuff */


#define TM					__REGB__(TM_ADDR)
#define TM_BIT_BG1			0x01
#define TM_BIT_BG2			0x02
#define TM_BIT_BG3			0x04
#define TM_BIT_BG4			0x08
#define TM_BIT_OBJ			0x10


#define TS 					__REGB__(TS_ADDR)
#define TS_BIT_BG1			0x01
#define TS_BIT_BG2			0x02
#define TS_BIT_BG3			0x04
#define TS_BIT_BG4			0x08
#define TS_BIT_OBJ			0x10





#define APUSTATUS			(*(unsigned char*)0x2140)
#define APUCMD				(*(unsigned char*)0x2141)
#define APUADDR 			(*(unsigned short*)0x2142)

#define APUPORT0			(*(unsigned char*)0x2140)
#define APUPORT1			(*(unsigned char*)0x2141)
#define APUPORT2 			(*(unsigned short*)0x2142)
#define APUPORT3 			(*(unsigned short*)0x2143)


#define DMA_MAIN_CTRL 		__REGB__(DMA_MAIN_CTRL_ADDR)
#define DMA_HMAIN_CTRL 		__REGB__(DMA_HMAIN_CTRL_ADDR)

#define NMITIMEN 			(*(unsigned char*)0x4200)
#define RDNMI 				(*(unsigned char*)0x4210)
#define TIMERIRQ			(*(unsigned char*)0x4211)
#define HVBJOY				__REGB__(0x4212)


#define HTIME				(*(unsigned char*)0x4207)
#define VTIME				(*(unsigned char*)0x4209)

#define STDCNTRL1			__REGW__(0x4218)
#define STDCNTRL1L			__REGB__(0x4218)
#define STDCNTRL1H			__REGB__(0x4219)


#define NOCASHDEBUGREG		(*(unsigned char*)0x21FC)

/*
* ###########################################################################
* SPC700 DSP REGISTER ADDRESSES
*/

#define DSP_VOL_0 			0x00
#define DSP_VOL_L_0			0x00
#define DSP_VOICE0_VOL_R 	0x01
#define DSP_VOICE0_PITCH 	0x02
#define DSP_VOICE0_PITCH_L 	0x02
#define DSP_VOICE0_PITCH_R 	0x03
#define DSP_VOICE0_SRC 		0x04
#define DSP_VOICE0_ADSR 	0x05

#define DSP_VOICE1_VOL 		0x10
#define DSP_VOICE1_VOL_L 	0x10
#define DSP_VOICE1_VOL_R 	0x11
#define DSP_VOICE1_PITCH 	0x12
#define DSP_VOICE1_PITCH_L 	0x12
#define DSP_VOICE1_PITCH_R 	0x13
#define DSP_VOICE1_SRC 		0x14
#define DSP_VOICE1_ADSR 	0x15

#endif
