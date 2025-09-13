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
    mov di, offset buffer
    mov cx, BUFFER_SIZE

    ; Read string from the keyboard
read_input:
    mov ah, 01h         ; read character from STDIN
    int 21h
    cmp al, 0Dh         ; check for Enter key
    je done_input
    mov [di], al
    inc di
    loop read_input

done_input:
    ; Output appropriate message based on the input condition
    cmp cx, 0         ; check for buffer fill condition
    je max_input_reached

    print_string input_ended

max_input_reached:
    ; Sorting words in the entered string 
    print_string sorting_prompt

    lea si, buffer

    ; Bubble Sort to Sort Words
bubble_sort:
    lea di, si            ; set destination index to source index

    next_char:
    lodsb
    or al, al
    jz done_sorting

    cmp al, ' '           ; check for space (end of word)
    je check_word

    jmp next_char

    check_word:
    lodsb
    or al, al
    jz done_sorting

    cmp al, ' '           ; check for end of the string
    je done_sorting

    ; Sorting logic
    mov ah, 0              ; reset word length counter
    mov cx, 0

    count_word:
    lodsb
    cmp al, ' '            ; check for space
    jz compare_words

    inc ah                 ; increment word length counter
    jmp count_word

    compare_words:
    mov cl, ah              ; load word length to cx
    sub di, ax              ; move the destination index to the start of the word
    dec di

    next_char_comparison:
    inc di                   ; move to the next character in the word
    lodsb                    ; load character from the word
    mov dl, [di]             ; load character from the word for comparison
    cmp al, dl               ; compare characters
    jae no_swap              ; if no swap is needed, jump to next character comparison

    xchg al, dl              ; swap characters
    mov [di], dl             ; store character in the word
    dec di                   ; move back to previous character
    loop next_char_comparison

    no_swap:
    inc di                   ; move to the next character in the string
    cmp al, ' '              ; check for the end of the word
    jnz next_char            ; if not the end of the word, jump to the next character
    jmp next_char            ; if end of the word, jump to the next character in the string

    done_sorting:
    ; Output the sorted string
    mov dx, offset buffer
    mov ah, 09h
    int 21h

    ; Ending the program
    mov ah, 4Ch
    int 21h
main endp

end start
