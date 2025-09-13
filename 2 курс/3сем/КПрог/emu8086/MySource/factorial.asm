factorial:
    push bp                 
    mov bp,sp               
    mov ax,[bp+4]           
    test ax,ax              
    jz f_ret1               
    dec ax                  
    push ax                 
    call factorial          
    mul word[bp+4]          
    jmp f_ret               
f_ret1:
    inc ax
f_ret:
    pop bp                  
    ret 2                   