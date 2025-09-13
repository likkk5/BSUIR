.model small
.stack 100h  

.data
   string db "12dg3", '$'
    
.code
start:
  
macro print out_string
    mov dx,offset out_string
    mov ah, 9
    int 21h
endm
  
ShowUInt16 proc        
    mov  bx, 10        ; Set divisor to 10 (decimal system)
    mov  cx, 0         ; Initialize counter

DIVV:                  
    xor  dx, dx        ; Clear DX (remainder)
    div  bx            ; Divide AX by BX, result in AX, remainder in DX
    add  dl, '0'       ; Convert remainder to ASCII
    push dx            ; Push the ASCII character onto the stack
    inc  cx            ; Increment the counter
    test ax, ax        ; Test if AX is not zero
    jnz  DIVV          ; Jump to DIVV if AX is not zero

SHOW:                  ; Display loop
    mov  ah, 02h       ; Set AH to 02h (function for displaying a character)
    pop  dx            ; Pop the ASCII character from the stack
    int  21h           ; Call interrupt 21h (output character)
    loop SHOW          ; Loop until CX becomes zero
    ret                ; Return from the procedure
ShowUInt16 endp 

call ShowUInt16
print string

end start