.model medium
 
.stack  200h
 
.data   
        startMessage      db      'This program calculates the average of the elements',0dh,0ah,'of an array of integers of size 10.', 0Dh, 0Ah,0dh,0ah,'Program has started.$'
        againMessage      db      0Dh, 0Ah,0dh,0ah,'Want to calculate again? (y/n): $'    
        checkMessage      db      0dh,0ah,'Are you sure in your choice? (y/n): $'
        CrLf              db      0Dh, 0Ah, '$'
        inputMessage      db      0Dh, 0Ah,0Dh, 0Ah, 'Enter an array of integers: ', 0Dh, 0Ah, '$'
        outputMessage     db      0Dh, 0Ah, 'Entered an array:', 0Dh, 0Ah, '$'
        averageMessage    db      0Dh, 0Ah, 'The average of the elements of an array of integers: $'
        iAverage          dw      ?
        N                 dw      ?
        Array             dw      10 dup(?)   
        errorMessage      db      0Dh, 0Ah, 'Error. The array can only contain integers. Re-enter the number or complete the entry: ', 0Dh, 0Ah, '$'
        continueMessage   db      0Dh, 0Ah,0Dh, 0Ah, 'The array must contain exactly 10 elements. Append the array with elements: ', 0Dh, 0Ah, '$' 
        overMessage       db      0Dh, 0Ah,0Dh, 0Ah, 'The array must contain exactly 10 elements. Entry of elements is completed.', 0Dh, 0Ah, '$' 
        overflowMessage   db      0Dh, 0Ah,0Dh, 0Ah, 'Error. The array can only contain integers ranging from -32768 to 32767.', 0Dh, 0Ah,'Re-enter the number or complete the entry: ', 0Dh, 0Ah, '$'  

.code 

ShowInt16       proc
        push    ax
        push    bx
        push    cx
        push    dx
        push    si
        push    di
        mov     bx,     10
        xor     cx,     cx     
        or      ax,     ax
        jns     div
                neg     ax
                push    ax
                mov     ah,     02h
                mov     dl,     '-'
                int     21h
                pop     ax
        div:
                xor     dx,     dx
                div     bx
                push    dx
                inc     cx      
                or      ax,     ax
        jnz     div
        mov     ah,     02h
        STORE:
                pop     dx
                add     dl,     '0'
                int     21h
        loop    STORE
        pop     di
        pop     si
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
ShowInt16       endp
 
ShowArray       proc
        push    ax
        push    bx
        push    cx
        push    dx
        push    si
        push    di
 
        jcxz    SA_EXIT       
 
        mov     si,     1      
        mov     di,     dx      
        SA_FOR_I:
                mov     ax,     [di]
                call    ShowInt16
                mov     ah,     02h
                mov     dl,     ' '
                int     21h
                inc     si
                add     di,     2
        loop    SA_FOR_I
SA_EXIT:
        pop     di
        pop     si
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
ShowArray       endp
 
