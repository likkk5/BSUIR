.model small
.stack 100h
.data
    string dw "abcdcba$"
    len equ $-string 
    msg_palindrome db "The string is a palindrome", "$"
    msg_not_palindrome db "The string is not a palindrome", "$"   
   
.code
main:
    mov ax, @data
    mov ds, ax 

    mov si, string[0]
    mov di, string[len - 1]
     
    check_palindrome:
        cmp si, di
        jae is_palindrome
        mov al, [si]
        mov ah, [di]
        cmp al, ah
        jne not_palindrome
        inc si
        dec di
        jmp check_palindrome
    is_palindrome:
        mov ah, 09h
        lea dx, msg_palindrome
        int 21h
        jmp exit_program
    not_palindrome:
        mov ah, 09h
        lea dx, msg_not_palindrome
        int 21h

    exit_program:
        mov ah, 4ch
        int 21h

end main

end main