.MODEL small
org 100h
.DATA 
final_message db "Average value of array elements:",0Ah, 0Dh, "$" 
msg1 db "Enter the size of array:",0Ah, 0Dh, "$"
msg2 db "Enter the element:",0Ah, 0Dh, "$"
msg_error_size db "Incorrect size, try again!",0Ah, 0Dh, "$"
msg_error db "Incorrect data,try again!",0Ah, 0Dh, "$"

NumMaxLength db 7   ;the value is 7, because we need to limit the entered value. the maximum amount of chars is 7 (-32768 +enter)
EnterredValue db 9 dup('$') ;it's designed to store ascii codes of each component of the inputted number ;its value is 9 because the input starts from the third byte and the max length is 7
NumBuf dw 0 
minus db 0
res_string db 4 dup('$') ;here element(s) and its occurrence(s) will be stored and outputted 
max_size dw 30
tmp dw 0
size dw ? ;variable to store the array's size
array dw max_size dup($)
aux_indexes_array dw max_size($) ;auxiliary array to store positions of elements, that are not unique 
sum dw 0 ;
.STACK 300h
.CODE
start:
    ;macro to print messages
    print macro out_str
    mov dx,offset out_str
    mov ah,9
    int 21h
    endm
    
    ;macro to go to the next line
    new_line macro
    mov ah,2 ;load the number of function responsible for output a symbol
    mov dl,10 ;ascii code of new line
    int 21h ;call function 2h
    mov dl,13 ;ascii code of carriage return
    int 21h ;call function 2h 
    endm

    ;main program
    ;here we set the array's size and its elements,we are looking for 
    ;the element with the biggest occurrence 
    ;and output the result
    print msg1
    call SetSize
    call InputArray
    CalculateAverage
   
;procedure to set array's size
SetSize proc
    mov cx, 1 ;the counter for inputArrayLengthLoop           
    inputSize:
       push cx ;in order not to loose the counter, push it to stack
       call Check_Transform_InputedElement ;here we check if the input was correct
       pop cx ;restore counter
       mov size,ax ;the result was stored at ax, we move it to the size variable
       cmp size,0 ;check, if it is equal or less than 0
       jle sizeError ;if so, output the error message 
       cmp size,30 ;if size is greater than 30, output the error message
       jg  sizeError                     
    loop inputSize     
    ret      
endp

