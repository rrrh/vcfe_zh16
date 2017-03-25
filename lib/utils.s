; utility libraries
;
; (c) sh@sighup.ch
;
;
	.setcpu		"65816"
	.importzp	sp, sreg, regsave, regbank, tmp1, ptr1, ptr2
	.import     	__DATA_LOAD__, __DATA_RUN__, __DATA_SIZE__
	.import		__ZP_START__
	.import 	incsp7

	.include 	"zeropage.inc"

	.export 	clear_snes
	.export 	force_vblank
	.export 	end_force_vblank
	.export		copydata
	.export		storeZP
	.export		restoreZP
	.export 	_hdma_transfer_ind
	.export 	_hdma_transfer_dir

	.export 	_switch_bank
	.export 	_switch_bank_back

	.bss

tmpZPdata:
	.res    (zpspace)     ; Other stuff

	.code

	.export _force_vblank
_force_vblank:
force_vblank:
	lda #$8F
	sta $2100
	rts

	.export _end_force_vblank
_end_force_vblank:
end_force_vblank:
	lda #$0F
	sta $2100
	rts


.export clear_snes
clear_snes:
		lda #$00
		sta $2101
		stz $2102
		stz $2103
		stz $2104
		sta $2105
		sta $2106
		sta $2107
		sta $2108
		sta $2109
		sta $210A
		sta $210B
		sta $210C

		; words come here
		sta $210D
		sta $210D

		sta $210E
		sta $210E

		sta $210F
		sta $210F

		sta $2110
		sta $2110

		sta $2111
		sta $2111

		sta $2112
		sta $2112

		sta $2113
		sta $2113

		sta $2114
		sta $2114

		lda #$80
		sta $2115

		lda #$00
		sta $2116
		sta $2117
		sta $2118
		sta $2119
		sta $211A

		; more words
		sta $211B
		sta $211B

		sta $211C
		sta $211C

		sta $211D
		sta $211D

		sta $211E
		sta $211E

		sta $211F
		sta $211F

		sta $2120
		sta $2120

		sta $2121
		sta $2122
		sta $2123
		sta $2124
		sta $2125
		sta $2126
		sta $2127
		sta $2128
		sta $2129
		sta $212A
		sta $212B
		sta $212C
		sta $212D
		sta $212E

		lda #$30
		sta $2130

		lda #$00
		sta $2131

		lda #$E0
		sta $2132

		lda #$00
		sta $2133

		sta $4200

		lda #$FF
		sta $4201

		lda #$00
		sta $4202
		sta $4203
		sta $4204
		sta $4205
		sta $4206
		sta $4207
		sta $4208
		sta $4209
		sta $420A
		sta $420B
		sta $420C
		sta $420D

		rts


copydata:
	    lda	#<__DATA_LOAD__         ; Source pointer
	    sta	ptr1
	    lda	#>__DATA_LOAD__
	    sta	ptr1+1

	    lda	#<__DATA_RUN__          ; Target pointer
	    sta	ptr2
	    lda	#>__DATA_RUN__
	    sta	ptr2+1

	    ldx	#<~__DATA_SIZE__
	    lda	#>~__DATA_SIZE__        ; Use -(__DATASIZE__+1)
	    sta	tmp1
	    ldy	#$00

	; Copy loop

	@L1:    inx
	        beq	@L3

	@L2:    lda	(ptr1),y
	        sta	(ptr2),y
	        iny
	        bne	@L1
	        inc	ptr1+1
	        inc	ptr2+1                  ; Bump pointers
	        bne	@L1                     ; Branch always (hopefully)

	; Bump the high counter byte

	@L3:    inc	tmp1
	        bne	@L2

	        rts

storeZP:
	        ldy     #zpspace-1
	:
	        lda     <__ZP_START__,y
	        sta     tmpZPdata,y
	        dey
	        bpl     :-

	        rts;

	; restore ZP

restoreZP:
	        ldy     #zpspace-1
	:
	        lda     tmpZPdata,y
	        sta     sp,y
	        dey
	        bpl     :-

	        rts;

	.export _sn_dma_register;
_sn_dma_register:

	rts

_switch_bank:
	phb;
	pha;
	lda #$01
	pha
	plb;
	rts;

_switch_bank_back:
	pla
	plb;
	rts;


_hdma_transfer_ind:
		phy

		lda     #$42 ; indirect, 2 bytes 01000010
		sta     $4300

		lda 	#$2
		sta     $4304 ; bank number (hardcoded for now)
		sta     $4307 ; bank number (hardcoded for now)

		ldy     #$04
		lda     (sp),y
		sta     $4301

		rep     #$30
.i16
.a16
		ldy     #$05
		lda     (sp),y
		sta     $4302
.a8
.i8
		sep     #$30

		lda     #$01
		sta     $420C

		jsr     incsp7

		ply
		rts

_hdma_transfer_dir:
		phy

		lda     #$00 ; direct, 1 byte 0000000
		sta     $4300

		lda 	#$3
		sta     $4304 ; bank number (3 for now)
		sta     $4307 ; bank number (3 for now)

		ldy     #$04
		lda     (sp),y
		sta     $4301

		rep     #$30
.i16
.a16
		ldy     #$05
		lda     (sp),y
		sta     $4302
.a8
.i8
		sep     #$30

		lda     #$01
		sta     $420C

		jsr     incsp7

		ply
		rts


	.segment "RES1"
	.segment "RES2"
	.segment "RES3"
	.segment "RES4"
	.segment "RES5"
	.segment "RES6"
	.segment "RES7"
	.segment "RES8"
	.segment "RES9"
	.segment "RESA"
