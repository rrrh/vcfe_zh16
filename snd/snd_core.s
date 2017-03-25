; yeah.. a sound kernel
; target: support midi somehow..

; Registers


TESTREG		.equ	$F0
CNTRL		.equ	$F1

DSPADDR		.equ	$F2
DSPDATA		.equ	$F3

PORT0		.equ	$F4
PORT1		.equ	$F5
PORT2		.equ	$F6
PORT3		.equ	$F7

TIMER0		.equ	$FA
TIMER1		.equ	$FB
TIMER2		.equ	$FC

COUNTER0	.equ	$FD
COUNTER1	.equ	$FE
COUNTER2	.equ	$FF

VOL0L		.equ	$00
VOL0R		.equ	$01
P0L			.equ	$02
P0R			.equ	$03
SRCN0		.equ	$04
ADSR0L		.equ	$05
ADSR0H		.equ	$06
GAIN0		.equ	$07

VOL1L		.equ	$10
VOL1R		.equ	$11
P1L			.equ	$12
P1R			.equ	$13
SRCN1		.equ	$14
ADSR1L		.equ	$15
ADSR1H		.equ	$16
GAIN1		.equ	$17

VOL2L		.equ	$20
VOL2R		.equ	$21
P2L			.equ	$22
P2R			.equ	$23
SRCN2		.equ	$24
ADSR2L		.equ	$25
ADSR2H		.equ	$26
GAIN2		.equ	$27

VOL3L		.equ	$30
VOL3R		.equ	$31
P3L			.equ	$32
P3R			.equ	$33
SRCN3		.equ	$34
ADSR3L		.equ	$35
ADSR3H		.equ	$36
GAIN3		.equ	$37

VOL4L		.equ	$40
VOL4R		.equ	$41
P4L			.equ	$42
P4R			.equ	$43
SRCN4		.equ	$44
ADSR4L		.equ	$45
ADSR4H		.equ	$46
GAIN4		.equ	$47

VOL5L		.equ	$50
VOL5R		.equ	$51
P5L			.equ	$52
P5R			.equ	$53
SRCN5		.equ	$54
ADSR5L		.equ	$55
ADSR5H		.equ	$56
GAIN5		.equ	$57

VOL6L		.equ	$60
VOL6R		.equ	$61
P6L			.equ	$62
P6R			.equ	$63
SRCN6		.equ	$64
ADSR6L		.equ	$65
ADSR6H		.equ	$66
GAIN6		.equ	$67

VOL7L		.equ	$70
VOL7R		.equ	$71
P7L			.equ	$72
P7R			.equ	$73
SRCN7		.equ	$74
ADSR7L		.equ	$75
ADSR7H		.equ	$76
GAIN7		.equ	$77

MVOLL		.equ	$0C
MVOLR		.equ	$1C
EVOLL		.equ	$2C
EVOLR		.equ	$3C
KON			.equ	$4C
KOFF		.equ	$5C
FLG			.equ	$6C

EFB			.equ	$0D

PMON		.equ	$2D
NON			.equ	$3D
EON			.equ	$4D
DIR			.equ	$5D
ESA			.equ	$6D
EDL			.equ	$7D

FILTC0		.equ	$0F
FILTC1		.equ	$1F
FILTC2		.equ	$2F
FILTC3		.equ	$3F
FILTC4		.equ	$4F
FILTC5		.equ	$5F
FILTC6		.equ	$6F
FILTC7		.equ	$7F

; CPU Commands
SND_START		.equ	$01
SND_PAUSE		.equ	$02
SND_STOP		.equ	$03
SND_LOAD_DATA 	.equ	$04
SND_READ_REG	.equ	$05
SND_WRITE_REG	.equ	$06
SND_READ_DSP	.equ	$07
SND_WRITE_DSP	.equ	$08


; timing:
; 	clocked at: 24.576 MHz??
;
;	128/128 at 200bpm is aprox. 427Hz
;

; start

START

; HOUSEKEEPING
DSP_RESET:
	MOV 	X, #$00
	MOV 	A, #$80
DSP_RESET_LOOP:
	DEC		A
	MOV 	DSPADDR, A
	MOV 	DSPDATA, X
	BNE		DSP_RESET_LOOP

; HERE WE GO
SND_KERNEL_LOOP:
	; we are ok
	MOV		PORT0, #$CC

	BRA		SND_HANDLE_CPU_COMMAND
SND_KERNEL_LOOP_RET_A:
	BRA		SND_HANDLE_SEQ
SND_KERNEL_LOOP_RET_B:
	BRA 	SND_HANDLE_TRIGGER_POINT
SND_KERNEL_LOOP_RET_C:
	BRA 	SND_FLAG_STATE
SND_KERNEL_LOOP_RET_D:
	BRA 	SND_KERNEL_LOOP

SND_KERNEL_MAIN_LOOP:
	MOV		PORT0, #$CC

;	read in the command value from APU_CMD
	MOV		A, PORT0



	BRA SND_KERNEL_MAIN_LOOP

SND_KERNEL_MAIN_LOOP_END:
	MOV		PORT0, #$CC
	BRA 	SND_KERNEL_MAIN_LOOP


; do all the stuff needed for a CPU -> APU command
SND_HANDLE_CPU_COMMAND:
	MOV		A, PORT0

	CMP		A, #$00
	BEQ		CASE00

	CMP		A, #SND_WRITE_DSP	; write dsp reg
	BEQ		CASE01

	CMP		A, #SND_READ_DSP	; read dsp reg
	BEQ		CASE02

	CMP		A, #SND_WRITE_REG	; write kernel reg
	BEQ		CASE03

	CMP		A, #SND_READ_REG	; read kernel reg
	BEQ		CASE04

SND_HANLDE_CPU_COMMAND_RET:
	BRA		SND_KERNEL_LOOP_RET_A

; do the sequencer stuff. note on, note off, etc..
SND_HANDLE_SEQ:
	BRA 	SND_KERNEL_LOOP_RET_B

;
SND_HANDLE_TRIGGER_POINT:
	BRA 	SND_KERNEL_LOOP_RET_C

SND_FLAG_STATE:
	BRA		SND_KERNEL_LOOP_RET_D

; the dummy nop
CASE00:
	BRA		SND_HANLDE_CPU_COMMAND_RET


; write a dsp register
CASE01:
	MOV 	DSPADDR, PORT1
	MOV 	DSPDATA, PORT2
	BRA		SND_HANLDE_CPU_COMMAND_RET

; read a dsp register
CASE02:
	;MOV 	DSPADDR, PORT1
	;MOV 	DSPDATA, PORT2
	BRA		SND_HANLDE_CPU_COMMAND_RET

; write kernel reg
CASE03:
	MOV 	X, PORT1	; value
	MOV		A, PORT2
	MOV		[REGISTER_BANK+X], A
	BRA		SND_HANLDE_CPU_COMMAND_RET

; read kernel reg
CASE04:
	BRA		SND_HANLDE_CPU_COMMAND_RET

CASE05:
	BRA		SND_HANLDE_CPU_COMMAND_RET

CASE06:
	BRA		SND_HANLDE_CPU_COMMAND_RET

; now take time, and burn cycles
WAIT_FOR_TICK:
	MOV		A, COUNTER0
	BEQ		WAIT_FOR_TICK

; do key on etc.
	BRA		SND_KERNEL_MAIN_LOOP


; calculate ticks to burn
; now burn remaining cycles until the time slot has ended
BURN:
	NOP
	BRA		BURN

	BRA		TESTLOOP


.END


REGISTER_BANK:
TRACK_FREQ:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP



