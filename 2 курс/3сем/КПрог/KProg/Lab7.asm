.286
.model small
.stack 100h

empty_segment SEGMENT    
empty_segment ENDS

.data
    program_path db "c:/KProg/Lab7.exe", 0
    exec_param_block dw 0
    cmd_of dw offset commandline, 0
    fcb1 dw 005ch, 0
    fcb2 dw 006ch, 0

    commandline db 4
                db " ", 0dh
    commandline_text db 122 dup(?)

    epb_length dw $-exec_param_block

    copy_counter dw 0

    count_of_copies db 5 dup(0)
    prev_count_of_copies db 5 dup(0)


    error_code dw 0
    error_code_string db 6 dup('$'), 0
    error_message db "Error occurred. Error code : ", '$'
    move_cursor db 10, 13, '$'

    copy_counter_overflow_msg db "Too many copies. Max value is 255", 10, 13, '$'

    no_symbol_msg db "No argument founded", 10, 13, '$'

    invalid_argument_msg db "Invalid argument", 10, 13, '$'

    number_message db "Copy number : ", '$', 0

    symbols_overflow_flag db 0
    no_symbol_flag db 0
    invalid_symbol_flag db 0

    data_segment_size = $ - program_path
.code

    handle_error proc
        pusha
        mov word ptr[error_code], ax
        mov si, offset error_code_string
        call itoa
        popa
        ret
    handle_error endp

    output_error proc
        pusha
        xor dx, dx
        mov ah, 09h
        mov dx, offset error_message
        int 21h
        mov ah, 09h
        mov dx, offset error_code_string
        int 21h
        mov ah, 09h
        mov dx, offset move_cursor
        int 21h
        popa
        ret
    output_error endp

     strlen proc
        push si
        xor ax, ax
        xor cx, cx
        strlen_loop:
            mov al, byte ptr[si]
            cmp al, 0
            je _exit_strlen
            inc si
            inc cx
            jmp strlen_loop

        _exit_strlen:
            pop si
            ret
    strlen endp

    ;input: ax - digit to convert
    ;       si - buffer to hold digit
    ;output: in buffer si - symbol representation of digit
    itoa proc
        pusha
        xor bx, bx
        mov di, si
        _outer_loop_:
           mov bx, 10
           xor dx, dx
           div bx
           add dx, '0'
           mov byte ptr[si], dl
           inc si 
           cmp ax, 0
           je _ret_itoa
           jmp _outer_loop_
        _ret_itoa:
            mov byte ptr[si], '$'
            mov si, di
            call reverse_string       
            popa
            ret
    itoa endp

    ;input: si - source string
    ;       di - place to hold digit
    ;output: in di   
    atoi proc
        pusha
        xor bx, bx
        xor ax, ax
        start_converting:
            cmp byte ptr[si], '0'
            jb _exit_atoi
            cmp byte ptr[si], '9'
            jg _exit_atoi
            mov bl, 10
            mul bx 
            mov bl, byte ptr [si]
            sub bl, '0'
            add ax, bx
            inc si
            jmp start_converting
        _exit_atoi:
        mov word ptr[di], ax
        popa
        ret
    atoi endp    
    

    parse_command_line proc
        pusha
        xor ax, ax
        xor bx, bx

        mov bl, byte ptr es:[80h]
        cmp bl, 1
        jbe _exit_parse_command_line_no_symbol

        cmp bl, 4
        jg _exit_parse_command_line_symbol_overflow

        mov si, 82h
        mov di, offset count_of_copies
        parse_count:
            mov al, byte ptr es:[si]
            cmp al, ' '
            je end_parse_count
            cmp al, 0dh
            je end_parse_count

            cmp al, '0'
            jl _invalid_value
            cmp al, '9'
            jg _invalid_value

            mov byte ptr[di], al
            inc si
            inc di
            jmp parse_count

        end_parse_count:
            mov byte ptr[di], '$'
            jmp _exit_parse_command_line

        _exit_parse_command_line_no_symbol:
            mov byte ptr[no_symbol_flag], 1
            jmp _exit_parse_command_line

        _exit_parse_command_line_symbol_overflow:
            mov byte ptr[symbols_overflow_flag], 1
            jmp _exit_parse_command_line

         _invalid_value:
            mov byte ptr[invalid_symbol_flag], 1
            jmp _exit_parse_command_line

        _exit_parse_command_line:
            popa
            ret
    parse_command_line endp


    print_number proc
        pusha
        xor dx, dx
        mov ah, 09h
        mov dx, offset number_message
        int 21h
        mov ah, 09h
        mov dx, offset prev_count_of_copies
        int 21h
        mov ah, 09h
        mov dx, offset move_cursor
        int 21h
        popa
        ret
    print_number endp


    set_cmd_param proc
        pusha
        mov si, offset count_of_copies
        call strlen
        mov byte ptr[commandline], cl
        mov di, offset count_of_copies
        mov si, 2
        xor ax, ax
        xor bx, bx

        set_cmd_param_loop:
            mov al, byte ptr[di]
            cmp al, '$'
            je _exit_set_param

            mov bl, byte ptr[commandline+si]
            inc si
            mov byte ptr[commandline+si], bl
            dec si
            mov byte ptr[commandline+si], al
            inc si
            inc di
            jmp set_cmd_param_loop

        _exit_set_param:
        popa
        ret
    set_cmd_param endp



    ;input: si -string to reverse
    reverse_string proc
        pusha
        xor bx, bx
        xor ax, ax
        mov di, si

        searching_end_string:
            cmp byte ptr[si], '$'
            je end_string
            inc si
            jmp searching_end_string

        end_string:
            dec si

        swap_loop:
            cmp si, di
            jle end_swap_loop
            mov al, byte ptr[si]
            mov bl, byte ptr[di]
            xchg ax, bx
            mov byte ptr[si], al
            mov byte ptr[di], bl
            dec si
            inc di
            jmp swap_loop
        end_swap_loop:

        _exit_reverse_string:
            popa
            ret
    reverse_string endp


