.model small
.stack 100h

.data
    array db 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ; sorted array
    array_size equ 10
    target db 7 ; element we are searching for

.code
start:
    mov ax, @data
    mov ds, ax

    mov al, target ; value we are searching for
    mov bx, 0 ; index of the beginning of the array
    mov cx, array_size ; size of the array
    dec cx ; decrease by 1 since indices start from 0

    ; call the binary search procedure
    call BinarySearch

    ; exit the program
    mov ah, 4Ch
    int 21h

BinarySearch proc
    mov si, bx ; si - index of the beginning of the array
    mov di, cx ; di - index of the end of the array

SearchLoop:
    cmp si, di ; check if indices have crossed each other
    jg NotFound ; if crossed, element not found

    ; calculate the index of the middle
    mov bx, si
    add bx, di
    shr bx, 1 ; divide by 2

    mov al, array[bx] ; load the element from the middle of the array

    cmp al, target ; compare with the target element
    je Found ; if equal, element found
    jb LessThanTarget ; if less, search in the right half
    ja GreaterThanTarget ; if greater, search in the left half

LessThanTarget:
    inc si ; shift the start of the range to the right
    jmp SearchLoop

GreaterThanTarget:
    dec di ; shift the end of the range to the left
    jmp SearchLoop

Found:
    ; convert the index to ASCII and print it
    mov ah, 02h
    add bx, '0' ; convert the index to ASCII
    mov dl, bl  ; move the ASCII code to dl (use bh, not bl)
    int 21h  
    
    ;mov ah, 02h
    ;mov al, bh  ; move the ASCII code to al (use bh, not bl)
    ;add al, '0' ; convert the index to ASCII
    ;mov dl, al  ; move the ASCII character to dl
    ;int 21h   
    
    ;mov ah, 02h
    ;mov bh, 0       ; clear bh to use it for division later
    ;mov bl, 10      ; set bl to 10 for division
    ;div bl          ; divide bx by 10, result in al (ASCII digit), remainder in ah
    ;add ah, '0'     ; convert the remainder to ASCII
    ;int 21h

    ; print additional message
    mov ah, 02h
    mov dl, 't'
    int 21h

    mov ah, 02h
    mov dl, 'h'
    int 21h

    mov ah, 02h
    mov dl, ' '
    int 21h

    ; exit the program
    mov ah, 4Ch
    int 21h


NotFound:
    ; print a message indicating the absence of the element
    mov ah, 09h
    lea dx, not_found_msg
    int 21h

    ; exit the program
    mov ah, 4Ch
    int 21h

not_found_msg db 'Element not found.$'

BinarySearch endp

end start
