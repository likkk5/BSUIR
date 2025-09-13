.model small


.data
print_message_begin db "Enter the string (max - 200 symbols)",0Dh, 0Ah, '$'
print_message_end db 0Dh, 0Ah, "Your modified string: ", 0Dh, 0Ah, '$'
buffer db 200, 0, 200 dup('$')  
buffer_for_dollar db , "$"    
enter db 0Dh, 0Ah, "$"
.stack 100h
.code
org 100h
main:
mov ax, @data
mov ds, ax
mov dx, offset print_message_begin
mov ah, 9
int 21h
;enter string
lea dx, buffer
mov ah, 0Ah
int 21h 

mov dx, offset enter
mov ah, 9
int 21h

mov si, 2
mov di, 0
mov cl, buffer[1]
jmp proccess_scanning
preendr:
    jmp endr
proccess_scanning:
    cmp cl, 0
    je preendr

    ;je print_result
    mov ah, buffer[si] 
    ;cmp ah, '$'
    ;je check_dollar
    cmp ah, 57    ;check it is digit
    jg pre_not_digit
    cmp ah, 48
    jl pre_not_digit
    
    cmp ah, 48
    je check_the_number_system
    
    cmp ah, 32        ;dodelat' so slovami
    je pre_not_digit_space            
    return_space:
        cmp cl, 0
        je preendr
        mov ah, buffer[si]
        cmp ah, 32
        je pre_not_digit_space
        
                
                
    inc si
    dec cl
    ;check_floating_point after digit if it is digit
    cmp cl, 0 
    je preendr
    ;je print_result
    
    mov ah, buffer[si]
    cmp ah, 46
    je pre_floating_point
    jmp proccess_scanning
    
    pre_floating_point:
        jmp floating_point
    check_dollar:
        mov dx, '$'
        mov ah, 02h 
        int 21h 
        inc si
        dec cl
        
            
         
        ;inc si
        ;dec cl
        ;cmp cl, 0
        ;je print_result
        ;mov ah, buffer[si]
        ;cmp ah, 57
        ;jg not_digit_after_doll
        ;cmp ah, 48
        ;jg not_digit_after_doll
        
        ;not_digit_after_doll:
           ; mov buffer_for_dollar[3], ah
          ;  mov ah, buffer_for_dollar[3]
         ;   jmp not_digit        
        jmp proccess_scanning
    pre_not_digit_space:
        jmp not_digit_space
    pre_not_digit:
        jmp not_digit
    check_the_number_system:
        inc si
        dec cl
        cmp cl, 0
        ;je print_result
        mov ah, buffer[si]
        cmp ah, 98 ;check it is (b)? binary
        je it_is_binary
        cmp ah, 120 ;check it is (x)? hexadecimal
        je it_is_hexadecimal
        cmp ah, 46 ;else check on floating point
        je pre_floating_point
        jmp proccess_scanning
        
        it_is_binary:
            inc si
            dec cl
            cmp cl, 0
            
            je end_in_binary
            mov ah, buffer[si]
            cmp ah, 48    ; equal 1 or 0
            je equal
            cmp ah, 49
            je equal
            jmp not_needed_digit_afterb
            equal:
                inc si
                dec cl
                jmp proccess_scanning
            not_needed_digit_afterb: ;check it is digits or letters 
                dec si
                inc cl
                mov ah, buffer[si]
                mov buffer[di], ah
                cmp ah, 57    ;check it is digit
                jg pre_not_digit
                cmp ah, 48
                jl pre_not_digit
                
                ;inc di
                jmp proccess_scanning     
        end_in_binary: ;if in binary b - last symbol in string
            dec si
            mov ah, buffer[si]
            mov buffer[di], ah
            inc di
            ;jmp print_result
            
        it_is_hexadecimal:
            inc si
            dec cl
            cmp cl, 0
            je pre_end_in_hexadecimal
            mov ah, buffer[si]
            
            cmp ah, 65      ;equal 0-9 or A-F
            je equal_x
            cmp ah, 66
            je equal_x
            cmp ah, 67
            je equal_x
            cmp ah, 68
            je equal_x
            cmp ah, 69
            je equal_x
            cmp ah, 70
            je equal_x
            cmp ah, 48
            je equal_x
            cmp ah, 49
            je equal_x
            cmp ah, 50
            je equal_x
            cmp ah, 51
            je equal_x
            cmp ah, 52
            je equal_x
            cmp ah, 53
            je equal_x
            cmp ah, 54
            je equal_x
            cmp ah, 55
            je equal_x
            cmp ah, 56
            je equal_x
            cmp ah, 57
            je equal_x
            jmp not_needed_digit_afterx
        pre_end_in_hexadecimal:
            jmp end_in_hexadecimal    
        equal_x:
            inc si
            dec cl
            jmp check_next_symbol
            ;jmp proccess_scanning
        preendr1:
            jmp endr
        check_next_symbol:    ;check next symbol after 0xA..
            cmp cl, 0
            je preendr1
            mov ah, buffer[si]
            cmp ah, 65      ;equal 0-9 or A-F
            je equal_x
            cmp ah, 66
            je equal_x
            cmp ah, 67
            je equal_x
            cmp ah, 68
            je equal_x
            cmp ah, 69
            je equal_x
            cmp ah, 70
            je equal_x
            cmp ah, 48
            je equal_x
            cmp ah, 49
            je equal_x
            cmp ah, 50
            je equal_x
            cmp ah, 51
            je equal_x
            cmp ah, 52
            je equal_x
            cmp ah, 53
            je equal_x
            cmp ah, 54
            je equal_x
            cmp ah, 55
            je equal_x
            cmp ah, 56
            je equal_x
            cmp ah, 57
            je equal_x
            jmp not_needed_digit_afterx
                                  
        not_needed_digit_afterx:
            dec si
            inc cl
            mov ah, buffer[si]
            cmp ah, 65
            je it_is_digit
            cmp ah, 66
            je it_is_digit
            cmp ah, 67
            je it_is_digit
            cmp ah, 68
            je it_is_digit
            cmp ah, 69
            je it_is_digit
            cmp ah, 70
            je it_is_digit
            mov buffer[di], ah
            cmp ah, 57 ;check it is digit
            jg not_digit
            cmp ah, 48
            jl not_digit
            
            jmp proccess_scanning
            
        it_is_digit:  ;in 0xAAFFmeow
            inc si
            dec cl
            jmp proccess_scanning
        end_in_hexadecimal: ;if in hexadecimal x - last symbol in string
            dec si
            mov ah, buffer[si]
            mov buffer[di], ah
            inc di
            ;jmp print_result
                               
    floating_point: ;skip floating point
        inc si
        dec cl
        jmp proccess_scanning
    not_digit: 
      
        mov dl, buffer[si]
        mov ah, 02h
        int 21h
        inc si
        inc di
        dec cl
        jmp proccess_scanning 
    not_digit_space:
        mov dl, buffer[si]
        mov ah, 02h
        int 21h
        inc si
        inc di
        dec cl
        jmp return_space
;print_result:
    
    
 ;   mov buffer[di], '$'
    
  ;  mov dx, offset print_message_end
   ; mov ah, 9
    ;int 21h
      
   ; lea dx, buffer
   ; mov ah, 9
   ; int 21h
   ; jmp endr
    
endr:
    mov ah, 4Ch
    int 21h
end main    
