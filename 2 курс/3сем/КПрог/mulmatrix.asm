 org $8000

 ldx #$8400   

 ldaa #1 
 staa 0,x     
 inx         
 ldaa #2 
 staa 0,x     
 inx                 
 ldaa #3 
 staa 0,x     
 inx                 
 ldaa #4 
 staa 0,x 

 ldx #$8410   

 ldaa #5 
 staa 0,x     
 inx         
 ldaa #6 
 staa 0,x  

 ldx #$8420   

; 1*5 + 2*6
 ldaa #1
 tab
 ldaa #5
 mul 
 std $8420
 ldaa #2
 tab
 ldaa #6
 mul 
 addd $8420  
 std $8420

; 3*5+4*6
 ldaa #3
 tab
 ldaa #5
 mul 
 std $8422
 ldaa #4
 tab
 ldaa #6
 mul 
 addd $8422  
 std $8422

 ; 1*5 + 2*6
 ;ldaa $8400
 ;tab
 ;ldaa $8410
 ;mul 
 ;std $8420
 ;ldaa $8401
 ;tab
 ;ldaa $8411
 ;mul 
 ;addd $8420  
 ;std $8420

;3*5 + 4*6
 ;ldaa $8402
 ;ldab $8410
 ;mul
 ;std $8422
 ;ldaa $8403
 ;ldab $8411
 ;mul
 ;addd $8422
 ;std $8422