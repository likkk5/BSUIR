.model small

org 100h

.data
length equ 200      ; Maximum length of the entered string
buffLength equ 203  ; Buffer length
startMessage0 db 'This program sort the words in a string alphabetically.$'
message1 db 0dh,0ah,'Enter the string: $'
message2 db 0dh,0ah,'Sorted string: $'
buff db buffLength dup(?)  ; Buffer to store the entered string, allocated with size buffLength
lengthString dw 0000h  ; Variable to store the length of the entered string, initialized to 0

.code
START:  ; Entry point of the program
mov dx, offset startMessage0  ; Load the address of startMessage0 into DX (display program starting message)
mov ah, 09h  ; Set AH register to 09h (display string function)
int 21h  ; Call interrupt 21h to display the message

BEGIN:  ; Label marking the beginning of program execution
mov lengthString, 0000h  ; Initialize the length of the entered string to zero

START_INPUT:  ; Label for initiating user input process
mov dx, offset message1  ; Load the address of message1 into DX (display string input prompt)
mov ah, 09h  ; Set AH register to 09h (display string function)
int 21h  ; Call interrupt 21h to display the message
mov cx, length  ; Set the counter CX to the maximum length allowed for input

FIRST_INPUT:  ; Label to mark the initial character input phase
mov si, 00h  ; Set SI register to 00h (initial position in the buffer)
mov ah, 01h  ; Set AH register to 01h (read a character from the standard input)
int 21h  ; Trigger interrupt 21h to read a character from the input
cmp al, 20h  ; Compare the entered character with space (ASCII code 20h)
je FIRST_INPUT  ; If the character is a space, continue input (skip spaces)
cmp al, 0Dh  ; Compare the entered character with carriage return (ASCII code 0Dh)
je END_INPUT  ; If the character is a carriage return (Enter), end the input process
cmp al, 08h  ; Compare the entered character with backspace (ASCII code 08h)
je DELETE_INPUT  ; If the character is a backspace, jump to the code handling backspace
mov buff[si], al  ; Store the entered character in the buffer at the current position (SI)
dec cx  ; Decrease the counter representing the remaining available characters in the string

INPUT:  ; Label for continuing input after the first character
inc si  ; Increment SI to move to the next position in the buffer
inc lengthString  ; Increment the string length counter
mov ah, 01h  ; Set AH register to 01h (read a character from standard input)
int 21h  ; Trigger interrupt 21h to read a character from input
cmp al, 20h  ; Compare the entered character with space (ASCII code 20h)
je DELETE_SPACE  ; If it's a space, jump to the code handling space deletion
.inputConti:  ; Label for continuing the input process
cmp al, 0Dh  ; Compare the entered character with carriage return (ASCII code 0Dh)
je END_INPUT  ; If it's a carriage return (Enter), end the input process
cmp al, 08h  ; Compare the entered character with backspace (ASCII code 08h)
je DELETE_INPUT  ; If it's a backspace, jump to the code handling backspace
mov buff[si], al  ; Store the entered character in the buffer at the current position (SI)
loopne INPUT  ; Loop until all characters are read or the maximum length is reached
inc si  ; Move to the next position in the buffer
jmp END_INPUT  ; Jump to the code for ending the input process

DELETE_SPACE:  ; Label for handling space deletion
cmp buff[si-1],' '  ; Compare the previous character in the buffer with a space
jne .inputConti  ; If it's not a space, jump to continue input
dec si  ; Decrement SI to remove the space
dec lengthString  ; Decrement the string length counter
jmp INPUT  ; Jump back to continue the input process

DELETE_INPUT:  ; Label for handling backspace deletion
cmp si, 00h  ; Compare the current position in the buffer with 00h (start of the string)
je FIRST_INPUT  ; If it's at the beginning, jump to the initial input stage
dec si  ; Move SI back by 1 to simulate backspace
dec si  ; Move SI back again to delete the character
inc cx  ; Increment the available characters count
dec lengthString  ; Decrement the string length counter
jmp INPUT  ; Jump back to continue the input process

