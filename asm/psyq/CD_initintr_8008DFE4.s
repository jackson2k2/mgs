	opt	c+, at+, e+, n-
	section .text

	xdef CD_initintr_8008DFE4
CD_initintr_8008DFE4:
	dw 0x27BDFFE8 ; 0x8008DFE4
	dw 0xAFBF0010 ; 0x8008DFE8
	dw 0x3C01800A ; 0x8008DFEC
	dw 0xAC203E6C ; 0x8008DFF0
	dw 0x3C01800A ; 0x8008DFF4
	dw 0xAC203E68 ; 0x8008DFF8
	dw 0x3C01800A ; 0x8008DFFC
	dw 0xAC203E78 ; 0x8008E000
	dw 0x3C01800A ; 0x8008E004
	dw 0x0C0260C6 ; 0x8008E008
	dw 0xAC203E74 ; 0x8008E00C
	dw 0x3C058009 ; 0x8008E010
	dw 0x24A5E570 ; 0x8008E014
	dw 0x0C0260D2 ; 0x8008E018
	dw 0x24040002 ; 0x8008E01C
	dw 0x8FBF0010 ; 0x8008E020
	dw 0x27BD0018 ; 0x8008E024
	dw 0x03E00008 ; 0x8008E028
	dw 0x00000000 ; 0x8008E02C
