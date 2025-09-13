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
    sorted_string db BUFFER_SIZE dup(0)

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

    ; Read string from keyboard
read_input:
    mov ah, 01h         ; read character from STDIN
    int 21h
    cmp al, 0Dh         ; check for Enter key
    je done_input
    mov [di], al
    inc di
    loop read_input

done_input:
    ; Output appropriate message based on input condition
    cmp cx, 0         ; check for buffer fill condition
    je max_input_reached

    print_string input_ended

max_input_reached:
    print_string max_input

    ; Bubble sort the input string 
    print_string sorting_prompt

    lea si, buffer
    lea di, sorted_string
    mov cx, BUFFER_SIZE

sort_words:
    lodsb
    or al, al
    jz done_sorting
    cmp al, ' '  ; Check for space to identify the start of a word
    je next_char  ; Skip spaces
    stosb

    ; Inner loop for sorting each word
inner_loop:
    lodsb
    or al, al
    jz word_sorted
    stosb

    ; Compare characters to sort words
    cmp al, [di]
    jb swap_chars  ; Jump if the character is less for swapping
    loop inner_loop
    jmp next_char

swap_chars:
    xchg al, [di]
    stosb
    loop inner_loop
    jmp next_char

word_sorted:
    mov byte ptr [di], ' '  ; Space between sorted words
    inc di
    jmp sort_words

next_char:
    jmp sort_words

done_sorting:
    mov byte ptr [di], '$'   ; Adding the end of string marker

    ; Output the sorted string directly
    mov dx, offset sorted_string
    mov ah, 09h
    int 21h

    ; Ending the program
    mov ah, 4Ch
    int 21h
main endp

end start
