; error tester for second move

.entry	LIST
.extern	W
MAIN:		add	r3, LIST1
LOOP:		prn	#48
 		lea 	sTR, r6
 		  inc r6
		  mov r3, W
		sub	r1, r4
 		bne	END
 		cmp	val1, #-6
 		bne	END[r15]
 		dec	K
  .entry MAIN
  .entry W
  .entry MAIN
 		sub	LOOP[r10] ,r14
END: 		stop
STR:	       .string	"abcd" 
LIST: 	       .data	6, -9
 	       .data -100
.entry	 K
K:	       .data	31
.extern val1
