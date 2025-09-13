.model small
org 100h 

.data
    matrix_size equ 3 
    matrix db matrix_size * matrix_size dup(?) 
    newline db 0Dh, 0Ah, '$' ; newline characters for printing

.code  
start:
    mov ax, @data
    mov ds, ax
    mov si, 0 

    mov cx, matrix_size
input_loop_row:
    mov dx, si
    mov ah, 09h
    int 21h 

    mov cx, matrix_size
input_loop_column:
    mov ah, 01h
    int 21h 
    sub al, '0' 
    mov [matrix + si], al 
    inc si
    loop input_loop_column

    mov dx, offset newline
    mov ah, 9
    int 21h

    inc dx 
    loop input_loop_row

    mov si, 0
    mov cx, matrix_size

sort_diagonal:
    mov di, si
    add di, matrix_size + 1 
    mov al, [matrix + si]
    mov ah, [matrix + di]
    cmp al, ah
    jge not_swap

    mov al, [matrix + si]
    mov ah, [matrix + di]
    mov [matrix + di], al
    mov [matrix + si], ah

not_swap:
    inc si
    loop sort_diagonal

    mov dx, offset newline
    mov ah, 9
    int 21h

    mov si, 0
    mov cx, matrix_size

output_loop_row:
    mov dx, si 
    mov ah, 09h
    int 21h 

    mov cx, matrix_size
output_loop_column:
    mov al, [matrix + si]
    add al, '0'
    mov ah, 02h
    int 21h 

    inc si
    loop output_loop_column

    mov dx, offset newline
    mov ah, 9
    int 21h

    inc dx 
    loop output_loop_row

    mov ah, 4Ch
    int 21h


end start
