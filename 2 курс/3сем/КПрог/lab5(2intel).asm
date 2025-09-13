.model small
.stack 100h

.data
    startMessage      db 'This program calculates the average value of array elements:',0Ah, 0Dh, '$'  
    inputMessage      db 'Enter an array of integers: ', 0Dh, 0Ah, '$'
    outputMessage     db 0Dh, 0Ah, 'Entered an array:', 0Dh, 0Ah, '$'
    averageMessage    db 0Dh, 0Ah, 'The average of the elements of an array of integers: $'
    iAverage          dw ?
    N                 dw ?
    Array             dw 10 dup(?)
    errorMessage      db 0Dh, 0Ah, 'Error. The array can only contain integers. Re-enter the number or complete the entry: ', 0Dh, 0Ah, '$'
    continueMessage   db 0Dh, 0Ah, 0Dh, 0Ah, 'The array must contain exactly 30 elements. Append the array with elements: ', 0Dh, 0Ah, '$'
    overMessage       db 0Dh, 0Ah, 0Dh, 0Ah, 'The array must contain exactly 30 elements. Entry of elements is completed.', 0Dh, 0Ah, '$'
    overflowMessage   db 0Dh, 0Ah, 0Dh, 0Ah, 'Error. The array can only contain integers ranging from -32768 to 32767.', 0Dh, 0Ah, 'Re-enter the number or complete the entry: ', 0Dh, 0Ah, '$'
    variable dw 2
.code

ShowInt16 proc
    push ax          ; Save the value of AX register on the stack
    push bx          ; Save the value of BX register on the stack
    push cx          ; Save the value of CX register on the stack
    push dx          ; Save the value of DX register on the stack
    push si          ; Save the value of SI register on the stack
    push di          ; Save the value of DI register on the stack
    mov bx, 10       ; Set BX to 10 (base for decimal conversion)
    xor cx, cx       ; Clear CX register (counter for digits)
    or ax, ax        ; Set flags based on the value in AX
    jns div          ; Jump to 'div' if AX is not negative
    neg ax           ; Negate AX (make it positive)
    push ax          ; Push the absolute value of AX on the stack
    mov ah, 02h      ; Set AH to 02h (function to print a character)
    mov dl, '-'      ; Set DL to '-' (to print a minus sign)
    int 21h          ; Call DOS function to print the character
    pop ax           ; Pop the original value of AX from the stack
div:
    xor dx, dx       ; Clear DX (remainder for division)
    div bx           ; Divide AX by BX; result in AX, remainder in DX
    push dx          ; Push the remainder on the stack (digit)
    inc cx           ; Increment the digit counter
    or ax, ax        ; Check if AX is zero (end of division)
    jnz div          ; If not zero, continue dividing
    mov ah, 02h      ; Set AH to 02h (function to print a character)
STORE:
    pop dx           ; Pop a digit from the stack
    add dl, '0'      ; Convert the digit to ASCII
    int 21h          ; Print the character
    loop STORE       ; Loop until all digits are printed
    pop di           ; Restore the value of DI from the stack
    pop si           ; Restore the value of SI from the stack
    pop dx           ; Restore the value of DX from the stack
    pop cx           ; Restore the value of CX from the stack
    pop bx           ; Restore the value of BX from the stack
    pop ax           ; Restore the value of AX from the stack
    ret              ; Return from the procedure
ShowInt16 endp      ; End of the procedure

ShowArray proc
    push ax          ; Save the value of AX register on the stack
    push bx          ; Save the value of BX register on the stack
    push cx          ; Save the value of CX register on the stack
    push dx          ; Save the value of DX register on the stack
    push si          ; Save the value of SI register on the stack
    push di          ; Save the value of DI register on the stack
    jcxz SA_EXIT     ; Jump to SA_EXIT if CX (array size) is zero
    mov si, 1        ; Set SI to 1 (index for the array elements)
    mov di, dx       ; Set DI to DX (pointer to the array)
