.model small
.stack 100h

 .data
    msg db 'radar$'
    msg_len equ $ - msg

    palindrome_msg db 'The string is a palindrome.$'
    not_palindrome_msg db 'The string is not a palindrome.$'

    buffer dw 256 dup(?)
    reversed_buffer dw 256 dup(?)

.code

start:
    ; Copy the constant string to the buffer
    mov si, 0
    mov di, buffer
copy_constant:
    mov al, [msg + si]
    cmp al, '$'
    je end_copy_constant
    mov [di], al
    inc si
    inc di
    jmp copy_constant
end_copy_constant:

    ; Calculate string length
    mov si, buffer
    mov cx, 0
find_length:
    cmp byte [si], 0
    je end_find_length
    inc si
    inc cx
    jmp find_length
end_find_length:

    ; Copy the original string to reversed_buffer in reverse order
    mov si, cx
    mov di, 0 
    
copy_reverse:
    cmp si, 0
    je end_copy_reverse
    dec si
    mov al, [buffer + si]
    mov [reversed_buffer + di], al
    inc di
    jmp copy_reverse
end_copy_reverse:

    ; Compare the original string with the reversed string
    mov si, 0
    mov di, 0
compare_strings:
    cmp si, cx
    je strings_match
    mov al, [buffer + si]
    mov bl, [reversed_buffer + di]
    cmp al, bl
    jne strings_differ
    inc si
    inc di
    jmp compare_strings

strings_match:
    ; Display "The string is a palindrome"
    mov ah, 09h         ; DOS function to print a string
    lea dx, [palindrome_msg]
    int 21h             ; Call DOS
    jmp exit_program

strings_differ:
    ; Display "The string is not a palindrome"
    mov ah, 09h         ; DOS function to print a string
    lea dx, [not_palindrome_msg]
    int 21h             ; Call DOS

exit_program:
    ; Exit the program
    mov ah, 4Ch         ; DOS function to terminate program
    int 21h             ; Call DOS
 end start