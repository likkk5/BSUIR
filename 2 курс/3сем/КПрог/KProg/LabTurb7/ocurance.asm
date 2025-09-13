; Calculate the frequency of each character within a given string
; Assembly program to accept a sring as input and count the number of characters in it

; Author: Lakhya Jyoti Nath aka ljnath
; Email: ljnath@ljnath.com
; https://www.ljnath.com
; Dated: 18th March 2013


DATA_SEG    SEGMENT
    MSG1        DB  'Enter a string (MAX=100 characters): $'
    MSG2A       DB  13,10,'Occurance of character "$'
    NEW_LINE    DB  13,10,'$'
    MSG2B       DB  '" is : $'
    ARR_OFFSET  DW  ?
    ARR_OFF2    DW  ?
    ARR_STRING  DB  101 DUP(?)
    CHAR_COUNT  DW  0
    CHAR        DB  ?
DATA_SEG    ENDS


CODE_SEG    SEGMENT
    ASSUME CS: CODE_SEG, DS:DATA_SEG
        START:
            MOV     AX, DATA_SEG
            MOV     DS, AX

            MOV     AH,9
            MOV     DX,OFFSET MSG1
            INT     21H

            MOV     SI, OFFSET ARR_STRING
            MOV     DI,SI
            MOV     BX,0
            MOV     ARR_OFFSET, SI

            MOV     [SI],'20'
            INC     SI

        STRING_INPUT:
            MOV     AH,01
            INT     21H
            CMP     AL,13
            JZ      GET_TOTAL_CHAR
            MOV     [SI],AL
            INC     SI
            JMP     STRING_INPUT

        GET_TOTAL_CHAR:
            MOV     ARR_OFF2,SI
            DEC     ARR_OFF2
            JMP     ACCEPT_CHAR


        CHECK_NEXT_CHAR:
            MOV     SI, ARR_OFF2
            INC     SI

        ACCEPT_CHAR:
            INC     DI
            MOV     BL, [DI]

        DISPLAY_2ND_MSG:
            MOV     AH,9
            MOV     DX,OFFSET MSG2A
            INT     21H

            MOV     AH,2
            MOV     DL,BL
            INT     21H

            MOV     AH,9
            MOV     DX,OFFSET MSG2B
            INT     21H

            JMP     COUNT_CHAR


        COUNT_CHAR:
            DEC     SI
            CMP     [SI], BL
            JZ      COUNT_OCC
            CMP     ARR_OFFSET,SI
            JZ      REFRESH_REG
            JMP     COUNT_CHAR

        COUNT_OCC:
            INC     CHAR_COUNT
            JMP     COUNT_CHAR

        REFRESH_REG:
            MOV     AX,0
            MOV     AX,CHAR_COUNT
            MOV     BX,0
            MOV     CX,10

        BREAKING_NUM:
            MOV     DX,0
            DIV     CX
            PUSH    DX
            INC     BX
            CMP     AX,0
            JZ      DISPLAY_COUNT
            JMP     BREAKING_NUM


        DISPLAY_COUNT:
            POP     DX
            ADD     DX,48
            MOV     AH,02
            INT     21H
            DEC     BX
            CMP     BX,0
            JZ      LOOP_ALL_CHAR
            JMP     DISPLAY_COUNT

        LOOP_ALL_CHAR:
            CMP     ARR_OFF2,DI
            JZ      EXIT
            MOV     CHAR_COUNT,0
            MOV     AX,0
            MOV     BX,0
            MOV     CX,0
            MOV     DX,0
            JMP     CHECK_NEXT_CHAR


        EXIT:
            MOV     AH,4CH
            MOV     AL,0
            INT     21H

CODE_SEG    ENDS
   END  START
