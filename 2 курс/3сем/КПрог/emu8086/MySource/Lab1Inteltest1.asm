.MODEL small
 org  100h
.STACK 300h
.DATA
    MAX_BUFFER_SIZE EQU 200
    MAX_STRING_SIZE EQU 199
    BUFFER_SIZE EQU MAX_BUFFER_SIZE + 1
    str db MAX_STRING_SIZE dup(0)
    buffer db BUFFER_SIZE dup(0)
    delimiter db "$"
    newline db 0Dh, 0Ah, "$"  
    
    input_prompt db "Enter string (200): $"
    sorting_prompt db "Sorting...$"  
    
.CODE  
print_message macro out_str ;a macro to print messages 
    mov ah,9 ;load the number of function responsible for string's output
    mov dx,offset out_str ;load the adress of string
    int 21h ;call function 9h
    mov ah,2 ;load the number of function responsible for outputing a symbol
    mov dl,10 ;ascii code of new line
    int 21h ;call function 2h
    mov dl,13 ;ascii code of carriage return
    int 21h ;call function 2h
endm   
input proc 
    mov ah,0Ah ;read a buffer
    int 21h
   ; new_line ;macro to go to the next line
    ret
input endp   

print_message input_prompt
lea dx,input_prompt
call input 

main proc
start:
mov ax, @data
    mov ds, ax

    ; inf about entering string
    mov ah, 09h
    lea dx, input_prompt
    int 21h

    ; enter string from keypad
    mov ah, 0Ah
    lea dx, [buffer]
    int 21h

    ; ending symbol '$'
    mov si, offset buffer
    mov di, offset str
    mov cx, MAX_STRING_SIZE
    rep movsb
    mov byte ptr [di], '$'

    ; sort
    mov ah, 09h
    lea dx, sorting_prompt
    int 21h

    lea si, str
    lea di, delimiter

next_word:
    mov al, [si]
    cmp al, '$'
    je done

    mov cx, 0
    mov bx, si

find_delimiter:
    mov al, [bx]
    cmp al, ' '
    je found_delimiter
    inc bx
    inc cx
    jmp find_delimiter

found_delimiter:
    lea di, [bx]

sort_word:
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
    jmp next_word

done:
    ; sort output 
    mov ah, 09h
    lea dx, str
    int 21h

    ; ending
    mov ah, 4Ch
    int 21h
main endp

 

end start