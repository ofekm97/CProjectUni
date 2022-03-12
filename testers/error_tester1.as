; error tester for first move

A: .entry	LIST
B: .extern	W

MAIN:		add	r3, LIST
MAIN:		prn	#48
		macro m1
 		  inc r6
		  mov r3, W
		endm
 		lead	STR, r6
 		m1
		macro m3
		endm
		sub	r1, r4
 		bne	END
 		cmp	val1, #-6
 		bne	END[r15]
 		dec	K
.entry MAIN
 		sub	LOOP[r10] ,r14
END: 		sto
STR:	       .string	"abcd" 
LIST: 	       .data	6, -9
 	       .data -100
.entry	 K
K:	       .data	-31
.extern val1
a: .extern MAIN

