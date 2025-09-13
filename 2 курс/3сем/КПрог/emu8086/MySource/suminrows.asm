.MODEL SMALL
.STACK 100h

.DATA
matrix  DB 1, 2, 3, 4, 5, 6, 7, 8, 9  ; 3x3 matrix
rows    DW 3  ; number of rows
cols    DW 3  ; number of columns
newline DB 0Dh, 0Ah, '$'

.CODE
start:
    MOV AX, @DATA
    MOV DS, AX

    ; Initialize the matrix
    MOV SI, 0
    MOV CX, rows

    CalculateSums:
        ; Call the procedure to calculate the sum of numbers in the row
        MOV DI, SI
        CALL CalculateRowSum

        ; Display the sum
        MOV AH, 02h
        MOV DL, 'S'
        INT 21h

        ; Convert the sum to ASCII and display
        MOV AX, SI
        ADD AX, '0'
        MOV DL, AH
        INT 21h

        ; Display a new line
        MOV DX, OFFSET newline
        MOV AH, 09h
        INT 21h

        ADD SI, cols  ; Move to the next row
        LOOP CalculateSums

    ; Exit the program
    MOV AH, 4Ch
    INT 21h

; Procedure to calculate the sum of numbers in a row of the matrix
; Input:
;   DI - Index of the current row
; Output:
;   AL - Sum of the numbers in the row (8-bit)
CalculateRowSum PROC
    PUSH AX
    PUSH CX

    MOV CX, cols  ; Number of columns
    XOR AL, AL    ; Clear AL to accumulate the sum

CalculateSumLoop:
    ADD AL, [matrix + DI]  ; Add the current element to the sum
    INC DI  ; Move to the next element in the row
    LOOP CalculateSumLoop

    POP CX
    POP AX
    RET
CalculateRowSum ENDP

END start
