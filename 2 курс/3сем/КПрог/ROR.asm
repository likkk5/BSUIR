 org $8100

 ldab #1
 stab $8208
 ldab #2
 stab $8207
 ldab #3
 stab $8206
 ldab #4
 stab $8205 
 ldab #5
 stab $8204 
 ldab #6
 stab $8203 
 ldab #7
 stab $8202 
 ldab #8
 stab $8201 
 ldab #0
 stab $8200   

 ldx #$81ff
 ldaa #3
loop:
 inx
 tab
 cmpa #0
 bne rorrr
compare:
 cpx #$8208
 bne loop
 beq end

rorrr:
 ror 0,x
 decb
 cmpb #0
 bne rorrr
 beq compare
end:          