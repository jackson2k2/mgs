	opt	c+, at+, e+, n-
	section .text

	xdef startIntrVSync_helper3_80098B48
startIntrVSync_helper3_80098B48:
	dw 0x10A00006 ; 0x80098B48
	dw 0x24A2FFFF ; 0x80098B4C
	dw 0x2403FFFF ; 0x80098B50
	dw 0xAC800000 ; 0x80098B54
	dw 0x2442FFFF ; 0x80098B58
	dw 0x1443FFFD ; 0x80098B5C
	dw 0x24840004 ; 0x80098B60
	dw 0x03E00008 ; 0x80098B64
	dw 0x00000000 ; 0x80098B68
	dw 0x00000000 ; 0x80098B6C
	dw 0x00000000 ; 0x80098B70
	dw 0x00000000 ; 0x80098B74
