.setcpu	"65816"
	.export _MAC_size
	.export _MAC_sc_offset
	.export _MAC_pic
	.export _MAC_map
	.export _MAC_clr
	.export _PET2001_size
	.export _PET2001_sc_offset
	.export _PET2001_pic
	.export _PET2001_map
	.export _PET2001_clr
.segment "RODATA"
_MAC_size:
	.word 10240
_PET2001_size:
	.word 6144
_MAC_sc_offset:
	.byte 20
_PET2001_sc_offset:
	.byte 12
.segment "GFX4"
_MAC_clr:
	.incbin "data/exibits/Apple_Macintosh/apple_macintosh_180px_nq.clr"
_PET2001_clr:
	.incbin "data/exibits/Commodore_PET2001/PET2001_180x180_8.clr"
.segment "GFXC"
; ---- MAC
_MAC_pic:
	.incbin "data/exibits/Apple_Macintosh/apple_macintosh_180px_nq.pic"
; padding
	.res 1632, $AA
_MAC_map:
	.incbin "data/exibits/Apple_Macintosh/apple_macintosh_180px_nq.map"
; ---- PET2001
_PET2001_pic:
	.incbin "data/exibits/Commodore_PET2001/PET2001_180x180_8.pic"
; padding
	.res 1472, $AA
_PET2001_map:
	.incbin "data/exibits/Commodore_PET2001/PET2001_180x180_8.map"

