	opt	c+, at+, e+, n-
	section .text

	xdef sub_80020920
sub_80020920:
	dw 0x3C02800B ; 0x80020920
	dw 0x24423CA8 ; 0x80020924
	dw 0xAF8206B8 ; 0x80020928
	dw 0x03E00008 ; 0x8002092C
	dw 0x00000000 ; 0x80020930
