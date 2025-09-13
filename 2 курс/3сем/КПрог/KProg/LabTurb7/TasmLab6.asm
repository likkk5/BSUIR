.model  small
 
.stack  100h
 
.data                             
        startMessage    db      'This program counts the number of lines in a file that contain all the entered',0dh,0ah,'characters.', 0Dh, 0Ah,0dh,0ah,'Program has started.$' 
        ;arg_string      db      127 + 2 dup(0)
        fname           db      0Dh, 0Ah,0Dh, 0Ah, 'Your filename is: $'
        CrLf            db      0Dh, 0Ah, '$'
        inputMessage    db      0Dh, 0Ah,0dh,0ah,'You have not entered any characters to search for. Please enter. ', 0Dh, 0Ah,'$'                    
        dataMessage     db      0Dh, 0Ah,'File data: ', 0Dh, 0Ah,'--------------------------------------------------------------------------------$' 
        againMessage    db      0Dh, 0Ah,0dh,0ah,'Want to count again? (y/n): $'    
        checkMessage    db      0dh,0ah,'Are you sure in your choice? (y/n): $'       
        delMessage      db      0dh,0ah,'Do you want to delete file? (y/n): $'
        errFileOpenRd   db      0dh,0ah,"File open (for read) -- error", '$'
        errFileOpenWr   db      0dh,0ah,"File open (for write) -- error", '$'
        errFileRead     db      0dh,0ah,"File read -- error", '$'
        errFileWrite    db      0dh,0ah,"File write -- error", '$'
        errFileClose    db      0dh,0ah,"File close -- error", '$'             
        msgGetChar      db      0Dh, 0Ah,0dh,0ah,"Input the symbols, please: ", '$'  
        success_oper    db      0Dh, 0Ah,0dh,0ah,"File was successful deleted", '$' 
        msgResult       db      0Dh, 0Ah,'--------------------------------------------------------------------------------', 0Dh, 0Ah, "Result: ", '$'
        _BUFFER_SIZE_   equ     1024
        FileBuffer      db      _BUFFER_SIZE_ dup(?) 
        Array           dw      50 dup(?) 
        CopyArray       dw      50 dup(?) 
        nBufLen         dw      ?                      
        nCount          dw      ?                      
        hFile           dw      ?
        cChar           db      ?                     
        bCheckOnce      dw      ? 
        cmdline_input_length db ? ;actual length from command line
        cmdline_input_max_length equ 126 ;max length in command line
        cmdline_text db cmdline_input_max_length dup (0) ;variable for text from command line
        path_to_dir db cmdline_input_max_length dup (0) ;ready path to the directory
        
.code
 
ShowUInt16       proc
               mov     bx,     10             
               mov     cx,     0 
                      
DIVV:
               xor     dx,     dx    
               div     bx
               add     dl,     '0'     
               push    dx            
               inc     cx              
               test    ax,     ax      
               jnz     DIVV  
                 
SHOW:
               mov     ah,     02h     
               pop     dx              
               int     21h            
               loop    SHOW                  
               ret
ShowUInt16       endp  

PRINT   macro   out_str
               mov     dx,     offset out_str
               mov     ah,     09h
               int     21h 
endm    PRINT               
 
main    proc                
               mov     ax,     @data                  
               mov     es,     ax         
               xor     cx,     cx
               mov cl, ds:[80h];command line and DTA area are situated at 80h offset
                    ;in cl the cmdline text length is stored now
    mov cmdline_input_length, cl ;move it to the variable 
    mov si, 82h  ;82 because first symbol is situated at this adress
    ;81h - space or tabulation
    mov di, offset cmdline_text
    rep movsb  ;text from command line to variable cmd_text
    mov ds, ax
    
    mov si,offset cmdline_text ;prepare the source string
    mov di,offset path_to_dir ;prepare the destination string (for the path)
    
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
    mov es:[di],'$'
    
               PRINT   startMessage
               PRINT   fname
               PRINT   path_to_dir
              ; mov     [di-1],  0     
               PRINT   CrLf

BEGIN: 
               mov     ah,     3Dh                    
               mov     al,     00h    
               lea     dx,     [path_to_dir]
               int     21h
               jnc     FILE_OPEN_OK
               PRINT     errFileOpenRd
               jmp     AGAIN              
        
FILE_OPEN_OK:
               mov     [hFile],        ax
               lea     si,     [FileBuffer]
               mov     [nBufLen],      0                                           
               mov     [nCount],       0                            
               PRINT     msgGetChar        
               mov     di,     offset Array            
               xor     cx,     cx                      
               xor     bx,     bx                     
          
INPUT: 
               mov     ah,     01h            
               int     21h 
               cmp     cx, 0
               je      CHECK_SYMBOLS 
               cmp     al, 0Dh
               je      CONTINUE 
              
