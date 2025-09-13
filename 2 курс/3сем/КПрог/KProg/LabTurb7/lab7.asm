;This program that runs other programs.The list of programs to be launched is specified in the lines of a text file.
.model small

.data
EPB dw 0                          ; Execution Program Block (EPB)
cmd_off dw offset commLine         ; Command offset
cmd_seg dw ?                       ; Command segment
fcb1 dd 0                          ; File Control Block 1
fcb2 dd 0                          ; File Control Block 2
Len dw $-EPB                       ; Length of EPB
commLine db 0, ' ', 126 dup(0), '$' ; Command line buffer
path db "text.txt", 0, "$"          ; File path
readed_total dw 0                  ; Total bytes read
cmd_length dw 0                    ; Command length
file_ID1 dw 0                       ; File ID 1
file dw 0                           ; File handle
buffer db 50 dup('$'), '$'         ; General-purpose buffer
buffer_prog db 50 dup('$'), '$'    ; Program buffer
enters db 0Dh, 0Ah,0Dh, 0Ah,'$'    ; New line characters
counter dw 0                        ; Counter for program execution
msg_start db 0Dh,0Ah,"This program that runs other programs.",0Dh,0Ah, "The list of programs to be launched is specified in the lines of a text file.",0Dh,0Ah,0Dh,0Ah,'$'
;errors
error_cmd db 0Ah, 0Dh, "Limit symbols in cmd string!", "$"
error_not_found_mes db 0Ah, 0Dh, "File not found!", "$" 
error_not_found_path db 0Ah, 0Dh, "Path not found!", "$"
error_many_files_mes db 0Ah, 0Dh, "Too many files open!", "$"
error_access_denied_mes db 0Ah, 0Dh, "Access is denied!", "$" 
error_incorrect_access_mode_mes db 0Ah, 0Dh, "Incorrect access mode!", "$"
error_invalid_id_mes db 0Ah, 0Dh, "Invalid ID of file!", "$"
rsErr db 0Ah, 0Dh, "Error in resize", "$"
stErr db 0Ah, 0Dh, "Error in start program", "$"
DataSize = $ - EPB

.stack 100h
.code
;macro to print messages
print macro out_str
    push ax ; Save registers to preserve their values
    push dx
    mov dx,offset out_str ; Load the offset of the output string into the dx register
    mov ah,9 ; Set the AH register to 9 (DOS print string function)
    int 21h  ; Invoke the DOS interrupt 21h to print the string
    pop dx ; Restore registers to their original values
    pop ax
endm
main:
   mov ax, @data       ; Load the data segment address into ax
   mov ds, ax          ; Move the data segment address to the ds register
   mov cmd_seg, ax     ; Copy the data segment address to the cmd_seg variable
   mov cmd_length, 8   ; Set the value 8 to the cmd_length variable

   mov cx, cmd_length  ; Copy the value of cmd_length to the cx register
   jmp main_proccess   ; Unconditional jump to the main_proccess label

    
main_proccess:                      ; MAIN Procedure
    print msg_start
    call openFile                   ; Call the openFile procedure
    jc error_badOpen                ; Jump to error_badOpen if there was an error opening the file
    mov [file], ax                 ; Save the file handle in [file]
    call readFromFile               ; Call the readFromFile procedure
    jc error_badRead                ; Jump to error_badRead if there was an error reading from the file
    
    mov bx, ax                       ; Move the result of the read operation to bx
    mov byte ptr [commLine], bl      ; Save the first byte of the file in [commLine]

    mov [readed_total], ax           ; Save the total bytes read in [readed_total]
    call closeFile                   ; Call the closeFile procedure
    jc error_close                   ; Jump to error_close if there was an error closing the file
    
    mov si, 0                         ; Initialize source index
    mov di, 0                         ; Initialize destination index
    mov cx, [readed_total]            ; Load total bytes read into cx
    jmp pre_loop                      ; Jump to pre_loop

error_close:
    jmp error_invalid_id              ; Jump to error_invalid_id in case of a close error
error_badRead:
    jmp badRead                       ; Jump to badRead in case of a read error
error_badOpen:
    jmp badOpen                       ; Jump to badOpen in case of an open error

pre_loop:
    mov ax, 4A00h                    ; Memory block resize
    mov bx, ((CodeSize / 16) + 17) + ((DataSize / 16) + 17) + 1
    int 21h
    jc errResize                      ; Jump to errResize if carry flag is set
    
loop_get_file:
    mov al, [buffer + si]            ; Load character from buffer into al
    cmp al, 0Dh                      ; Compare character with carriage return
    je start_prog                     ; Jump to start_prog if it's a carriage return
    mov [buffer_prog + di], al        ; Copy the character to buffer_prog
    inc si                            ; Increment source index
    inc di                            ; Increment destination index
    dec cx                            ; Decrement character count
    jmp loop_get_file                 ; Repeat the loop
    
