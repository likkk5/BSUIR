.8086
.model tiny

.code
org 100h

print macro out_str ; ����� ������ ������  
    mov ah,9
    mov dx,offset out_str
    int 21h
endm

println macro ; ����� ������ ������� ����� �����
    print new_line
endm
 
start:
    
    ; ��������� 2 �����, ������� � ����                       
    print enter_first_number
    call InputInt
    push ax
    print enter_second_number
    call InputInt
    push ax 
    
    
    ; ������� xor
    print xor_str
    pop ax
    pop bx
    push bx
    push ax
    xor ax, bx
    call OutInt
    println
    
    ; ������� and
    print and_str
    pop ax
    pop bx
    push ax
    push bx
    and ax, bx
    call OutInt
    println
    
    ; ������� or
    print or_str
    pop ax
    pop bx
    or ax, bx
    call OutInt
    println 
          
    ret

InputInt proc 
 
    mov ah,0ah
    xor di,di
    mov dx,offset buff ; ������ ������
    int 21h ; ��������� ������
    println
    
; ������������ ���������� ������
    mov si,offset buff+2 ; ����� ������ ������ ������
    
    ; ����� ������ > 0
    mov cl, buff+1
    cmp cl, 0
    je er
    xor ax,ax
    mov bx,10  ; ��������� �c
lp:
    xor cx, cx  ; ������� ������� cx
    mov cl,[si] ; ����� ������ �� ������
    cmp cl,0dh  ; ��������� �� ��������� �� ��
    jz endin
    
; ���� ������ �� ���������, �� ��������� ��� �� ������������
    cmp cl,'0'  ; ���� ������ �������� ������ <0
    jl er
    cmp cl,'9'  ; ���� ������ �������� ������ >9
    ja er
 
    sub cl,'0' ; ������ �� ������� ����� 
    mul bx     ; �������� �� 10
    add ax,cx  ; ���������� � ���������
    inc si     ; ��������� �� ��������� ������
    jmp lp     ; ���������
 
er:   ; ���� ���� ������, �� ������� ��������� �� ���� � �������
    mov dx, offset error
    mov ah,09
    int 21h
    int 20h
 
; ��� ������� �� ������ ���������� ����� ��������� � ax
endin:
    ret
InputInt endp

OutInt proc
    xor     cx, cx
    mov     bx, 10 ; ��������� ��. 10 ��� ������������ � �.�.
oi2:
    xor     dx,dx
    div     bx
; ����� ����� �� ��������� ��. � ������� ���������� ��������� �����.
; ����� �������� � ������, ������� �������� � � �����.
    push    dx
    inc     cx
; � � ������� ��������� �� �� �����, ������� �� ���� ���������
; ����� ������, ���� �� ��������� ����, ��� ������, ��� ������
; ����� ������ ����.
    test    ax, ax
    jnz     oi2
; ������ ��������� � ������.
    mov     ah, 02h
oi3:
    pop     dx
; ��������� ��������� �����, ��������� � � ������ � �������.
    add     dl, '0'
    int     21h
; �������� ����� ������� ���, ������� ���� ���������.
    loop    oi3  
    ret
OutInt endp

buff                   db      5,6 Dup(?)
error                  db      "Incorrect input$"
enter_first_number:    db      "Enter first number:", 0Dh,0Ah, '$'
enter_second_number:   db      "Enter second number:", 0Dh,0Ah, '$'
xor_str:               db      "Xor: $" 
or_str:                db      "Or:  $"
and_str:               db      "And: $"
new_line:              db      0Dh, 0Ah, '$'
end start