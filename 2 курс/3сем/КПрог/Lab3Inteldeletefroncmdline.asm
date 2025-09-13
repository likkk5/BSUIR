.model  small

.stack  100h

.data
    startMessage    db      'This program counts the number of lines in a file that contain all the entered',0dh,0ah,'characters.$'
    arg_string      db      255 dup(0)     
    filename_length dd      0
    fname           db      0Dh, 0Ah,0Dh, 0Ah, 'Your filename is: $'
    CrLf            db      0Dh, 0Ah, '$'
    inputMessage    db      0Dh, 0Ah,0dh,0ah,'You have not entered any characters to search for. Please enter. ', 0Dh, 0Ah,'$'
    dataMessage     db      0Dh, 0Ah,'File data: ', 0Dh, 0Ah,'$'
    errFileOpenRd   db      0dh,0ah,"File open (for read) - error, choose another one", '$'
    errFileOpenWr   db      0dh,0ah,"File open (for write) - error", '$'
    errFileRead     db      0dh,0ah,"File read - error", '$'
    errFileWrite    db      0dh,0ah,"File write - error", '$'
    errFileClose    db      0dh,0ah,"File close - error",0dh,0ah, '$'
    msgGetChar      db      0Dh, 0Ah,0dh,0ah,"Input symbols: ", '$'
    msgResult       db      0Dh, 0Ah,"Result: ", '$'
    msgFile         db      0Dh, 0Ah,"File exists", '$'
    againmsg        db      0Dh, 0Ah,"Do you want to continue? If yes press 1, on the other hand press 0: ", '$'
    deletemsg       db      0Dh, 0Ah,"Do you want to delete file? If yes press 1: ", '$'  
    del             db      0Dh, 0Ah,"File delete", '$'
    _BUFFER_SIZE_   equ     1024
    FileBuffer      db      _BUFFER_SIZE_ dup(?)
    Array           dw      50 dup(?)
    CopyArray       dw      50 dup(?)
    nBufLen         dw      ?
    nCount          dw      ?
    hFile           dw      ?
    cChar           db      ?
    bCheckOnce      dw      ? 
    finish_buffer   db      3 dup(0)
    delete_buffer   db      3 dup(0) 
    yes_length      dw      0   
    dlength         dw      0

;\trash.txt

.code                  ; Code section

ShowUInt16 proc        ; Procedure to display 16-bit numbers in the console
    mov  bx, 10        ; Set divisor to 10 (decimal system)
    mov  cx, 0         ; Initialize counter

DIVV:                   ; Division loop
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

PRINT macro out_str   ; Macro for displaying a string in the console
    mov  dx, offset out_str  ; Set DX to the offset of the output string
    mov  ah, 09h       ; Set AH to 09h (function for displaying a string)
    int  21h           ; Call interrupt 21h (output string)
endm PRINT             ; End of the PRINT macro

; Macro to reload based on user choice
RELOAD macro message, do1, do2
    PRINT message     ; Display the provided message
    mov  ah, 01h       ; Set AH to 01h (function for reading a character)
    int  21h           ; Call interrupt 21h (input character)
    cmp  al, 79h       ; Compare the input character with 'y'
    je   do1           ; Jump to do1 if equal
    cmp  al, 59h       ; Compare the input character with 'Y'
    je   do1           ; Jump to do1 if equal
    cmp  al, 6Eh       ; Compare the input character with 'n'
    je   do2           ; Jump to do2 if equal
    cmp  al, 4Eh       ; Compare the input character with 'N'
    je   do2           ; Jump to do2 if equal
endm RELOAD            ; End of the RELOAD macro

enter_line macro string, string_length; a macro to enter and save data 
    local enter_char ;declare local labels
    local return_line ;to avoid duplicate declarations
    mov si,0 ;load 0 to the counter
    mov dx,offset string ;load the string's adress into dx
    mov ah,1 ;load the number of function responsible for outputing a symbol
    int 21h ;call this function

