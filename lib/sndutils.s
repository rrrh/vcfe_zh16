; basic sound kernel

	.setcpu         "65816"
	.import 		__SOFTSTACK_START__, __SOFTSTACK_SIZE__
    .importzp       sp, ptr1, ptr2, tmp1

    .import         __ZP_START__            ; Linker generated
    .include        "zeropage.inc"

    .import incsp2
    .import incsp4

	.export _apuSndStartExec
	.export _apuWaitReady
	.export _apuSetTransferAddr
	.export _apuSetNextTransferAddr
	.export _apuTransferBlock

	APU_STAT 	= $2140 ;
	APU_CMD 	= $2141	;
	APU_ADDR 	= $2142	;

.code
; SND_ADDR = DIR * 100h + SRCN * 4
;
; eg. DIR = 4, SRCN = 0
; addr

; len (sp),3
; bank (sp),2
; addr (sp),0

; ********************************
; 50 stages of transfer :)

_apuWaitReady:
	lda #$AA
:
	cmp	$2140
	bne :-
	lda #$BB
:
	cmp $2141
	bne :-

	rts

; (sp) addr
_apuSetTransferAddr:
	pha
	phx
	phy

	rep #$20
.a16
	lda (sp)
	sta $2142
.a8
	sep #$20

	lda #$CC
	sta $2141
	sta $2140

:
	cmp $2140
	bne :-

	ply
	plx
	pla

	jsr     incsp2
	rts

; (sp) addr
_apuSetNextTransferAddr:
	rep #$20
.a16
	lda (sp)
	sta $2142
.a8
	sep #$20

	lda $2140
	ina
:	ina
	beq :-
	sta $2140
:
	cmp $2140
	bne :-

	rts


; (sp) 		src addr
; (sp),2 	bank
; (sp),3	len
_apuTransferBlock:

	pha
	phx
	phy

	ldy #$03
	lda (sp),y
	ina
	tax

	rep #$20
.a16
	lda (sp)
	sta $A0	; zero page hack
.a8
	sep #$20

	dey
	lda (sp),y
	phb									; push the data bank reg

		pha								; push the new bank
		plb								; pull the data bank reg

		ldy #$00

:
		lda ($A0),y

		phb								; push the data bank reg

		phk								; je deteste ma vie..
		plb								;   we push the program register since
										;   it is zero..

		sta $2141 						; set data

		tya
		sta $2140 						; set counter

:
		cmp $2140
		bne :-

		plb

		iny
		dex
		txa
		bne :--

	plb

	ply
	plx
	pla

	jsr     incsp4
	rts

; (sp) addr
_apuSndStartExec:
	ldy #$00
	sty APU_CMD

	rep #$20
.a16
	lda (sp),y
	sta APU_ADDR
.a8
	sep #$20
	lda APU_STAT
	ina
	ina
	sta APU_STAT

	rts
