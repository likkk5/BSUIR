 org $8000

 ldab #%00000100
 stab $8200
 ldab #%00100000
 stab $8201
 ldab #%00000000
 stab $8202
 ldab #%00100100
 stab $8203

 ldx #$8200

loop:
 ldaa 0,x
 ldab 0,x
 anda #%00000100
 andb #%00100000
 lsla
 lsla
 lsla
 stab $1
 eora $1
 cmpa #0
 bne make_one
 beq make_zero
 inx
 cpx #$8220
 bls loop
make_one: 
 bset 0,x,#%01000000
 inx
 cpx #$8220
 bls loop
make_zero:
 bclr 0,x,#%01000000
 inx
 cpx #$8220
 bls loop