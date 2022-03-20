.entry S2
			; mov check
S2: mov #1, r15
S3: mov #2, S1
mov #3, S2[r14]
mov S1, S2
mov S2, S3[r13]
mov S3, r12
mov S1[r11], S2
mov S2[r10], S3[r12]
 mov S3[r12], r7

.extern S1
S6: .string "cdef"
.data 1,2 ,3 , 4
			; cmp check
cmp #4, #5
cmp #6, S4
cmp #7, S1[r15]
cmp #8, r5
cmp S5, #9
cmp S4, S6
cmp S3, S7[r14]
cmp S2, r3
cmp S1[r12], #10
S5: cmp S1[r12], S2
cmp S1[r12], S3[r12]
cmp S1[r12], r0
S4: cmp r1, #11
cmp r1, S4
cmp r1, S5[r12]
cmp r1, r3

.extern S7
.entry S4
yarin: clr r1
			; add check
add #1, r15
add #2, S1
add #3, S2[r14]
add S1, S2
add S2, S3[r13]
add S3, r12
add S1[r11], S2
add S2[r10], S3[r15]
add S3[r12], r7

ofek: clr r2
			; add check
sub #1, r15
sub #2, S1
sub #3, S2[r14]
sub S1, S2
sub S2, S3[r13]
sub S3, r12
sub S1[r11], S2
sub S2[r10], S3[r10]
sub S3[r15], r7

dani: clr r3