main    proc
        mov     ax,     @data
        mov     ds,     ax  
        
        mov     dx,     offset startMessage
        mov     ah,     09h
        int     21h 
        
  BEGIN:     
        mov     dx,     offset inputMessage 
        mov     ah,     09h
        int     21h 
        
        mov     di,     offset Array            
        xor     cx,     cx                      
        xor     bx,     bx                     
        xor     si,     si     
                          
        FIRST_INPUT:
                   mov     ah,     01h            
                   int     21h
                   cmp     al,     '-'             
                   jne     IS_DIGIT1
                   mov     si,     -1      
                   jmp     CONTINUE_INPUT       
                   
                   IS_DIGIT1:            
                            cmp     al,     20h   
                            je      FIRST_INPUT                            
                            cmp     al,     0Dh   
                            je      FIRST_INPUT  
                            cmp     al,     '0'            
                            jb      DELETE_SYMBOL1
                            cmp     al,     '9'
                            ja      DELETE_SYMBOL1
                            push    ax             
                            mov     ax,     10
                            mul     bx
                            pop     bx
                            sub     bl,     '0'
                            xor     bh,     bh
                            add     bx,     ax                
                            jmp     CONTINUE_INPUT  
                            
                            DELETE_SYMBOL1:                       
                                           mov     dx,     offset errorMessage
                                           push    ax 
                                           mov     ah,     09h    
                                           int     21h 
                                           pop     ax                                
                                           mov     dx,     offset Array 
                                           xor     bx,     si     
                                           sub     bx,     si      
                                           xor     si,     si     
                                           xor     bx,     bx         
                                           call    ShowArray
               
  CONTINUE_INPUT:        
                 mov     ah,     01h             
                 int     21h    
                 cmp     bx,     0  
                 jne     IS_DIGIT
            CONT:        
                 cmp     al,     '-'         
                 jne     IS_DIGIT
                 mov     si,     -1     
                 jmp     CONTINUE_INPUT      
                 
                 IS_DIGIT:            
                          cmp     al,     20h   
                          je      STORE1                            
                          cmp     al,     0Dh   
                          je      STORE1  
                          cmp     al,     '0'             
                          jb      DELETE_SYMBOL
                          cmp     al,     '9'
                          ja      DELETE_SYMBOL 
                          push    ax             
                          mov     ax,     10
                          mul     bx
                          pop     bx
                          sub     bl,     '0'
                          xor     bh,     bh
                          add     bx,     ax  
                          cmp     si,     -1
                          je      CHECK_OTHER
                          cmp     bx,     32767
                          ja      ERROR_INPUT1
                          jmp     CONTINUE_INPUT        
                          
                          DELETE_SYMBOL:                         
                                        mov     dx,     offset errorMessage
                                        push    ax 
                                        mov     ah,     09h    
                                        int     21h 
                                        pop     ax
                                        mov     dx,     offset Array 
                                        xor     bx,     si      
                                        sub     bx,     si   
                                        xor     si,     si     
                                        xor     bx,     bx         
                                        cmp     al,     '0'             
                                        jb      OUTPUT_ARRAY      
                                        cmp     al,     '9'
                                        ja      OUTPUT_ARRAY   
                                        
                                        OUTPUT_ARRAY:      
                                                     call ShowArray
                                                     jmp CONTINUE_INPUT   
                                                          
     
    STORE1:    
           cmp     al,     0Dh          
           je      STORE2          
           cmp     bx,     0
           je      CONTINUE_INPUT   
                    
            STORE2:
                    xor     bx,     si      
                    sub     bx,     si      
                    xor     si,     si        
                    cmp     bx,     0
                    je      STORE3          
                    mov     [di],   bx      
                    add     di,     2
                    inc     cx  
                    cmp     cx,     10
                    je      OVER_INPUT  
                              
                    STORE3: xor     bx,     bx      
                            cmp     al,     0Dh    
                            je      BREAK          
                                                              
     CHECK_OTHER:
                 cmp     bx, 32768
                 ja      ERROR_INPUT1
                 jmp     CONTINUE_INPUT  
                             
                 ERROR_INPUT1:
                                mov     dx,     offset overflowMessage
                                push    ax 
                                mov     ah,     09h    
                                int     21h 
                                pop     ax  
                                mov     dx,     offset Array 
                                xor     bx,     si      
                                sub     bx,     si    
                                xor     si,     si     
                                xor     bx,     bx                                 
                                cmp     al,     '0'             
                                jb      OUTPUT_ARRAY      
                                cmp     al,     '9'
                                ja      OUTPUT_ARRAY  
                                
                                OVER_INPUT:
                                           mov     ah,     09h
                                           mov     dx,     offset overMessage
                                           int     21h    
                                           jmp     BREAK
                                                                          
                                           CONTINUE_INPUT1:
                                                          mov     ah,     09h
                                                          mov     dx,     offset continueMessage
                                                          int     21h  
                                                          mov     dx,     offset Array 
                                                          xor     bx,     si     
                                                          sub     bx,     si      
                                                          xor     si,     si     
                                                          xor     bx,     bx    
                                                          jmp     OUTPUT_ARRAY
    BREAK:             
            cmp     cx,     0    
            je      M1  
            jmp     M2
        M1:
            jmp     FIRST_INPUT
        M2:
            cmp     cx,     10
            jb      CONTINUE_INPUT1
            mov     [N],    cx
            mov     ah,     09h
            mov     dx,     offset outputMessage
            int     21h
            mov     cx,     [N]
            mov     dx,     offset Array
            call    ShowArray
            mov     cx,     [N]
            mov     si,     offset Array
            xor     bx,     bx
            xor     di,     di   
            
            FOR:
                lodsw
                cwd
                add     bx,     ax
                adc     di,     dx
                loop    FOR
                mov     dx,     di
                mov     ax,     bx
                idiv    [N]
                push ax
    push dx
    mov ax,N 
    mov cl,2
    idiv cl
    pop dx
    cmp dx,ax 
    jg greater
    jle skip
greater:
     pop ax
     inc ax
skip:    
    mov [iAverage], ax  ; Store the average in iAverage
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    mov dx, offset averageMessage  ; Load the offset address of averageMessage into DX
    int 21h           ; Call DOS function to print the averageMessage
    mov ax, [iAverage]  ; Load the average value into AX
    call ShowInt16   ; Call the ShowInt16 procedure to display the average
    mov ah, 09h
    jmp     AGAIN
          
   CHECK:
         mov dx,offset checkMessage 
         mov ah,09h
         int 21h
         mov ah,01h
         int 21h
         cmp al,79h
         je      M3  
         jmp     M4
     M3:
         jmp     BEGIN
     M4: 
         cmp al,59h
         je      M5  
         jmp     M6
     M5:
         jmp     BEGIN
     M6: 
         cmp al,6Eh
         je END
         cmp al,4Eh
         je END   
         jmp AGAIN        
 
          CHECK1:
                 mov dx,offset checkMessage 
                 mov ah,09h
                 int 21h
                 mov ah,01h
                 int 21h
                 cmp al,79h
                 je END 
                 cmp al,59h
                 je END
                 cmp al,6Eh
                 je      M7  
                 jmp     M8
     M7:
         jmp     BEGIN
     M8: 
                 cmp al,4Eh
                 je      M9  
                 jmp     M99
     M9:
         jmp     BEGIN
     M99:   
                 jmp AGAIN

                   AGAIN:
                         mov dx,offset againMessage
                         mov ah,09h
                         int 21h
                         mov ah,01h
                         int 21h
                         cmp al,79h ;y
                         je CHECK
                         cmp al,59h ;Y
                         je CHECK
                         cmp al,6Eh ;n
                         je CHECK1
                         cmp al,4Eh ;N
                         je CHECK1
                         jmp AGAIN
                         
    END:
        mov     ax,     4C00h
        int     21h 
        
main    endp
 
end     main