SA_FOR_I:
    mov ax, [di]     ; Load a 16-bit integer from the array to AX
    call ShowInt16   ; Call the ShowInt16 procedure to display the integer
    mov ah, 02h      ; Set AH to 02h (function to print a character)
    mov dl, ' '      ; Set DL to ' ' (space character)
    int 21h          ; Print the space character
    inc si           ; Increment the array index
    add di, 2        ; Move the pointer to the next 16-bit integer
    loop SA_FOR_I    ; Loop until all array elements are displayed
SA_EXIT:
    pop di           ; Restore the value of DI from the stack
    pop si           ; Restore the value of SI from the stack
    pop dx           ; Restore the value of DX from the stack
    pop cx           ; Restore the value of CX from the stack
    pop bx           ; Restore the value of BX from the stack
    pop ax           ; Restore the value of AX from the stack
    ret              ; Return from the procedure
ShowArray endp      ; End of the procedure

main proc
    mov ax, @data    ; Load the address of the data segment into AX
    mov ds, ax       ; Initialize the data segment with the value in AX

    mov dx, offset startMessage  ; Load the offset address of startMessage into DX
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    int 21h           ; Call DOS function to print the startMessage

BEGIN:
    mov dx, offset inputMessage  ; Load the offset address of inputMessage into DX
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    int 21h           ; Call DOS function to print the inputMessage

    mov di, offset Array  ; Load the offset address of Array into DI
    xor cx, cx        ; Clear CX register (counter for array elements)
    xor bx, bx        ; Clear BX register (temporary variable for input)
    xor si, si        ; Clear SI register (sign flag for negative numbers)

FIRST_INPUT:
    mov ah, 01h       ; Set AH to 01h (function to read a character from standard input)
    int 21h           ; Call DOS function to read a character into AL

    cmp al, '-'       ; Compare AL with '-' (check if the input is a negative sign)
    jne IS_DIGIT1     ; If not a negative sign, jump to IS_DIGIT1
    mov si, -1        ; Set SI to -1 (to represent a negative number)
    jmp CONTINUE_INPUT ; Jump to CONTINUE_INPUT

IS_DIGIT1:
    cmp al, 20h       ; Compare AL with space character
    je FIRST_INPUT    ; If space, jump to FIRST_INPUT
    cmp al, 0Dh       ; Compare AL with carriage return (Enter key)
    je FIRST_INPUT    ; If Enter key, jump to FIRST_INPUT
    cmp al, '0'       ; Compare AL with '0'
    jb DELETE_SYMBOL1 ; If less than '0', jump to DELETE_SYMBOL1
    cmp al, '9'       ; Compare AL with '9'
    ja DELETE_SYMBOL1 ; If greater than '9', jump to DELETE_SYMBOL1
    push ax           ; Push AX on the stack
    mov ax, 10        ; Set AX to 10
    mul bx            ; Multiply AX by BX
    pop bx            ; Pop the original value of AX from the stack
    sub bl, '0'       ; Convert the character to its numeric value
    xor bh, bh        ; Clear BH register
    add bx, ax        ; Update BX with the new value
    jmp CONTINUE_INPUT ; Jump to CONTINUE_INPUT

DELETE_SYMBOL1:
    mov dx, offset errorMessage  ; Load the offset address of errorMessage into DX
    push ax           ; Push AX on the stack
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    int 21h           ; Call DOS function to print the errorMessage
    pop ax            ; Pop the original value of AX from the stack
    mov dx, offset Array  ; Load the offset address of Array into DX
    xor bx, si        ; XOR BX with SI (clear BX if SI is -1)
    sub bx, si        ; Subtract SI from BX (convert negative to positive)
    xor si, si        ; Clear SI (reset sign flag)
    xor bx, bx        ; Clear BX
    call ShowArray    ; Call the ShowArray procedure to display the array

