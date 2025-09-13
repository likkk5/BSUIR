.MODEL small
.STACK 100h
.DATA
    MAX_STRING_SIZE EQU 199
    MAX_BUFFER_SIZE EQU MAX_STRING_SIZE + 1
    str db MAX_STRING_SIZE dup(0)
    buffer db MAX_BUFFER_SIZE dup(0)
    input_prompt db "Enter string (200): $"
    sorting_prompt db "Sorting...$"
    newline db 0Dh, 0Ah, "$"

.CODE
print_message macro out_str ;a macro to print messages
    mov ah, 09h ;load the number of function responsible for string's output
    mov dx, offset out_str ;load the address of the string
    int 21h ;call function 9h
endm

input proc
    mov ah, 0Ah ;read a buffer
    int 21h
    ret
input endp

main proc
start:
    mov ax, @data
    mov ds, ax

    print_message input_prompt
    lea dx, input_prompt
    call input

    ; enter string from keypad
    mov ah, 0Ah
    lea dx, buffer
    int 21h

    mov si, offset buffer
    mov di, offset str
    mov cx, MAX_STRING_SIZE
    rep movsb
    mov byte ptr [di], '$'

    print_message sorting_prompt

    lea si, str

next_word:
    mov al, [si]
    cmp al, '$'
    je done

    ; Bubble sort for sorting words
    mov bx, si
    find_end_of_word:
        cmp byte ptr [bx], ' '
        je found_end_of_word
        inc bx
        jmp find_end_of_word
    found_end_of_word:
        lea dx, [bx]

    lea di, [si]
    next_word_inner:
        mov cx, 0
        mov bx, si

    find_next_char:
        mov al, [bx]
        cmp al, ' '
        je found_end
        inc bx
        inc cx
        jmp find_next_char

    found_end:
        lea dx, [bx]

        lea di, [si]

    repeat_swap:
        mov al, [si]
        mov bh, [di]
        cmp al, ' '
        je done_repeat_swap
        cmp bh, ' '
        je done_repeat_swap
        cmp al, bh
        jae no_swap

    swap:
        mov al, [si]
        mov bh, [di]
        mov [si], bh
        mov [di], al

    no_swap:
        inc si
        inc di
        jmp repeat_swap

    done_repeat_swap:
        lea si, dx

        inc si
        jmp next_word_inner

    done:
        lea si, dx

    inc si
    jmp next_word

done_sorting:
    ; print sorted string
    mov ah, 09h
    lea dx, str
    int 21h

    ; ending
    mov ah, 4Ch
    int 21h
main endp

end start
