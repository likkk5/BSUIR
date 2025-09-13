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
  bhs notSmaller
  staa 0,x                  

notSmaller:               
  cmpa 0,x           
  bls notGreater
  staa $8205
notGreater:
  cpx #$8204         
  bne loopStart

finish:
  dex 
  ldab 0,x


 ;ldaa $8201
 ;tab
 ;ldaa $8204
 ;aba
 ;staa $8210
 ;ldaa $8210
 ;ldd $8211