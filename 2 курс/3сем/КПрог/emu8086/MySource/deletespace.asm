data segment
    str db "123456 String !!!$"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
    mov ax, data
    mov ds, ax
    mov es, ax 
    mov si, offset str
cycle:  
    cmp byte ptr [si],' '
    je skip
    cmp byte ptr [si],'$'
    je exit
    mov dx ,[si]
    mov ah, 06h
    int 21h 
    inc si
    jmp cycle
exit:
    mov ax, 4c00h 
    int 21h    
skip:
    inc si
    jmp cycle
ends

end start