.model small
.stack 100h

.data
    matrix  dw 9, 7, 5, 6, 8, 4, 3, 1, 2  ; 3x3 matrix

.code   
start:
    mov si, matrix      ; SI points to the beginning of the matrix
    mov cx, 3           ; Number of elements in each row of the matrix

outer_loop:
    mov di, si           ; DI will be used for the inner loop

    ; Sort the main diagonal
    mov cx, 2            ; Number of elements on the diagonal
    add di, 2            ; Increase DI by the size of an element (2 bytes)

diagonal_loop:
    mov ax, [di]        ; Load the current element into AX
    mov bx, di
    sub bx, 4            ; Address of the previous element on the diagonal

    cmp ax, [bx]         ; Compare with the previous element on the diagonal
    jge next_iteration   ; If the current element is greater or equal, go to the next iteration

    ; Swap the elements
    xchg ax, [di]
    xchg ax, [bx]
    mov [di], ax

next_iteration:
    sub di, 4            ; Move to the previous element on the diagonal
    loop diagonal_loop

    add si, 6            ; Move to the next row of the matrix
    loop outer_loop

    ; Display the sorted matrix
    mov si, matrix
    mov cx, 9            ; Total number of elements in the matrix

print_matrix:
    mov ax, [si]
    call print_number
    add si, 2
    loop print_matrix

    int 20h  ; End the program

print_number:
    ; Print a number in ASCII format
    push ax
    push dx

    mov bx, 10
    xor dx, dx

divide_loop:
    div bx
    add dl, '0'
    push dx
    xor dx, dx
    test ax, ax
    jnz divide_loop

print_loop:
    pop dx
    ; Output the ASCII character
    mov ah, 02h
    int 21h

    cmp sp, 0  ; Check if there are more numbers in the stack
    jnz print_loop

    pop dx
    pop ax
    ret
end start