.model small
.stack 100h  

.data
   string db 6 dup(?)   ; Reserve space for a 6-character string
   newline db 0Dh, 0Ah, '$'
    
.code
start:  
mov ax,@data
mov ds,ax

mov ax, 1234            ; Your 16-bit number
xor dx, dx              ; Clear the DX register (remainder)
call ShowUInt16         ; Call the procedure to convert and display

mov ah, 4Ch             ; DOS service to exit the program
int 21h

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
    mov si, cx
    mov [string + si], dl ; Store the character in the string    
    mov dx, offset string
    mov ah, 9
    int 21h
    loop SHOW          ; Loop until CX becomes zero
    
   ; Display a new line
    mov dx, offset newline
    mov ah, 9
    int 21h   
    ret                ; Return from the procedure
ShowUInt16 endp 

end start