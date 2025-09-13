.model small
.stack 100h
.data
     F DW 0
     T DB 5
     str1 db "Input Freq: $"
     str2 db "Input Time: $"
.code
mov ax,@data
mov ds,ax

mov ah, 09h; 
mov dx, offset str1
int 21h
mov cx, 5
xor ax, ax
push ax
la:
      mov ah, 08h
      int 21h
      cmp al, 13d
      je ex
      cmp al, 48d
      jb la
      cmp al, 57d
      ja la
      mov bl, al
      mov bh, 0h
      mov dl, al
      mov ah, 02h
      int 21h
      sub bx, 48d
      pop ax
      mov dx, 10d
      mul dx
      jc er      
      add ax, bx
      jc er
      push ax
loop la
jmp ex
er:push 0ffffh
ex:
pop ax
mov F, ax
;-----------------------------------------------------------------------------------------------------
mov dl, 0ah
mov ah, 02h
int 21h
mov dl, 0dh
mov ah, 02h
int 21h


mov ah, 09h
mov dx, offset str2
int 21h
mov cx, 3
xor ax, ax
push ax
la2:
      mov ah, 08h
      int 21h 
      cmp al, 13d
      je ex2
      cmp al, 48d
      jb la
      cmp al, 57d
      ja la
      mov bl, al
      mov dl, al
      mov ah, 02h
      int 21h
      sub bl, 48d 
      pop ax
      mov dl, 10d
      mul dl
      jc er2     
      add al, bl
      jc er2
      push ax
loop la2
jmp ex2
er2:push 0ffh
ex2:
pop ax
mov T, al

IN al, 61H    
OR al,00000011B
OUT 61H,al
mov SI,0
mov al,0B6H
OUT 43H,al
 
mov dx, F
mov al,DL
OUT 42H,al
mov al,DH
OUT 42H,al
 
mov ah,0;
INT 1AH
MOV AL, T; 
MOV CX, 10
MUL CL
mov CX, AX
mov bx,dx
ADD bx,cx
 
ST_SOU: INT 1AH
CMP dx,bx
JNE ST_SOU
 
IN al,61H
AND al,0FCH
OUT 61H,al
 
mov ax,4c00h
int 21h
 
 
end