END_INPUT:  ; Label for ending the input process
mov buff[si],' '  ; Add a space at the current position in the buffer
mov buff[si + 1],00h  ; Add a null character after the space
mov buff[si + 2],00h  ; Add another null character for safety
mov si,00h  ; Reset SI to the beginning of the buffer

SORT_BEGIN:  ; Label marking the beginning of the sorting process
mov dl, 00h  ; Load DL register with 00h (end-of-string marker)
mov cx, length  ; Load CX register with the maximum length allowed for input
lea di, buff  ; Load the address of the buffer into DI register
mov al, 20h  ; Load AL register with 20h (ASCII value for space)
repne scasb  ; Scan the buffer for the space character, decrementing CX if found
lea bx, buff  ; Load the address of the buffer into BX register

WORD:  ; Label for handling individual words
cmp ds:[di+1], 00h  ; Compare the next character in the buffer with the end-of-string marker
je END_TEST  ; If it's the end of the string, jump to the end of the word comparison
push di  ; Save the current address in the stack
mov ax, di  ; Move the address to AX register
push ax  ; Push the address to the stack
mov cx, length  ; Reset the character count to the maximum length
mov al, 20h  ; Set AL to 20h (ASCII space)
repne scasb  ; Scan the buffer for space, decrementing CX if found
pop ax  ; Restore the original address to AX
cmp cx, 00h  ; Compare the character count with 0
je END_TEST  ; If the character count is 0, jump to the end of the word comparison
push di  ; Save the current address to the stack
sub di, ax  ; Calculate the end of the second word (DI - end of word 2, AX - end of word 1)
sub ax, bx  ; Calculate the end of the first word (AX - end of word 1, BX - start of word 1)
jmp ACOMPARISON  ; Jump to the comparison of the two words

CONTINUE_WORD:  ; Label to continue the word comparison process
pop dx  ; Restore the value from DX
pop di  ; Restore the value from DI
pop bx  ; Restore the value from BX
jmp WORD  ; Jump back to the WORD label to continue word comparison

ACOMPARISON:  ; Label for word comparison
push dx  ; Store the value in DX onto the stack
push di  ; Store the value in DI onto the stack
mov di, bx  ; Move the value of BX into DI
push di  ; Store the value of DI onto the stack
push ax  ; Store the value in AX onto the stack
add ax, bx  ; Add the value of BX to AX
mov di, ax  ; Move the result into DI
pop ax  ; Restore the value in AX
mov bl, [di]  ; Move the value at DI into BL
pop di  ; Restore the value in DI
mov dl, [di]  ; Move the value at DI into DL
pop di  ; Restore the value in DI
cmp dl, bl  ; Compare the values in DL and BL
je ESPES_EVENT  ; If they are equal, jump to ESPES_EVENT
ja REPLACE  ; If DL > BL, jump to REPLACE
jmp CONTINUE_WORD  ; Otherwise, jump back to CONTINUE_WORD for further comparison 

ESPES_EVENT:  ; Label for a special event during comparison
pop dx  ; Restore the value from DX
push dx  ; Save the value in DX
push di  ; Save the value in DI
inc bx  ; Increment the value in BX
mov di, bx  ; Move the value of BX to DI
push di  ; Save the value of DI
push ax  ; Save the value in AX
add ax, bx  ; Add the value in BX to AX
mov di, ax  ; Move the result to DI
pop ax  ; Restore the value in AX
mov bl, [di]  ; Move the value at DI into BL
pop di  ; Restore the value in DI
inc di  ; Increment the value in DI
mov dl, [di]  ; Move the value at DI into DL
pop di  ; Restore the value in DI
cmp dl, bl  ; Compare the values in DL and BL
je ACOMPARISON  ; If they are equal, jump to ACOMPARISON
ja REPLACE  ; If DL > BL, jump to REPLACE
jmp CONTINUE_WORD  ; Otherwise, jump back to CONTINUE_WORD for further comparison