CONTINUE_INPUT:
    mov ah, 01h       ; Set AH to 01h (function to read a character from standard input)
    int 21h           ; Call DOS function to read a character into AL
    cmp bx, 0         ; Compare BX with 0
    jne IS_DIGIT      ; If not zero, jump to IS_DIGIT
CONT:
    cmp al, '-'       ; Compare AL with '-' (check if the input is a negative sign)
    jne IS_DIGIT      ; If not a negative sign, jump to IS_DIGIT
    mov si, -1        ; Set SI to -1 (to represent a negative number)
    jmp CONTINUE_INPUT ; Jump to CONTINUE_INPUT

IS_DIGIT:
    cmp al, 20h       ; Compare AL with space character
    je STORE1         ; If space, jump to STORE1
    cmp al, 0Dh       ; Compare AL with carriage return (Enter key)
    je STORE1         ; If Enter key, jump to STORE1
    cmp al, '0'       ; Compare AL with '0'
    jb DELETE_SYMBOL  ; If less than '0', jump to DELETE_SYMBOL
    cmp al, '9'       ; Compare AL with '9'
    ja DELETE_SYMBOL  ; If greater than '9', jump to DELETE_SYMBOL
    push ax           ; Push AX on the stack
    mov ax, 10        ; Set AX to 10
    mul bx            ; Multiply AX by BX
    pop bx            ; Pop the original value of AX from the stack
    sub bl, '0'       ; Convert the character to its numeric value
    xor bh, bh        ; Clear BH register
    add bx, ax        ; Update BX with the new value
    cmp si, -1        ; Compare SI with -1 (check if the number is negative)
    je CHECK_OTHER    ; If negative, jump to CHECK_OTHER
    cmp bx, 32767     ; Compare BX with 32767 (check for overflow)
    ja ERROR_INPUT1   ; If overflow, jump to ERROR_INPUT1
    jmp CONTINUE_INPUT ; Jump to CONTINUE_INPUT

DELETE_SYMBOL:
    mov dx, offset errorMessage  ; Load the offset address of errorMessage into DX
    push ax           ; Push AX on the stack
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    int 21h           ; Call DOS function to print the errorMessage
    pop ax            ; Pop the original value of AX from the stack
    mov dx, offset Array  ; Load the offset address of Array into DX
    xor bx, si        ; XOR BX with SI (clear BX if SI is -1)
    sub bx, si        ; Subtract SI from BX (convert negative to positive)
    xor si, si        ; Clear SI (reset sign flag)
    xor bx, bx        ; Clear BX
    cmp al, '0'       ; Compare AL with '0'
    jb OUTPUT_ARRAY   ; If less than '0', jump to OUTPUT_ARRAY
    cmp al, '9'       ; Compare AL with '9'
    ja OUTPUT_ARRAY   ; If greater than '9', jump to OUTPUT_ARRAY

OUTPUT_ARRAY:
    call ShowArray    ; Call the ShowArray procedure to display the array
    jmp CONTINUE_INPUT ; Jump to CONTINUE_INPUT

STORE1:
    cmp al, 0Dh       ; Compare AL with carriage return (Enter key)
    je STORE2         ; If Enter key, jump to STORE2
    cmp bx, 0         ; Compare BX with 0
    je CONTINUE_INPUT ; If zero, jump to CONTINUE_INPUT

STORE2:
    xor bx, si        ; XOR BX with SI (clear BX if SI is -1)
    sub bx, si        ; Subtract SI from BX (convert negative to positive)
    xor si, si        ; Clear SI (reset sign flag)
    cmp bx, 0         ; Compare BX with 0
    je STORE3         ; If zero, jump to STORE3
    mov [di], bx      ; Store BX in the array at DI
    add di, 2         ; Move DI to the next position in the array
    inc cx            ; Increment the array element counter
    cmp cx, 10        ; Compare CX with 10 (check if 10 elements are entered)  30!
    je OVER_INPUT     ; If 10 elements, jump to OVER_INPUT

