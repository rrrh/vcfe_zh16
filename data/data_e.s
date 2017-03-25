.setcpu         "65816"
.segment "GFX4"
.export _Altair_8800_main_clr
_Altair_8800_main_clr:
	.incbin "resources/exhibits/Altair_8800/Altair_8800_180x180_8.clr"
.export _Amiga_500_main_clr
_Amiga_500_main_clr:
	.incbin "resources/exhibits/Amiga_500/Amiga_500_180x180_8.clr"
.export _Apple_II_main_clr
_Apple_II_main_clr:
	.incbin "resources/exhibits/Apple_II/Apple_II_180x180_8.clr"
.export _Apple_Lisa_main_clr
_Apple_Lisa_main_clr:
	.incbin "resources/exhibits/Apple_Lisa/Apple_Lisa_180x180_8.clr"
.export _Apple_Macintosh_main_clr
_Apple_Macintosh_main_clr:
	.incbin "resources/exhibits/Apple_Macintosh/Apple_Macintosh_180x180_8.clr"
.export _BBC_Micro_main_clr
_BBC_Micro_main_clr:
	.incbin "resources/exhibits/BBC_Micro/BBC_Micro_180x180_8.clr"
.export _C128_main_clr
_C128_main_clr:
	.incbin "resources/exhibits/C128/C128_180x180_8.clr"
.export _C64_main_clr
_C64_main_clr:
	.incbin "resources/exhibits/C64/C64_180x180_8.clr"
.export _EpsonPX_main_clr
_EpsonPX_main_clr:
	.incbin "resources/exhibits/EpsonPX/EpsonPX_180x180_8.clr"
.export _HP200_main_clr
_HP200_main_clr:
	.incbin "resources/exhibits/HP200/hp200_180x180_8.clr"
.export _IMSAI8080_main_clr
_IMSAI8080_main_clr:
	.incbin "resources/exhibits/IMSAI8080/imsai8080_180x180_8.clr"
.export _JUPITER_ACE_main_clr
_JUPITER_ACE_main_clr:
	.incbin "resources/exhibits/JUPIRTER-ACE/jupiter-ace_180x180_8.clr"
.export _KIM1_main_clr
_KIM1_main_clr:
	.incbin "resources/exhibits/KIM1/kim1_180x180_8.clr"
.export _Lilith1_main_clr
_Lilith1_main_clr:
	.incbin "resources/exhibits/LILITH/lilith_180x180_8.clr"
.export _ORIC1_main_clr
_ORIC1_main_clr:
	.incbin "resources/exhibits/ORIC-1/ORIC-1_180x180_8.clr"
.export _PDP11_main_clr
_PDP11_main_clr:
	.incbin "resources/exhibits/PDP11/PDP11_180x180_8.clr"
.export _PDP8_main_clr
_PDP8_main_clr:
	.incbin "resources/exhibits/PDP8/pdp8_180x180_8.clr"
.export _PET2001_main_clr
_PET2001_main_clr:
	.incbin "resources/exhibits/PET2001/PET2001_180x180_8.clr"
.export _PLUS4_main_clr
_PLUS4_main_clr:
	.incbin "resources/exhibits/PLUS4/plus4_180x180_8.clr"
.export _PONG_main_clr
_PONG_main_clr:
	.incbin "resources/exhibits/PONG/PONG_180x180_8.clr"
.export _TI994a_main_clr
_TI994a_main_clr:
	.incbin "resources/exhibits/TI994a/TI-994a_180x180_8.clr"
.export _ZX81_main_clr
_ZX81_main_clr:
	.incbin "resources/exhibits/ZX81/ZX81_180x180_8.clr"
.segment "GFX5"
.export _Altair_8800_main_pic
_Altair_8800_main_pic:
	.incbin "resources/exhibits/Altair_8800/Altair_8800_180x180_8.pic"
	.res 1024, $AA
.export _Altair_8800_main_map
_Altair_8800_main_map:
	.incbin "resources/exhibits/Altair_8800/Altair_8800_180x180_8.map"
.export _Amiga_500_main_pic
_Amiga_500_main_pic:
	.incbin "resources/exhibits/Amiga_500/Amiga_500_180x180_8.pic"
	.res 1568, $AA
.export _Amiga_500_main_map
_Amiga_500_main_map:
	.incbin "resources/exhibits/Amiga_500/Amiga_500_180x180_8.map"
.export _Apple_II_main_pic
_Apple_II_main_pic:
	.incbin "resources/exhibits/Apple_II/Apple_II_180x180_8.pic"
	.res 1728, $AA
.export _Apple_II_main_map
_Apple_II_main_map:
	.incbin "resources/exhibits/Apple_II/Apple_II_180x180_8.map"
.export _Apple_Lisa_main_pic
_Apple_Lisa_main_pic:
	.incbin "resources/exhibits/Apple_Lisa/Apple_Lisa_180x180_8.pic"
	.res 128, $AA
.export _Apple_Lisa_main_map
_Apple_Lisa_main_map:
	.incbin "resources/exhibits/Apple_Lisa/Apple_Lisa_180x180_8.map"
.export _Apple_Macintosh_main_pic
_Apple_Macintosh_main_pic:
	.incbin "resources/exhibits/Apple_Macintosh/Apple_Macintosh_180x180_8.pic"
	.res 1664, $AA
.export _Apple_Macintosh_main_map
_Apple_Macintosh_main_map:
	.incbin "resources/exhibits/Apple_Macintosh/Apple_Macintosh_180x180_8.map"