END_TEST:  ; Label for the end comparison
cmp dl, 00h  ; Compare the value in DL with 00h (end-of-string marker)
je END_SORT  ; If it's the end of the string, jump to the end of sorting
jmp SORT_BEGIN  ; Otherwise, jump back to the start of sorting

REPLACE:  ; Label for replacing characters in the sorting process
pop dx  ; Restore the value from DX
mov dl, 01h  ; Set DL to 01h
mov cx, ax  ; Move the value of AX to CX
pop di  ; Restore the value from DI
pop bx  ; Restore the value from BX
sub bx, ax  ; Subtract the value in AX from BX
sub di, ax  ; Subtract the value in AX from DI
push di  ; Save the value in DI
add di, ax  ; Add the value in AX to DI

CYCLIC_SHIFT_ITERATION:  ; Label for iterating the cyclic shift process
push cx  ; Save the value in CX onto the stack
mov cx, di  ; Move the value of DI to CX
sub cx, bx  ; Subtract the value in BX from CX
dec cx  ; Decrement the value in CX
mov si, bx  ; Move the value in BX to SI
dec di  ; Decrement the value in DI
mov al, ds:[si]  ; Move the value at memory location SI to AL

ITER:  ; Label for iteration process
mov ah, ds:[si+1]  ; Move the value at memory location (si+1) to AH
mov ds:[si], ah  ; Move the value in AH to the memory location (SI)
inc si  ; Increment SI to point to the next memory location
loopne ITER  ; Loop through ITER while CX register is not zero or until the condition is met
mov ds:[si], al  ; Move the value in AL to the memory location (SI)
inc di  ; Increment DI to point to the next memory location
pop cx  ; Restore the value from the stack into CX
loopne CYCLIC_SHIFT_ITERATION  ; Loop through CYCLIC_SHIFT_ITERATION while CX is not zero

pop bx  ; Restore the value from the stack into BX
cmp ds:[di], '$'  ; Compare the value at memory location DI with '$'
je END_TEST  ; If it's the end marker '$', jump to the end of the test
jmp WORD  ; Otherwise, jump to the label WORD to continue the process

END_SORT:  ; Label marking the end of the sorting process
mov dx, offset message2  ; Load the offset of message2 into DX (display sorted string message)
mov ah, 09h  ; Set AH register to 09h (display string function)
int 21h  ; Trigger interrupt 21h to display the sorted string message

mov ch, 00h  ; Set CH register to 00h
mov cl, length  ; Move the length to the CL register

mov ah, 02h  ; Set AH register to 02h (character output function)
mov si, 00h  ; Set SI register to 0
dec si  ; Decrement SI by 1

.spaceClear:  ; Label for clearing space characters
inc si  ; Increment SI
cmp buff[si], ' '  ; Compare the value at memory location SI with ' '
je .spaceClear  ; If it's a space, continue clearing

.writeString:  ; Label for writing characters to output
cmp buff[si], 00h  ; Compare the value at memory location SI with 00h (end-of-string marker)
je .endWrite  ; If it's the end, jump to the end of writing

mov dl, buff[si]  ; Move the value at memory location SI to DL
int 21h  ; Trigger interrupt 21h to display the character in DL
inc si  ; Increment SI
loop .writeString  ; Loop through .writeString

.endWrite:  ; Label marking the end of the writing process
mov cx, buffLength  ; Move the buffer length to CX
mov si, 0  ; Set SI to 0

BUFFCLEAR:  ; Label for clearing the buffer
mov buff[si], 00h  ; Set the value at memory location SI to 00h
inc si  ; Increment SI
loop BUFFCLEAR  ; Loop through BUFFCLEAR
jmp END  ; Jump to the END label

END:  ; Label marking the end of the program
mov ax, 4C00h  ; Set AX to 4C00h (exit program function)
int 21h  ; Trigger interrupt 21h to exit
end START  ; End the program and specify the starting label 