start_prog:
    mov [buffer_prog + di], 0      ; Null-terminate buffer_prog
    inc di                          ; Increment destination index
    mov [buffer_prog + di], '$'    ; Append '$' to buffer_prog
    mov dx, offset buffer_prog      ; Load offset of buffer_prog into dx
    mov ah, 09h                     ; Print string function
    int 21h                          ; Invoke interrupt 21h

    mov dx, offset enters           ; Load offset of enters into dx
    mov ah, 02h                     ; Print characters function
    int 21h                          ; Invoke interrupt 21h

    mov ax, @data                   ; Load data segment into ax
    mov es, ax                      ; Move data segment into es
    mov ah, 4Bh                     ; Exec function
    mov al, 00h                     ; Normal termination
    mov dx, offset buffer_prog      ; Load offset of buffer_prog into dx
    mov bx, offset EPB              ; Load offset of EPB into bx
    int 21h                          ; Invoke interrupt 21h
    jc errStart                     ; Jump to errStart in case of an exec error
    sub cx, [counter]               ; Subtract counter from cx
    cmp cx, 2                       ; Compare cx with 2
    je end_program                  ; Jump to end_program if equal
    add cx, [counter]               ; Add counter to cx
    add [counter], 2                ; Add 2 to counter
    inc si                          ; Increment source index
    inc si                          ; Increment source index
    mov di, 0                       ; Reset destination index
    jmp loop_get_file               ; Repeat the loop

errStart:
    mov ah, 09h                     ; Print string function
    lea dx, stErr                   ; Load offset of stErr into dx
    int 21h                         ; Invoke interrupt 21h
    jmp end_program                 ; Jump to end_program

errResize:
    mov ah, 09h                     ; Print string function
    lea dx, rsErr                   ; Load offset of rsErr into dx
    int 21h                         ; Invoke interrupt 21h
    jmp end_program                 ; Jump to end_program

end_program:
    mov ah, 4ch                     ; Exit function
    int 21h                         ; Invoke interrupt 21h

openFile proc                       ; Try to open a file
    push dx
    mov dx, offset path
    mov ah, 3Dh                     ; Open file
    mov al, 00h                     ; Access mode (read-only)
    mov cx, 00h                     ; File attributes (normal)
    int 21h                         ; Invoke interrupt 21h
    mov [file_ID1], ax              ; Save the file handle in [file_ID1]
    pop dx
    ret

openFile endp

readFromFile proc
    mov bx, [file]                  ; Load file handle into bx
    mov ah, 3Fh                     ; Read file
    mov cx, 50                      ; Number of bytes to read
    lea dx, buffer                  ; Load offset of buffer into dx
    int 21h                         ; Invoke interrupt 21h
    ret

readFromFile endp

closeFile proc
    mov bx, [file_ID1]              ; Load file handle into bx
    mov ah, 3Eh                     ; Close file
    int 21h                         ; Invoke interrupt 21h
    ret

closeFile endp

badOpen:
    cmp ax, 02h                    ; Check if error code is 2 (File not found)
    je error_not_found             ; Jump to error_not_found if true
    cmp ax, 03h                    ; Check if error code is 3 (Path not found)
    je error_path_not_found        ; Jump to error_path_not_found if true
    cmp ax, 04h                    ; Check if error code is 4 (Too many open files)
    je error_many_files            ; Jump to error_many_files if true
    cmp ax, 05h                    ; Check if error code is 5 (Access is denied)
    je error_access_denied         ; Jump to error_access_denied if true
    cmp ax, 0Ch                    ; Check if error code is 12 (Incorrect access mode)
    je error_incorrect_access_mode ; Jump to error_incorrect_access_mode if true

badRead:
    cmp ax, 05h                    ; Check if error code is 5 (Access is denied)
    je error_access_denied         ; Jump to error_access_denied if true
    cmp ax, 06h                    ; Check if error code is 6 (Invalid file ID)
    je error_invalid_id            ; Jump to error_invalid_id if true

error_invalid_id:
    mov ax, @data                  ; Load data segment into ax
    mov ds, ax                     ; Move data segment into ds
    mov dx, offset error_invalid_id_mes ; Load offset of error_invalid_id_mes into dx
    mov ah, 09h                    ; Print string function
    int 21h                        ; Invoke interrupt 21h
    jmp end_program                ; Jump to end_program

error_not_found:
    mov ax, @data                  ; Load data segment into ax
    mov ds, ax                     ; Move data segment into ds
    mov dx, offset error_not_found_mes ; Load offset of error_not_found_mes into dx
    mov ah, 09h                    ; Print string function
    int 21h                        ; Invoke interrupt 21h
    jmp end_program                ; Jump to end_program

error_path_not_found:
    mov ax, @data                  ; Load data segment into ax
    mov ds, ax                     ; Move data segment into ds
    mov dx, offset error_not_found_path ; Load offset of error_not_found_path into dx
    mov ah, 09h                    ; Print string function
    int 21h                        ; Invoke interrupt 21h
    jmp end_program                ; Jump to end_program

error_many_files:
    mov ax, @data                  ; Load data segment into ax
    mov ds, ax                     ; Move data segment into ds
    mov dx, offset error_many_files_mes ; Load offset of error_many_files_mes into dx
    mov ah, 09h                    ; Print string function
    int 21h                        ; Invoke interrupt 21h
    jmp end_program                ; Jump to end_program

error_access_denied:
    mov ax, @data                  ; Load data segment into ax
    mov ds, ax                     ; Move data segment into ds
    mov dx, offset error_access_denied_mes ; Load offset of error_access_denied_mes into dx
    mov ah, 09h                    ; Print string function
    int 21h                        ; Invoke interrupt 21h
    jmp end_program                ; Jump to end_program

error_incorrect_access_mode:
    mov ax, @data                  ; Load data segment into ax
    mov ds, ax                     ; Move data segment into ds
    mov dx, offset error_incorrect_access_mode_mes ; Load offset of error_incorrect_access_mode_mes into dx
    mov ah, 09h                    ; Print string function
    int 21h                        ; Invoke interrupt 21h
    jmp end_program                ; Jump to end_program

CodeSize = $ - main               ; Calculate the size of the code section

end main                          ; End of the main program
  