.export _BBC_Micro_main_pic
_BBC_Micro_main_pic:
	.incbin "resources/exhibits/BBC_Micro/BBC_Micro_180x180_8.pic"
	.res 256, $AA
.export _BBC_Micro_main_map
_BBC_Micro_main_map:
	.incbin "resources/exhibits/BBC_Micro/BBC_Micro_180x180_8.map"
.segment "GFX6"
.export _C128_main_pic
_C128_main_pic:
	.incbin "resources/exhibits/C128/C128_180x180_8.pic"
	.res 1600, $AA
.export _C128_main_map
_C128_main_map:
	.incbin "resources/exhibits/C128/C128_180x180_8.map"
.export _C64_main_pic
_C64_main_pic:
	.incbin "resources/exhibits/C64/C64_180x180_8.pic"
	.res 704, $AA
.export _C64_main_map
_C64_main_map:
	.incbin "resources/exhibits/C64/C64_180x180_8.map"
.export _EpsonPX_main_pic
_EpsonPX_main_pic:
	.incbin "resources/exhibits/EpsonPX/EpsonPX_180x180_8.pic"
	.res 1440, $AA
.export _EpsonPX_main_map
_EpsonPX_main_map:
	.incbin "resources/exhibits/EpsonPX/EpsonPX_180x180_8.map"
.export _HP200_main_pic
_HP200_main_pic:
	.incbin "resources/exhibits/HP200/hp200_180x180_8.pic"
	.res 1600, $AA
.export _HP200_main_map
_HP200_main_map:
	.incbin "resources/exhibits/HP200/hp200_180x180_8.map"
.export _IMSAI8080_main_pic
_IMSAI8080_main_pic:
	.incbin "resources/exhibits/IMSAI8080/imsai8080_180x180_8.pic"
	.res 192, $AA
.export _IMSAI8080_main_map
_IMSAI8080_main_map:
	.incbin "resources/exhibits/IMSAI8080/imsai8080_180x180_8.map"
.export _JUPITER_ACE_main_pic
_JUPITER_ACE_main_pic:
	.incbin "resources/exhibits/JUPIRTER-ACE/jupiter-ace_180x180_8.pic"
	.res 544, $AA
.export _JUPITER_ACE_main_map
_JUPITER_ACE_main_map:
	.incbin "resources/exhibits/JUPIRTER-ACE/jupiter-ace_180x180_8.map"
.export _KIM1_main_pic
_KIM1_main_pic:
	.incbin "resources/exhibits/KIM1/kim1_180x180_8.pic"
	.res 256, $AA
.export _KIM1_main_map
_KIM1_main_map:
	.incbin "resources/exhibits/KIM1/kim1_180x180_8.map"
.segment "GFX7"
.export _Lilith1_main_pic
_Lilith1_main_pic:
	.incbin "resources/exhibits/LILITH/lilith_180x180_8.pic"
	.res 480, $AA
.export _Lilith1_main_map
_Lilith1_main_map:
	.incbin "resources/exhibits/LILITH/lilith_180x180_8.map"
.export _ORIC1_main_pic
_ORIC1_main_pic:
	.incbin "resources/exhibits/ORIC-1/ORIC-1_180x180_8.pic"
	.res 1312, $AA
.export _ORIC1_main_map
_ORIC1_main_map:
	.incbin "resources/exhibits/ORIC-1/ORIC-1_180x180_8.map"
.export _PDP11_main_pic
_PDP11_main_pic:
	.incbin "resources/exhibits/PDP11/PDP11_180x180_8.pic"
	.res 1472, $AA
.export _PDP11_main_map
_PDP11_main_map:
	.incbin "resources/exhibits/PDP11/PDP11_180x180_8.map"
.export _PDP8_main_pic
_PDP8_main_pic:
	.incbin "resources/exhibits/PDP8/pdp8_180x180_8.pic"
	.res 1344, $AA
.export _PDP8_main_map
_PDP8_main_map:
	.incbin "resources/exhibits/PDP8/pdp8_180x180_8.map"
.export _PET2001_main_pic
_PET2001_main_pic:
	.incbin "resources/exhibits/PET2001/PET2001_180x180_8.pic"
	.res 160, $AA
.export _PET2001_main_map
_PET2001_main_map:
	.incbin "resources/exhibits/PET2001/PET2001_180x180_8.map"
.export _PLUS4_main_pic
_PLUS4_main_pic:
	.incbin "resources/exhibits/PLUS4/plus4_180x180_8.pic"
	.res 1632, $AA
.export _PLUS4_main_map
_PLUS4_main_map:
	.incbin "resources/exhibits/PLUS4/plus4_180x180_8.map"
.segment "GFX8"
.export _PONG_main_pic
_PONG_main_pic:
	.incbin "resources/exhibits/PONG/PONG_180x180_8.pic"
	.res 1408, $AA
.export _PONG_main_map
_PONG_main_map:
	.incbin "resources/exhibits/PONG/PONG_180x180_8.map"
.export _TI994a_main_pic
_TI994a_main_pic:
	.incbin "resources/exhibits/TI994a/TI-994a_180x180_8.pic"
	.res 224, $AA
.export _TI994a_main_map
_TI994a_main_map:
	.incbin "resources/exhibits/TI994a/TI-994a_180x180_8.map"
.export _ZX81_main_pic
_ZX81_main_pic:
	.incbin "resources/exhibits/ZX81/ZX81_180x180_8.pic"
	.res 224, $AA
.export _ZX81_main_map
_ZX81_main_map:
	.incbin "resources/exhibits/ZX81/ZX81_180x180_8.map"
