; hns startup fty libraries
;
; (c) sh@sighup.ch
;
;

; Settings

	.setcpu         "65816"
	.import 		__SOFTSTACK_START__, __SOFTSTACK_SIZE__
    .importzp       sp, ptr1, ptr2, tmp1

    .import         __ZP_START__            ; Linker generated
    .include        "zeropage.inc"


	.import clear_snes

	.import force_vblank
	.import end_force_vblank

	.import _init
	.import _start
	.import _nmi
	.import _irq
	.import copydata
	.import storeZP
	.import restoreZP

	.export native_nmi
	.export native_irq
	.export emu_nmi
	.export emu_irq
	.export emu_reset


; make the linker happy
	.segment "SOFTSTACK"	
	.segment "HARDSTACK"

; data
	.bss
	.res 256
intrStack:

retsav: .res    2               ; Save buffer for return address

; code
.code

native_nmi:
	pha
	phx
	phy

	lda 	$4210       ; Clear NMI flag

	jsr     storeZP       ; Swap stuff

    lda     #<intrStack      ; Set new stack
    sta     sp
    lda     #>intrStack
    sta     sp+1

    jsr     _nmi            ; Call C code
	jsr     restoreZP       ; Swap stuff back

	ply
	plx
	pla
	rti

native_irq:
	rti;

emu_nmi:
	rti

emu_irq:
	;sei
	;clc
	;xce

	;jsr 	_irq

	rti

emu_reset:
	sei
	clc	
	xce

	jsr force_vblank
	jsr clear_snes


	rep #$10
	.i16
	ldx #$1FFF
	txs

	sep #$10
	.i8

	; setup the stack

	lda     #<(__SOFTSTACK_START__ + __SOFTSTACK_SIZE__)
	sta     sp
	lda     #>(__SOFTSTACK_START__ + __SOFTSTACK_SIZE__)
	sta     sp+1            ; Set argument stack ptr

	jsr copydata

	; switch to c code
	jsr _init

	jsr end_force_vblank
	cli
	
	; and again to c code
	jmp _start