;procedure to check the input and transform it to a number
Check_Transform_InputedElement proc                                     
    mov ax,0
    mov cx,0
    mov al,NumMaxLength 
    mov [EnterredValue],al
    mov [EnterredValue +1],0
    lea dx,EnterredValue ;load effective address of the string to DI, it's necessary for the following input procedure
    ;entered values will be stored in EnterredValue  
    call input ;input the number
    mov cl,[EnterredValue+1] ;load the length of the inputted value into cl, this will be the counter
    lea si, EnterredValue;load effective address of the string to SI
    add si,2 ;skip two first bytes (they're not related to the inputted number)
    mov ax,0 
    mov bx,0
    mov dx,10 ;this value will be used in multiply operation        
    Next:
         mov ax,0
         lodsb ;load the first byte of the inputted number in al
         cmp bl,0 ;if it's the first char (bx is 0), we should check if it's minus or not
         je checkMinus
    
    checkSym:
         ;here we check if inputted data was correct (ascii code between 48 and 57)
         ;if not, there's an error
         cmp al,'0' 
         jl errorNum
         cmp al,'9'
         jg errorNum
         
         sub ax,'0';transform the ascii code of our char to a decimal code
         mov bx,ax ;save it to BX
         mov ax,NumBuf ;load a value from NumBuffer to AX, it will be used in arithmetical operation 
         
         imul dx ;multiply AX and DX,result in AX, DX-10, we recreate the number
         jo errorNum ;if there's overflow - error
         cmp minus,1 ;if the number is negative, instead of add operation, do substract operation
         je SubOperation
         add ax, bx ;add BX to AX
         
         comeBack:
         jo errorNum ;check if there's overflow (for negative numbers)
         mov NumBuf,ax ;load new data to NumBuf
         mov bx,1
         mov dx,10
    loop Next 
    
    mov ax,NumBuf ;when loop is finished, load the number into AX
    mov minus,0 ;reset minus variable
    finish: 
    mov NumBuf,0 ;reset NumBuf                      
    ret ;finish the procedure
SubOperation:
    sub ax,bx ;subtract  operation for negative numbers
    jmp comeBack
           
checkMinus:
    inc bl ;we won't have any minuses anymore, that's why bx is set to 1
    cmp al, '-'
    je SetMinus ;if the first char was minus, take it to account
    jmp checkSym ;else just check the symbol
                  
SetMinus:
    mov minus,1 ;variable minus is set to 1
    dec cx ;decrement the counter
    cmp cx,0
    je errorNum ;if the counter is 0 - we have inputted only minus, so it's an error
    jmp Next ;go to the next char
    
errorNum:
    clc ;reset c flag if the was a borrow/carry
    mov minus,0 ;reset minus variable
    print msg_error ;print error message using macro
    mov NumBuf, 0 ;reset NumBuffer
    jmp Check_Transform_InputedElement ;restart the process                            
endp

;procedure to input data
input proc 
    mov ah,0Ah ;read a buffer
    int 21h
    new_line ;macro to go to the next line
    ret
input endp

;procedure to input the array
InputArray proc 
    mov di,0                                                               
    mov cx,size ;load size to the counter           
    InputArrayLoop:
       print msg2 ;invitation to enter an element
       push cx ;save cx in stack            
       call Check_Transform_InputedElement ;check if the entered string was correct and transform it to a number
       pop cx ;restore counter     
       mov array[di], ax ;mov the entered value from AX to a position in array
       add di,2 ;carry DI to the next position (2 because dw)                     
    loop InputArrayLoop           
    ret  
endp

;macro to output a number (we need to transform the number into a string)
output_number macro
    local division
    local transfrom_and_output
    local exit
    ;the number of lines is stored in ax
    push ax
    push cx
    push -1; break condition
    mov cx, 10
division:
    mov dx,0
    mov ah,0
    div cl; al - entire part, ah - remainder
    mov dl, ah ;save remainder to stack
    push dx ;save rests in stack
    cmp al, 0 ;continue until the entire part is 0
    jne division
    
    mov ah, 2 ;interrupt func to output a symbol
    
transfrom_and_output: ;transformation to ascii
    pop dx ;remove one rest
    cmp dx, -1; if -1 break (it was our break condition)
    je exit ;if so, finish the process
    add dl, '0'; ascii code transformation
    int 21h ;output that symbol
    jmp transfrom_and_output
exit:
    mov dl, ' '
    int 21h
    pop cx
    pop ax
endm
 
; macro to calculate the average value of array elements
CalculateAverage macro
    local loop_start, loop_end, finish
    ; Declare local labels for control flow within the macro
    ; mov di, size ; Uncomment this line if DI needs to be initialized with the size counter
    mov ax, size         ; Load the size of the array into AX
    mov dx, 2            ; Set DX to 2 (for multiplication and division)
    mul dx               ; Multiply AX by DX, result in DX:AX (double of the size)
    mov di, ax           ; Move the result (double of the size) into the DI register (used as a counter)
    mov sum, 0           ; Initialize the sum variable to 0 (accumulator)
    print final_message  ; Print a message indicating the start of the calculation

loop_start:
    sub di, 2            ; Decrement DI by 2 to access each element of the array (assuming each element is a word)
    mov ax, [array + di] ; Load the array element into AX
    add sum, ax          ; Add the array element to the running sum
    cmp di, 0            ; Compare DI with 0
    je finish            ; Jump to finish if DI is 0 (end of loop)
    jne loop_start       ; Jump to loop_start if DI is not 0

finish:
    mov dx, size         ; Load the size of the array into DX
    mov ax, sum          ; Load the sum into AX
    idiv dl              ; Divide AX by DL (size)
    mov ax, dx           ; Store the result of the division (average value) into AX
    jmp loop_end         ; Jump to loop_end

loop_end:
    output_number        ; Call the output_number macro to print the average value
endm
 
sizeError: ;when the array's size is greater than 30 or less than 1
    print msg_error_size 
    jmp  inputSize 
      
end start