_start:

    mov ax,es
    mov bx,empty_segment
    sub bx,ax

    mov ax, 4a00h
    int 21h
    jc _error

    mov ax, @data
    mov ds, ax

    jmp parse
    _error:
        call handle_error
        call output_error
        jmp _exit
        
    parse:

    call parse_command_line

    cmp byte ptr[no_symbol_flag], 1
    je error_no_symbol

    cmp byte ptr[symbols_overflow_flag], 1
    je copy_counter_overflow

    cmp byte ptr[invalid_symbol_flag], 1
    je invalid_argument

    mov ax, @data
    mov es, ax

    mov si, offset count_of_copies
    mov di, offset copy_counter
    call atoi

    mov ax, word ptr[copy_counter]
    mov si, offset prev_count_of_copies
    call itoa

    ;call print_number
    
    cmp word ptr[copy_counter], 0
    je _exit_with_print

    cmp word ptr[copy_counter], 255
    jg copy_counter_overflow

    mov ax, word ptr[copy_counter]
    dec ax
    mov word ptr[copy_counter], ax
    mov si, offset count_of_copies
    call itoa
    call set_cmd_param

    mov bx,offset exec_param_block
    mov ax,ds
    mov word ptr[exec_param_block+4],ax
    mov ax,cs
    mov word ptr[exec_param_block+8],ax
    mov word ptr[exec_param_block+12],ax

    mov ax, 4b00h
    lea dx, program_path
    lea bx, exec_param_block
    int 21h
    jc _error

    call print_number

    jmp _exit

    copy_counter_overflow:
        xor dx, dx
        mov ah, 09h
        mov dx, offset copy_counter_overflow_msg
        int 21h
        jmp _exit
    
    error_no_symbol:
        xor dx, dx
        mov ah, 09h
        mov dx, offset no_symbol_msg
        int 21h
        jmp _exit

    invalid_argument:
        xor dx, dx
        mov ah, 09h
        mov dx, offset invalid_argument_msg
        int 21h
        jmp _exit

    _exit_with_print:
        call print_number
        jmp _exit

    _exit:
        mov ax, 4c00h
        int 21h

end _start