STORE3:
    xor bx, bx        ; Clear BX
    cmp al, 0Dh       ; Compare AL with carriage return (Enter key)
    je BREAK          ; If Enter key, jump to BREAK

CHECK_OTHER:
    cmp bx, 32768     ; Compare BX with 32768 (check for overflow)
    ja ERROR_INPUT1   ; If overflow, jump to ERROR_INPUT1
    jmp CONTINUE_INPUT ; Jump to CONTINUE_INPUT

ERROR_INPUT1:
    mov dx, offset overflowMessage  ; Load the offset address of overflowMessage into DX
    push ax           ; Push AX on the stack
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    int 21h           ; Call DOS function to print the overflowMessage
    pop ax            ; Pop the original value of AX from the stack
    mov dx, offset Array  ; Load the offset address of Array into DX
    xor bx, si        ; XOR BX with SI (clear BX if SI is -1)
    sub bx, si        ; Subtract SI from BX (convert negative to positive)
    xor si, si        ; Clear SI (reset sign flag)
    xor bx, bx        ; Clear BX
    cmp al, '0'       ; Compare AL with '0'
    jb OUTPUT_ARRAY   ; If less than '0', jump to OUTPUT_ARRAY
    cmp al, '9'       ; Compare AL with '9'
    ja OUTPUT_ARRAY   ; If greater than '9', jump to OUTPUT_ARRAY

OVER_INPUT:
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    mov dx, offset overMessage  ; Load the offset address of overMessage into DX
    int 21h           ; Call DOS function to print the overMessage
    jmp BREAK         ; Jump to BREAK

CONTINUE_INPUT1:
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    mov dx, offset continueMessage  ; Load the offset address of continueMessage into DX
    int 21h           ; Call DOS function to print the continueMessage
    mov dx, offset Array  ; Load the offset address of Array into DX
    xor bx, si        ; XOR BX with SI (clear BX if SI is -1)
    sub bx, si        ; Subtract SI from BX (convert negative to positive)
    xor si, si        ; Clear SI (reset sign flag)
    xor bx, bx        ; Clear BX
    jmp OUTPUT_ARRAY  ; Jump to OUTPUT_ARRAY

BREAK:
    cmp cx, 0         ; Compare CX with 0 (check if any elements were entered)
    je FIRST_INPUT    ; If no elements, jump to FIRST_INPUT
    cmp cx, 10        ; Compare CX with 10 (check if 10 elements were entered)
    jb CONTINUE_INPUT1  ; If less than 10, jump to CONTINUE_INPUT1
    mov [N], cx       ; Store the value of CX in the variable N
    mov ah, 09h       ; Set AH to 09h (function to print a string)
    mov dx, offset outputMessage  ; Load the offset address of outputMessage into DX 
    int 21h           ; Call DOS function to print the outputMessage
    mov cx, [N]       ; Load the value of N into CX (chastich sum in BX perenos in DI)
    mov dx, offset Array  ; Load the offset address of Array into DX
    call ShowArray    ; Call the ShowArray procedure to display the array
    mov cx, [N]       ; Load the value of N into CX
    mov si, offset Array  ; Load the offset address of Array into SI
    xor bx, bx        ; Clear BX
    xor di, di        ; Clear DI

FOR:
    lodsw            ; Load a 16-bit integer from the array to AX
    cwd              ; Sign-extend AX into DX:AX
    add bx, ax       ; Add AX to BX
    adc di, dx       ; Add DX to DI with carry
    loop FOR         ; Loop until all array elements are processed
    mov dx, di       ; Move the result (sum) to DX
    mov ax, bx       ; Move the result (sum) to AX
    idiv [N]         ; Divide the sum by N; quotient in AX, remainder in DX    
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
    mov ah, 09h       ; Set AH to 09h (function to print a string)

END:
    mov ax, 4C00h     ; Set AX to 4C00h (function to terminate the program)
    int 21h           ; Call DOS function to terminate the program
main endp           ; End of the procedure
end main