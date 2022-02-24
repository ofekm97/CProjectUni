; file ps.as
.entry LIST
.extern W

MAIN:		addw	r3, LIST
MAIN:		prn	#48
		macro m1
 		  inc r6
		  mov r3, W
		endm
 		lea 	STR
 		m1
		macro m3
		endm
		sub	r1, r4,a
 		bne	END
 		cmp	val1, #-6
 		bne	END[r15]
 		dec	#1
.entry MAIN
 		sub	LOOP[r16] ,r14
END: 		stop
ST-R:	       .string  "abcd"
1LIST: 	       .data    6, -9
 	       .data    -100
.entry K
K:	       .data    31
.extern val1
