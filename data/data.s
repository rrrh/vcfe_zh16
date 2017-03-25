
	.setcpu         "65816"


	.export _res_clr_bg_pal_pet2001

	.export _res_clr_font_16x16_4bpp
	.export _res_pic_font_16x16_4bpp

	.export _res_clr_startup7
	.export _res_pic_startup7
	.export _res_map_startup7

	.export _sin_table_us
	.export _sin_table_s

	.export _res_clr_font
	.export _res_pic_font

	.export _res_map_border
	.export _res_clr_border
	.export _res_pic_border

	.export _res_clr_logos
	.export _res_pic_logos


.segment "PAD"

.segment "RODATA"

; exhibit bg palettes

_res_clr_bg_pal_pet2001:
	.include "data/bg.clr"

_sin_table_s:
	.include "data/sin_table_s.s"

_sin_table_us:
	.include "data/sin_table_us.s"

.segment "DATA"
_res_clr_sz_next_icon:
	.word $256

; startup GFX
; - merged mode 3 background and palette block including sprites.
;
.segment "GFX1"
; 0000
_res_pic_startup_logo:
	.incbin "data/splashscreen.pc7"
	;startup_logo.pc7"

; 4000
;.align #$4000
_res_map_startup_logo:
	.incbin "data/splashscreen.mp7"

; 8000
;.align #$8000
_res_clr_startup_logo:
	.incbin "data/splashscreen.clr"

.segment "GFX2"
.segment "GFX3"

_res_clr_startup7:
	.incbin "data/splashscreen.clr"
	;startup_logo.clr"
_res_pic_startup7:
	.incbin "data/splashscreen.pc7"
;	.incbin "data/font_16x16_4bpp.pic"
_res_map_startup7:
	.incbin "data/splashscreen.mp7"


.segment "GFX9"
_res_clr_font_16x16_4bpp:
	.incbin "data/font_16x16_4bpp.clr"
_res_pic_font_16x16_4bpp:
	.incbin "data/font_16x16_4bpp.pic"

.segment "GFX9"
.segment "GFXA"

_res_clr_font:
	.incbin "data/font.clr"
_res_pic_font:
	.incbin "data/font.pic"

_res_clr_logos:
	.incbin "resources/logo_sprites.clr"
_res_pic_logos:
	.incbin "resources/logo_sprites.pic"


_res_clr_border:
	.incbin "data/border.clr"
_res_pic_border:
	.incbin "data/border.pic"
_res_map_border:
	.include "data/border.map"

.segment "GFX8"
.segment "GFX9"
.segment "GFXA"
.segment "GFXB"
.segment "GFXC"
.segment "GFXD"
.segment "GFXE"
.segment "GFXF"