enter_char:
    cmp al,13 ;compare the entered symbol with the symbol of carriage return
    je return_line ;if equal, it means that the line is already entered
    mov [string+si],al ;load the symbol into the string variable
    inc si ;increment the counter (string's length)
    int 21h ;call function number 2 for symbol's input
    jmp enter_char ;restart the same for a new entered symbol

return_line:
    mov [string_length],si ;load the counter into the length's variable
    mov ah,2
    mov dl,10
    int 21h
    mov dl,13
    int 21h
endm

main proc
    mov  ax, @data      ; Load the address of the data segment into AX
    mov  es, ax         ; Set ES to the data segment
    xor  cx, cx         ; Clear CX (counter) to zero
    mov  cl, [80h]      ; Load the value at memory location 80h into CL
    mov  si, 82h        ; Set SI to the memory location 82h
    lea  di, arg_string ; Load the effective address of arg_string into DI
    rep  movsb          ; Repeat the move string operation from SI to DI, CX times
    mov  ds, ax         ; Set DS to the data segment
    mov  [di-1], '$'    ; Replace the last character of arg_string with '$'
    PRINT startMessage  ; Display the start message
    PRINT fname         ; Display the filename message
    PRINT arg_string    ; Display the argument string
    mov  [di-1], 0      ; Replace the last character of arg_string with null terminator
    PRINT CrLf          ; Display a new line

BEGIN:
    mov  ah, 3Dh        ; Set AH to 3Dh (function for opening existing file)
    mov  al, 00h        ; Set AL to 00h (open file for reading)
    lea  dx, [arg_string] ; Load the effective address of arg_string into DX
    int  21h            ; Call interrupt 21h (DOS function)
    jnc  FILE_OPEN_OK   ; Jump to FILE_OPEN_OK if no carry flag (success)
    PRINT errFileOpenRd ; Display an error message for file open failure

FILE_OPEN_OK:
    mov  [hFile], ax    ; Save the file handle in hFile
    lea  si, [FileBuffer] ; Set SI to the effective address of FileBuffer
    mov  [nBufLen], 0   ; Initialize buffer length to zero
    mov  [nCount], 0    ; Initialize line count to zero
    PRINT msgGetChar    ; Display a message for getting characters
    mov  di, offset Array ; Set DI to the effective address of Array
    xor  cx, cx         ; Clear CX (counter) to zero
    xor  bx, bx         ; Clear BX (counter) to zero

INPUT:
    mov  ah, 01h        ; Set AH to 01h (function for reading a character)
    int  21h            ; Call interrupt 21h (DOS function)
    cmp  cx, 0          ; Compare the counter CX with zero
    je   CHECK_SYMBOLS  ; Jump to CHECK_SYMBOLS if equal
    cmp  al, 0Dh        ; Compare the input character with carriage return (Enter key)
    je   CONTINUE       ; Jump to CONTINUE if equal

CONTIN:
    mov  [di], al       ; Store the input character in Array
    push di             ; Push the current value of DI onto the stack
    mov  di, offset CopyArray ; Set DI to the effective address of CopyArray
    add  di, cx         ; Move DI to the next position based on the counter CX
    mov  [di], al       ; Store the input character in CopyArray
    pop  di             ; Pop the original value of DI from the stack
    inc  cx             ; Increment the counter
    add  di, 1          ; Move DI to the next position
    cmp  cx, 49         ; Compare the counter CX with 49
    ja   CONTINUE       ; Jump to CONTINUE if above (more than or equal to 49)
    jmp  INPUT          ; Jump to INPUT

CHECK_SYMBOLS:
    cmp  al, 0Dh        ; Compare the input character with carriage return (Enter key)
    jne  CONTIN         ; Jump to CONTIN if not equal
    PRINT inputMessage  ; Display a message for missing search characters
    jmp  INPUT          ; Jump to INPUT

CONTINUE:
    push cx             ; Push the current value of CX onto the stack
    PRINT CrLf          ; Display a new line
    PRINT dataMessage   ; Display a message for file data

WHILE:
    cmp  [nBufLen], 0   ; Compare buffer length with zero
    jnz  GETC           ; Jump to GETC if not zero
    mov  ah, 3Fh        ; Set AH to 3Fh (function for reading from a file)
    mov  bx, [hFile]    ; Load the file handle into BX
    mov  cx, _BUFFER_SIZE_ ; Load the buffer size into CX
    lea  dx, [FileBuffer] ; Load the effective address of FileBuffer into DX
    int  21h            ; Call interrupt 21h (DOS function)
    jnc  FILE_READ_OK   ; Jump to FILE_READ_OK if no carry flag (success)
    PRINT errFileRead   ; Display an error message for file read failure
    jmp  BREAK          ; Jump to BREAK

FILE_READ_OK:
    test ax, ax         ; Test if AX is zero (end of file)
    jz   BREAK          ; Jump to BREAK if zero
    mov  [nBufLen], ax  ; Save the buffer length
                 
GETC:
    lodsb              ; Load a byte from SI to AL, incrementing SI
    dec  [nBufLen]     ; Decrement the buffer length
    mov  di, offset Array ; Set DI to the effective address of Array
    pop  cx            ; Pop the current value of CX from the stack
    push dx            ; Push the current value of DX onto the stack
    xor  dx, dx        ; Clear DX (counter) to zero

CHECK_EQUAL:
    inc  dx            ; Increment DX (counter)
    cmp  al, [di]      ; Compare the current character with the one in Array
    jne  CHECK_5       ; Jump to CHECK_5 if not equal
    push di            ; Push the current value of DI onto the stack
    mov  di, offset CopyArray ; Set DI to the effective address of CopyArray
    add  di, dx        ; Move DI to the next position based on the counter DX
    dec  di            ; Move DI back by one
    cmp  [di], 0       ; Compare the character in CopyArray with null terminator
    je   SKIP          ; Jump to SKIP if equal
    mov  [di], 0       ; Replace the character in CopyArray with null terminator
    pop  di            ; Pop the original value of DI from the stack
    jmp  CHECK_NEW_LINE ; Jump to CHECK_NEW_LINE

SKIP:
    pop  di            ; Pop the current value of DI from the stack

CHECK_5:
    add  di, 1         ; Move DI to the next position
    cmp  cx, dx        ; Compare CX with DX
    jne  CHECK_EQUAL   ; Jump to CHECK_EQUAL if not equal

CHECK_NEW_LINE:
    pop  dx            ; Pop the original value of DX from the stack
    push cx            ; Push the current value of CX onto the stack

NEXT:
    mov  ah, 02h       ; Set AH to 02h (function for displaying a character)
    mov  dl, al        ; Load the current character into DL
    int  21h           ; Call interrupt 21h (DOS function)
    cmp  al, 0Dh       ; Compare the current character with carriage return (Enter key)
    je   TUT           ; Jump to TUT if equal
    cmp  al, 0h        ; Compare the current character with null terminator
    je   TUT           ; Jump to TUT if equal
    jmp  WHILE         ; Jump to WHILE

TUT:
    pop  cx            ; Pop the current value of CX from the stack
    mov  bx, cx        ; Move the current value of CX to BX
    push cx            ; Push the current value of CX onto the stack
    xor  dx, dx        ; Clear DX (counter) to zero
    push di            ; Push the current value of DI onto the stack
    mov  di, offset CopyArray ; Set DI to the effective address of CopyArray

CHK:
    cmp  [di], 0       ; Compare the character in CopyArray with null terminator
    jne  NADDIT        ; Jump to NADDIT if not equal

ADDIT:
    inc  dx            ; Increment DX (counter)
    add  di, 1         ; Move DI to the next position
    dec  bx            ; Decrement BX (counter)
    cmp  bx, 0         ; Compare BX with zero
    jne  CHK           ; Jump to CHK if not equal
    jmp  CHK1          ; Jump to CHK1

NADDIT:
    jmp  CONT          ; Jump to CONT

CHK1:
    cmp  cx, dx        ; Compare CX with DX
    jne  CONT          ; Jump to CONT if not equal
    inc  [nCount]      ; Increment the line count

CONT:
    pop  di            ; Pop the original value of DI from the stack
    pop  cx            ; Pop the original value of CX from the stack
    mov  bx, cx        ; Move the original value of CX to BX
    push cx            ; Push the original value of CX onto the stack

copyproc:
    mov  di, [Array]   ; Move the value at the effective address of Array to DI
    mov  [CopyArray], di ; Copy the value in DI to CopyArray
    add  Array, 1      ; Move to the next position in Array
    add  CopyArray, 1  ; Move to the next position in CopyArray
    dec  cx            ; Decrement CX (counter)
    cmp  cx, 0         ; Compare CX with zero
    jne  copyproc      ; Jump to copyproc

    pop  cx            ; Pop the original value of CX from the stack
    mov  bx, cx        ; Move the original value of CX to BX
    push cx            ; Push the original value of CX onto the stack

copyproc2:
    dec  Array         ; Decrement Array
    dec  CopyArray     ; Decrement CopyArray
    dec  cx            ; Decrement CX (counter)
    cmp  cx, 0         ; Compare CX with zero
    jne  copyproc2     ; Jump to copyproc2
    jmp  WHILE         ; Jump to WHILE

BREAK:
    mov  ah, 3Eh       ; Set AH to 3Eh (function for closing a file)
    mov  bx, [hFile]   ; Load the file handle into BX
    int  21h           ; Call interrupt 21h (DOS function)
    jnc  SHOW_RESULT   ; Jump to SHOW_RESULT if no carry flag (success)
    PRINT errFileClose ; Display an error message for file close failure
   
SHOW_RESULT:
    PRINT msgResult    ; Display a message for the result
    mov  ax, [nCount]  ; Load the line count into AX
    call ShowUInt16    ; Call the ShowUInt16 procedure to display AX as a number

delete_error:
   PRINT deletemsg
   enter_line   delete_buffer, dlength
   cmp dlength, 1
   jne delete_error
   mov si,0
   cmp [delete_buffer+si],'1'        
   jne  check_zero1
   jmp  DELETE 
check_zero1:
   cmp [delete_buffer+si], '0'
   je finish_error
   jne delete_error         
    
DELETE:
   mov ah, 3Eh
   mov bx, 5   
   int 21h 
   mov ah, 41h
   mov dx, offset arg_string 
   int 21h 
   PRINT del

finish_error:
   PRINT againmsg
   enter_line   finish_buffer, yes_length
   cmp yes_length, 1
   jne finish_error
   mov si,0
   cmp [finish_buffer+si],'1'        
   jne  check_zero
   jmp  BEGIN 
check_zero:
   cmp [finish_buffer+si], '0'
   je END
   jne finish_error
   
END:
    mov  ax, 4C00h     ; Set AX to 4C00h (function for program termination)
    int  21h           ; Call interrupt 21h (DOS function)
main endp              ; End of the main procedure

end main              ; End of the program