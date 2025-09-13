.MODEL SMALL
.STACK 300h

.DATA
  array dw 10 dup(0)
  new_array dw 10 dup(0) 
  temp dd 0 
  
.CODE
  start:
   mov si,9
   mov di,0  
   mov ax,1
   mov array[di],ax
   mov array[di+1],2
   mov array[di+2],3
   mov array[di+3],4
   mov array[di+4],5
   mov array[di+5],6
   mov array[di+6],7
   mov array[di+7],8
   mov array[di+8],9
   mov array[di+9],10
   
   loop:
    mov ax,array[di]
    mov bx,ax
    mul bx,ax
    add bx,ax
    mov new_array[di],bx
    inc di
    cmp di,si
    jne loop   
   
    ;mov ax, array[di]
    ;imul bx, ax, ax  ; Use imul instead of mul for signed multiplication
    ;add bx, ax
    ;mov new_array[di], bx
    ;inc di
    ;cmp di, si
    ;jne loop   
    
    mov ax, 4c00h 
    int 21h   
END start