CONTIN:    
               mov     [di],   al 
               push di
               mov     di,     offset CopyArray
               add di, cx
               mov     [di],   al 
               pop di 
               inc     cx 
               add     di,     1  
               cmp     cx, 49
               ja      CONTINUE  
               jmp     INPUT 
           
CHECK_SYMBOLS:
               cmp al, 0Dh
               jne CONTIN  
               PRINT inputMessage
               jmp     INPUT  

CONTINUE:    
               push    cx        
               PRINT CrLf                            
               PRINT dataMessage
      
WHILE:                                
               cmp     [nBufLen],      0     
               jnz     GETC                           
               mov     ah,     3Fh 
               mov     bx,     [hFile]
               mov     cx,     _BUFFER_SIZE_
               lea     dx,     [FileBuffer]
               int     21h
               jnc     FILE_READ_OK
               PRINT   errFileRead
               jmp     BREAK
            
FILE_READ_OK:
               test    ax,     ax
               jz      M1
               jmp M2
           M1:
               jmp BREAK
           M2:               
               mov     [nBufLen],      ax
                 
GETC:
               lodsb
               dec     [nBufLen]                                                                    
               mov     di, offset Array                 
               pop cx     
               push dx
               xor     dx, dx  
     
            
CHECK_EQUAL: 
               inc     dx  
               cmp     al,     [di]  
               jne     CHECK_5
               push    di
               mov     di, offset CopyArray 
               add     di, dx
               dec     di    
               cmp    [di], 0
               je      SKIP
               mov     [di], 0 
               pop di
               jmp     CHECK_NEW_LINE   
            
SKIP:   
               pop di   
                    
CHECK_5:  
               add     di, 1   
               cmp cx, dx
               jne CHECK_EQUAL                              
                                   
CHECK_NEW_LINE:
               pop dx
               push cx         
NEXT:              
               mov     ah,     02h            
               mov     dl,     al
               int     21h
               cmp     al, 0Dh
               je      TUT 
               cmp     al, 0h
               je      TUT                                               
               jmp     WHILE
         
TUT:                                            
               pop     cx 
               mov     bx,     cx 
               push    cx       
               xor     dx,     dx 
               push    di 
               mov     di,     offset CopyArray 
        
CHK: 
               cmp    [di], 0
               jne     NADDIT   
                                    
ADDIT: 
               inc dx
               add di, 1 
               dec bx
               cmp bx, 0 
               jne CHK 
               jmp CHK1 
                    
NADDIT:
               jmp CONT
                                                
CHK1:                   
               cmp cx, dx
               jne CONT
               inc [nCount] 
                    
CONT:
               pop di                      
               pop cx
               mov bx, cx 
               push cx
                   
copyproc:         
               mov di, [Array]
               mov [CopyArray], di
               add Array, 1 
               add CopyArray, 1
               dec cx            
               cmp cx, 0
               jne copyproc                   
               pop cx
               mov bx, cx 
               push cx  
                    
copyproc2:       
               dec Array
               dec CopyArray
               dec cx            
               cmp cx, 0
               jne copyproc2
               jmp     WHILE 
                                             
BREAK:
               mov     ah,     3Eh
               mov     bx,     [hFile]
               int     21h    
               jnc     SHOW_RESULT
               PRINT   errFileClose
        
SHOW_RESULT:                   
               PRINT   msgResult
               mov     ax,     [nCount]
               call    ShowUInt16    
CHANGE_FILE:    
               PRINT  delMessage 
               mov ah,01h
               int 21h
               cmp al,79h
               je DELETE_FILE 
               cmp al,59h
               je DELETE_FILE
               cmp al,6Eh
               je AGAIN
               cmp al,4Eh
               je AGAIN                          
               jmp CHANGE_FILE
DELETE_FILE:
               mov     ah,     41h  
               lea     dx,     [path_to_dir]
               int     21h  
               jnc     SUCCESS
SUCCESS:           
               PRINT   success_oper                
               jmp     AGAIN          
                  
CHECK:
               PRINT  checkMessage 
               mov ah,01h
               int 21h
               cmp al,79h
               je SUDA 
               cmp al,59h
               je SUDA
               cmp al,6Eh
               je ENDD
               cmp al,4Eh
               je ENDD   
               jmp AGAIN         
 
CHECK1:
               PRINT  checkMessage 
               mov ah,01h
               int 21h
               cmp al,79h
               je ENDD 
               cmp al,59h
               je ENDD
               cmp al,6Eh
               je SUDA
               cmp al,4Eh
               je SUDA   
               jmp AGAIN        

AGAIN:  
               PRINT  againMessage 
               mov ah,01h
               int 21h
               cmp al,79h
               je CHECK 
               cmp al,59h
               je CHECK
               cmp al,6Eh
               je CHECK1
               cmp al,4Eh
               je CHECK1   
               jmp AGAIN      
           SUDA:
jmp BEGIN               
 
           ENDD:
               mov     ax,     4C00h
               int     21h
main    endp
 
end     main