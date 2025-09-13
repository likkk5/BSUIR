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
    print_string max_input

    ; Sorting words in the entered string 
    print_string sorting_prompt

    lea si, buffer

    ; Word Sorting Algorithm
sort_words:
    lodsb                 ; load character into AL
    or al, al             ; check for end of string
    jz done_sorting

    ; Check for space to identify the start of a word
    cmp al, ' '
    je continue_sorting   ; skip spaces

    ; Collect word characters until space or end of string
    lea di, si            ; set destination index to source index
    collect_word:
    lodsb                 ; load next character
    or al, al
    jz word_sorted        ; end of string reached
    cmp al, ' '           ; check for space
    je word_sorted        ; end of word if space is found
    stosb                 ; store the character
    jmp collect_word      ; continue collecting characters of the word

    continue_sorting:
    jmp sort_words        ; continue to the next character

    word_sorted:
    ; Sorting words using Bubble Sort
    lea di, si            ; set destination index to source index
    next_word:
    lodsb                 ; load character to AL
    cmp al, [di]          ; compare character with the sorted part
    jb swap_words         ; jump if the character is less
    jmp skip_swap         ; continue comparison if not less

    swap_words:
    xchg al, [di]         ; swap characters
    stosb                 ; store character
    dec di                ; adjust the pointer

    skip_swap:
    cmp al, ' '           ; check for space (end of the word)
    je next_word          ; next word if space is found
    loop swap_words       ; repeat comparison until the end of the word

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