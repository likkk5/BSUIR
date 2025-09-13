 org $8000
	ldab #0
	stab $4000 ;load zeros in memory for sub operation
        stab $4002 ;are not modified during the whole program
	stab $4004
	ldaa #35
	ldab #56
        staa $8200
	stab $8201
        ldaa #47
	ldab #22
        staa $8202
	stab $8203
	ldaa #69
	ldab #88
        staa $8204
	stab $8205
	ldab #33
        stab $8213
	ldab #98
        stab $82ff
	ldab #100
        stab $82fe
	ldx #33535 ;load final address to X
	ldab #255 ;load counter to B
	jmp help ;go to help label to skip the decrement 
	

begin:  decb
	decb
help:	stab $4001 ;load counter to memory (isn't modified during one iteration)
	beq end ;check if counter is equal to 0, if so, go to end
	ldab #0 ;load 0 to B
	xgdx ; auxiliary action
	subd $4000 ;get the initial address of next iteration
	xgdx ;write the address back to X
	ldaa $0000,x ;load data from the beginning to A


label0:	incb ; increment value in B
	cmpb $4001 ;compare value in B with the counter stored at $40001
	bhi begin  ;unsigned comparison, if value in B is greater than the counter come to begin
	cmpb $4000 ;compare value in B with 0
	bls begin ;unsigned comparison, if value in B is less/equal to 0 come to begin (last check in iteration)
	inx ;increment address
        cmpa $0000,x ;compare last bigger value with next position value
	blt label1 ;signed comparison, if value from A is less than the other value, go to label1
	jmp label0 ;else restart label0

label1: psha ;load little value to stack
	ldaa $0000,x ;load bigger value to A
	stab $4003 ;save actual counter from B in memory
        staa $4005 ;save bigger value from A in memory
	xgdx
	subd $4002 ;return X to begin
	xgdx
	staa $0000,x ;load bigger value to begin
        abx ;restore X, X+=B, B-actual shift
	pula ;load little value to A from stack
	staa $0000,x ;load little to M
	ldaa $4005 ;load bigger value to A
	jmp label0 ;go to label0

end:    ldy #0 ;the end of the program