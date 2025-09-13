.MODEL small
.STACK 100h
.DATA
    BUFFER_SIZE EQU 200
    buffer db BUFFER_SIZE dup(0)
    input_prompt db "Enter a string of up to 200 characters (press Enter to finish input): $"
    sorting_prompt db "Sorting...$"
    newline db 0Dh, 0Ah, "$"
    max_input db "Maximum input size reached. Processing input...$"
    input_ended db "Input ended. Sorting the provided input...$"

.CODE
print_string macro str  ; a macro to print a string
    mov ah, 09h          ; load the function responsible for string output
    mov dx, offset str   ; load the address of the string
    int 21h             ; call function 9h
endm

input proc
    mov ah, 0Ah          ; read a buffer
    int 21h
    ret
input endp

main proc
start:
    mov ax, @data
    mov ds, ax

    print_string input_prompt

    mov si, offset buffer

    ; Read string from the keyboard
read_input:
    mov ah, 01h         ; read character from STDIN
    int 21h
    cmp al, 0Dh         ; check for Enter key
    je done_input
    mov [si], al
    inc si
    loop read_input

done_input:
    ; Output appropriate message based on the input condition
    print_string input_ended

    ; Sorting words in the entered string 
    print_string sorting_prompt

    lea si, buffer

    ; Bubble Sort to Sort Words
bubble_sort:
    mov cx, 0           ; initialize word counter
    mov bx, 0           ; initialize sorted word counter

sort_loop:
    lodsb
    or al, al
    jz end_of_string

    cmp al, ' '
    je check_sorted

    inc cx
    jmp sort_loop

check_sorted:
    cmp cx, 0
    jbe skip_sorting

    inc bx               ; Increment the counter for sorted words

    ; Bubble Sort for the word
    mov bx, cx            ; set word length to BX
    dec bx                ; adjust for zero-based indexing

next_word_char:
    lea di, si            ; reset destination index to source index
    mov cx, bx            ; set word length to CX

inner_loop:
    lodsb
    cmp al, ' '
    je skip_swap          ; skip spaces within the word
    mov dl, [di]
    cmp al, dl
    jae skip_swap
    xchg al, [di]
    stosb
    dec di

    cmp cx, 0            ; check if word length is zero
    je word_sorted

    loop inner_loop

word_sorted:
    add si, cx  ; Move the pointer to the next word
    inc si      ; Skip the space between words

    cmp si, offset buffer + BUFFER_SIZE ; Check if we've reached the end of the entire string
    jae end_of_string

    jmp bubble_sort  ; Continue sorting the next word   ; Jump back to the outer loop

skip_swap:
    ; Continue with the sorting process...

skip_sorting:
    jcxz end_of_string  ; Check if CX is zero to end the sorting loop
    jmp bubble_sort     ; Continue sorting if not all words are sorted

end_of_string:
    ; Output the sorted string
    mov dx, offset buffer
    mov ah, 09h
    int 21h

    ; Ending the program
    mov ah, 4Ch
    int 21h

main endp

end start
