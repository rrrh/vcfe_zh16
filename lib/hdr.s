; header
.define ROMTITLE "VCFE HNS 2016"
.define MAKERCODE "C3"
.define SNES "ACTE"

; external vectors
.import native_nmi
.import native_irq
.import emu_nmi
.import emu_irq
.import emu_reset

.segment "CODE"

; null vectors
null_vect:
native_cop:
native_brk:
native_abort:
native_unused:
	rti

; FFB0
.segment "ROMRESHEADER"
	.byte MAKERCODE		; maker code b0/1
	.byte SNES			; game code (4 bytes) b2-b5
	.byte 0				; fixed	0xb6
	.byte 0				; fixed	0xb7
	.byte 0				; fixed	0xb8
	.byte 0				; fixed	0xb9
	.byte 0				; fixed	0xba
	.byte 0				; fixed	0xbb
	.byte 0				; fixed	0xbc
	.byte 0				; exp ram 0xbd
	.byte 0				; special version 0xbe
	.byte 0				; cart type 0xbf

.segment "ROMHEADER"
	.byte ROMTITLE
	.res $15 - .strlen(ROMTITLE),$20
	.byte $31			; HiRom	0xD5
	.byte $02			; No SRAM 0xD6
	.byte $0C			; 128K ROM 0xD7
	.byte $03			; no SRAM 0xD8
	.byte $02			; country code 0xD9
	.byte $33			; licensee code 0xDA
	.byte $0			; version number 0xDB
	.word $0489		; dummy complement 0xDC/D
	.word $fb76			; dummy checksum 0xDE/F

.segment "VECTORS"		
	.word $0000			; what is this padding???
	.word $0000
	.word .loword(native_cop)	; e0
	.word .loword(native_brk)	; e2
	.word .loword(native_abort)	; e4
	.word .loword(native_nmi)	; ea
	.word .loword(native_unused); ec
	.word .loword(native_irq)	; ee
	
	.word $AAAA			; f0 checksum dummy
	.word $FFFF			; f2 checksum dummy

	.word .loword(null_vect)	; f4
	.word .loword(null_vect)	; f6
	.word .loword(null_vect)	; f8
	.word .loword(emu_nmi)		; fa
	.word .loword(emu_reset)	; fc
	.word .loword(emu_irq)		; fe


