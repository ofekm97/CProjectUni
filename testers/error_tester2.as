; error tester for helpers

; long lineeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
.entry	LIST
.extern	Waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

MAIN:		add	r3, LIST,
2OOP:		prn	#48
		macro m1
 		  inc r6
		  mov r3, W
		endm
 		lea 	,STR, r6
 		m1
		macro m3
		endm
		sub	r1, r 4
 		bne	END,
 		cmp	val1, #-6, #1
 		bne	END[r20]
 		dec	K
.entry MAIN
 		sub	LOOP[r10] ,,r14
ENDaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa: 		stop
STR:	       .sring	"abcd" 
LIST: 	       .data	6, -9
 	       .data -100
.entry	 K
K:	       .data	-31
.extern val1
