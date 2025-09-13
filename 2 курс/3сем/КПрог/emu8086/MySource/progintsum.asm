.MODEL SMALL
.STACK 100h

.DATA
matrix   DW 1, 2, 3, 4, 5, 6, 7, 8, 9 ; 3x3 matrix
newline  DB 0Dh, 0Ah, '$'

.CODE
start:
    MOV AX, @DATA
    MOV DS, AX

    ; Initialize matrix
    MOV SI, 0
    MOV CX, 3 ; Number of rows

    CalculateSums:  
        call  INTERRUPT_33
        ; Call the interrupt to calculate the sum for the current row
        MOV AX, 0   ; Clear AX to accumulate the sum
        MOV BX, SI  ; Index of the current row
        INT 21h

        ; Convert the sum to ASCII and display
        ADD AX, '0'
        MOV DL, AH
        MOV AH, 02h
        INT 21h

        ; Display a new line
        MOV DX, OFFSET newline
        MOV AH, 09h
        INT 21h

        ADD SI, 6   ; Move to the next row (3 columns * 2 bytes per element)
        LOOP CalculateSums

    ; Exit the program
    MOV AH, 4Ch
    INT 21h

; Interrupt 33h - Calculate sum of numbers in the row
; Input:
;   BX - Index of the current row
; Output:
;   AX - Sum of the numbers in the row  

INTERRUPT_33 PROC
    PUSH AX
    PUSH CX

    MOV CX, 3   ; Number of columns
    XOR AX, AX  ; Clear AX to accumulate the sum

    ; Calculate sum loop
CalculateSumLoop:
    ADD AX, [matrix + BX] ; Add the current element to the sum
    ADD BX, 2   ; Move to the next element in the row
    LOOP CalculateSumLoop

    POP CX
    POP AX
    IRET
INTERRUPT_33 ENDP

END start
