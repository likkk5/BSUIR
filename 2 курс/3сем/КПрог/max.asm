 org $8000

 ldaa #45 
 staa $8200             
 ldaa #44 
 staa $8201                      
 ldaa #111 
 staa $8202                    
 ldaa #99 
 staa $8203

 ldx #$8200   

loopStart:
  ldaa 0,x           
  inx
  cmpa 0,x           
  bls notSmaller
  staa 0,x                  

notSmaller:               
  cpx #$8204         
  bne loopStart

finish:
  dex 
  ldab 0,x