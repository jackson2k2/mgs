	opt	c+, at+, e+, n-
	section .text

	xdef sub_8007F350
sub_8007F350:
	dw 0x1080000E ; 0x8007F350
	dw 0x00000000 ; 0x8007F354
	dw 0x10A0000C ; 0x8007F358
	dw 0x00000000 ; 0x8007F35C
	dw 0x8C820000 ; 0x8007F360
	dw 0xACA40004 ; 0x8007F364
	dw 0xACA20000 ; 0x8007F368
	dw 0x8C820000 ; 0x8007F36C
	dw 0x00000000 ; 0x8007F370
	dw 0x14440003 ; 0x8007F374
	dw 0x00000000 ; 0x8007F378
	dw 0x0801FCE2 ; 0x8007F37C
	dw 0xAC850004 ; 0x8007F380
	dw 0xAC450004 ; 0x8007F384
	dw 0xAC850000 ; 0x8007F388
	dw 0x03E00008 ; 0x8007F38C
	dw 0x00000000 ; 0x8007F390
