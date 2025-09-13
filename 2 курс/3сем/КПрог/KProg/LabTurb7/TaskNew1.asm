 ;This program that runs other programs.The list of programs to be launched is specified in the lines of a text file.

.model small

.data
    
    cmdline_input_length db ? ;actual length from command line
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
    DataSegment=$-cmdline_input_length

.STACK 100h

.CODE
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


start:
    mov ah, 4Ah ;function to change the memory taken by the program (in paragraphs)                                                 
    mov bx, ((CodeSegment / 16) + 1) + 2*((DataSegment / 16) + 1) + 256/16 ;code's length+ (data and extra data)+stack
    int 21h
    
    mov ax, @data ;the beginning of data in our program
    mov es, ax ;mov it to additional data segment
    mov ch,0
    mov cl, ds:[80h];command line and DTA area are situated at 80h offset
                    ;in cl the cmdline text length is stored now
    mov cmdline_input_length, cl ;move it to the variable 
    mov si, 82h  ;82 because first symbol is situated at this adress
    ;81h - space or tabulation
    mov di, offset cmdline_text
    rep movsb  ;text from command line to variable cmd_text
    mov ds, ax
    
    mov si,offset cmdline_text ;prepare the source string
    mov di,offset textFilePath ;prepare the destination string (for the path)
    
copy:
    mov al,ds:[si] ;check a symbol from command line
    cmp al,0Dh ;if it's a caret symbol, stop copying
    je end_copy
    cmp al,0 ;same for null
    je end_copy
    mov es:[di],al ;copy symbol to the path
    inc di ;increment indexes
    inc si
    jmp copy
    
end_copy: 
               print msg_start 
               print msg_start1 
               mov     ah,     3Dh                    
               mov     al,     0  
               lea     dx,     textFilePath
               int     21h
               jnc     FILE_OPEN_OK
               print     errFileOpenRd
               jmp     ENDD              
        
FILE_OPEN_OK:
               mov     [hFile],        ax
               lea     si,     [FileBuffer]
               mov     [nBufLen],      0                                           
               mov     [nCount],       0                            
WHILE:                                
               cmp     [nBufLen],      0     
               jnz     GETC                           
               mov     ah,     3Fh 
               mov     bx,     [hFile]
               mov     cx,     _BUFFER_SIZE_
               lea     dx,     [FileBuffer]
               int     21h
               jnc     FILE_READ_OK
               print   errFileRead
               jmp     BREAKK
            
FILE_READ_OK:
               test    ax,     ax
               jz      M1
               jmp M2
M1:
               jmp BREAKK
M2:               
               mov     [nBufLen],      ax  
NEW_PROG:    
               xor cx, cx
               mov di,offset Array 
GETC:
               lodsb
               dec nBufLen 
NEXT:              
                cmp     al, 0
                je      end_cop
                cmp     al, 0Dh
                je      end_cop  
                mov    [di],al
                inc di
                jmp GETC
end_cop:
    dec nBufLen            
    mov ah,1Ah ;function to set DTA area
    mov dx, offset DTA
    int 21h
    
    mov ah,4Eh ;function to find the first file in current directory
    mov dx,offset Array 
    int 21h
    print CrLf
    execute_program
    jnc SUCCESS
    print error_msg
    jmp ENDD
SUCCESS:
    print msg_start2
    print CrLf
    lodsb
    ;dec nBufLen 
    mov ax, [nBufLen]
    cmp [nBufLen], 0
    jnbe NEW_PROG

    BREAKK:
               mov     ah,     3Eh
               mov     bx,     [hFile]
               int     21h    
               jnc     ENDD
               print   errFileClose
               jmp     ENDD

 ENDD:
               mov     ax,     4C00h
               int     21h
    
CodeSegment = $ - start
end start