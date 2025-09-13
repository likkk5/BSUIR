.model small

.data
    ;cmdline_input_length db ? ;actual length from command line
    cmdline_input_max_length equ 126 ;max length in command line
    cmdline_text db cmdline_input_max_length dup (0) ;variable for text from command line
    textFilePath db cmdline_input_max_length dup (0) ;ready path to the directory
    _BUFFER_SIZE_   equ     1024
    FileBuffer      db      _BUFFER_SIZE_ dup(?) 
    errFileOpenRd   db      0dh,0ah,"File open (for read) -- error", '$'
    errFileRead     db      0dh,0ah,"File read -- error", '$'
    errFileClose    db      0dh,0ah,"File close -- error", '$'  
    nBufLen         dw      ?                      
    nCount          dw      ?                      
    hFile           dw      ?
    Array           dw      50 dup(?)
    cChar           db      ?        
    CrLf            db      0Dh, 0Ah, '$'    
    msg_start db 0Dh,0Ah,"This program that runs other programs.",0Dh,0Ah, "The list of programs to be launched is specified in the lines of a text file.",0Dh,0Ah,0Dh,0Ah,'$'
    msg_start1 db 0Dh,0Ah,"Main program was started.",0Dh,0Ah,0Dh,0Ah,'$' 
    msg_start2 db 0Dh,0Ah,"Child program was started.",0Dh,0Ah,0Dh,0Ah,'$' 
    error_msg db 0Dh,0Ah,"Child program was crashed.",0Dh,0Ah,0Dh,0Ah,'$' 
    
    MENU_MSG db 0Dh,0Ah,"Select a program to run:",0Dh,0Ah,'$'
    ERROR_INVALID_OPTION db 0Dh,0Ah,"Invalid option. Please enter a valid number.",0Dh,0Ah,'$'
    
    ;EXEC Parameter Block (for 4Bh function)
    EPB dw 0 ;Segment address of the environment to be provided for the allocate a duplicate of the current environment for the child.     
        dw offset line,0 ;command line's offset
        dw 005Ch, 0, 006Ch, 0 ;adress of a FCB (File Control Block) to be placed at PSP:005c, PSP:006c (FCB stores file's data)    
    line db 126
         db " /?"
    line_text db 126 dup(?) ;Text to be passed to the child as its command-line arguments.
    EPBlen dw $ - EPB ;EPB length
    
    ;DTA block (size: 100h-80h=256-128=128)
    sizeofDTA equ 128
    DTA db sizeofDTA dup(0)
    
    ;variable to store data segment length
    ;DataSegment=$-cmdline_input_lengt

CODE_SEGMENT equ $

.STACK 100h

;macro to print messages
print macro out_str
    push ax
    push dx
    mov dx,offset out_str
    mov ah,9
    int 21h
    pop dx
    pop ax
endm

enter_line macro string, string_length; a macro to enter and save data 
    local enter_char ;declare local labels
    local return_line ;to avoid duplicate declarations
    mov si,0 ;load 0 to the counter
    mov dx,offset string ;load the string's adress into dx
    mov ah,1 ;load the number of function responsible for outputing a symbol
    int 21h ;call this function

enter_char:
    cmp al,13 ;compare the entered symbol with the symbol of carriage return
    je return_line ;if equal, it means that the line is already entered
    mov [string+si],al ;load the symbol into the string variable
    inc si ;increment the counter (string's length)
    int 21h ;call function number 2 for symbol's input
    jmp enter_char ;restart the same for a new entered symbol

return_line:
    mov [string_length],si ;load the counter into the length's variable
    mov ah,2
    mov dl,10
    int 21h
    mov dl,13
    int 21h
endm

;macro to run exe programs
execute_program macro
    mov ah, 4Bh ;function to load and run the program .exe 
    mov al,0 ;load and accomplish    
    mov bx, offset EPB ;adress of EPB 
    mov dx, offset DTA + 1Eh ;in DTA area file's name is situated on 1Eh offset
    int 21h
endm


.CODE
start:
    ; Prompt user for the file path
    print 0Dh, 0Ah, "Enter the path to the text file:", 0Dh, 0Ah, '$'
    enter_line  cmdline_text, cmdline_input_max_length

    ; Open the file
    mov ah, 3Dh
    mov al, 0 ; Read-only mode
    lea dx, line_text
    int 21h
    jnc FILE_OPEN_OK
    print errFileOpenRd
    jmp ENDD

FILE_OPEN_OK:
    mov [hFile], ax
    lea si, [FileBuffer]
    mov [nBufLen], 0
    mov [nCount], 0

READ_FILE:
    cmp [nBufLen], 0
    jnz GETC

    ; Read from the file
    mov ah, 3Fh
    mov bx, [hFile]
    mov cx, _BUFFER_SIZE_
    lea dx, [FileBuffer]
    int 21h
    jnc FILE_READ_OK
    print errFileRead
    jmp BREAKK

FILE_READ_OK:
    test ax, ax
    jz M1
    jmp M2

M1:
    jmp BREAKK

M2:
    mov [nBufLen], ax

NEW_PROG:
    xor cx, cx
    mov di, offset Array

GETC:
    lodsb
    dec [nBufLen]
    cmp al, 0
    je END_COP
    cmp al, 0Dh
    je END_COP
    mov [di], al
    inc di
    jmp GETC

END_COP:
    dec [nBufLen]
    inc [nCount]

    jmp READ_FILE

BREAKK:
    ; Check if any programs were found in the file
    cmp [nCount], 0
    jz NO_PROGRAMS_FOUND

    ; Print menu
    print MENU_MSG

    ; Print the list of programs with numbers
    mov si, offset Array
    mov cx, [nCount]
    mov dx, 1 ; Program number counter
    mov ah, 2 ; DOS function to print character
PRINT_MENU:
    mov al, dl ; Convert counter to ASCII
    int 21h
    print ": "
    lodsb ; Load program name
    print line_text
    print CrLf
    inc dx ; Increment counter
    loop PRINT_MENU

    ; Get user input
    enter_line line, line_text

    ; Convert user input to a number
    mov si, offset line
    mov ax, 0
CONVERT_TO_NUMBER:
    mov al, [si]
    cmp al, 0
    je  INVALID_OPTION
    sub al, '0'
    cmp al, 0
    jb  INVALID_OPTION
    imul ax, 10
    add ax, al
    inc si
    jmp CONVERT_TO_NUMBER

INVALID_OPTION:
    cmp ax, [nCount]
    jae INVALID_OPTION ; Entered number is out of range

    ; Execute the selected program
    mov si, offset Array
    mov cx, ax
    mov dx, 1
SEARCH_PROGRAM:
    lodsb
    dec cx
    jz  RUN_PROGRAM
    jmp SEARCH_PROGRAM

RUN_PROGRAM:
    ; Extract the selected program name
    mov si, offset Array
    mov cx, ax
    mov dx, offset line_text
SEARCH_SELECTED_PROGRAM:
    lodsb
    dec cx
    jz  EXECUTE_SELECTED_PROGRAM
    mov [dx], al
    inc dx
    jmp SEARCH_SELECTED_PROGRAM

EXECUTE_SELECTED_PROGRAM:
    mov byte ptr [dx], 0 ; Null-terminate the selected program name
    execute_program
    jnc SUCCESS
    print error_msg
    jmp ENDD

NO_PROGRAMS_FOUND:
    print 0Dh, 0Ah, "No programs found in the file.", 0Dh, 0Ah, '$'
    jmp ENDD

SUCCESS:
    print msg_start2
    print CrLf
    jmp MENU ; Return to the menu

ENDD:
    ; Close the file
    mov ah, 3Eh
    mov bx, [hFile]
    int 21h

.CODE_SEGMENT equ $
;CodeSegment = $ - start
end start
