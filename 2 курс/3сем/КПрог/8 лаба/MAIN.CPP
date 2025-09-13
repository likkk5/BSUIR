#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print() {
    printf("Good morning!\n\n");
    printf("+-------------------------+\n");
    printf("|   NOTIFICATION CONTROL  |\n");
    printf("|-------------------------|\n");
    printf("| WAKE UP!  :)   WAKE UP! |\n");
    printf("| Time to go to university|\n");
    printf("|                         |\n");
    printf("| Notification Settings   |\n");
    printf("|                         |\n");
    printf("| 1. Change duration of   |\n");
    printf("|    sound signal         |\n");
    printf("| 2. Change color of      |\n");
    printf("|    notification         |\n");
    printf("|                         |\n");
    printf("| Exit:                   |\n");
    printf("|   press 3               |\n");
    printf("+-------------------------+\n");
}

int main() {
    short n, m, row, column, color = 7;
    int dur = 600;
    int alarm_hour, alarm_minute;
      
    printf("Enter the alarm time in HH MM format (24-hour format): ");
    scanf("%d %d", &alarm_hour, &alarm_minute);

    while (1) {
 main: 
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);
    int current_hour = current_time->tm_hour;
    int current_minute = current_time->tm_min;

   if (alarm_hour > current_hour || (alarm_hour == current_hour && alarm_minute > current_minute)) {
        //printf("The alarm time has not yet arrived.\n");
    } else if (alarm_hour == current_hour && alarm_minute == current_minute) {
        printf("Wake up! It's time for the alarm.\n");
        asm {
            mov si, word ptr dur
        }
        generate_sound:
        asm {
            in al, 61h
            or al, 2
            out 61h, al

            call delay

            in al, 61h
            and al, 11111100b
            out 61h, al

            call delay

            dec si
            cmp si, 0
            jg generate_sound
        }

        print();

        asm {
            call colorize
        }

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            change_sound:
            dur *= 10;
            printf("You chose to change the duration of the sound signal.\n");
        } else if (choice == 2) {
            color++;
            printf("You chose to change the color of the notification.\n");
        } else if (choice == 3) {
            _exit:
            asm{
                mov ah, 00h 
                int 10h     
            }
            printf("Program terminated.\n");
            return 0;
        } else {
            printf("Incorrect input. Please enter 1, 2, or 3.\n");
        }
        asm {
            call colorize
            jmp main
        }
    } else {
        //printf("You're late! The alarm time has already passed.\n");
    }

        
    }

    asm {
            delay proc
            mov cx, 1000
        }
        _wait:
        asm {
            loop _wait
            ret
        delay endp
        }

    asm {
        colorize proc
    mov ah, 03h
    mov bh, 0 
    int 10h

    mov byte ptr n, dh
    mov byte ptr m, dl
    
    mov byte ptr row, 0
    mov byte ptr column, 0
}  
color_loop:
asm {
    mov ah, 02h    
    mov bh, 0     
    mov dh, byte ptr row     
    mov dl, byte ptr column    
    int 10h
    
    mov ah, 08h
    mov bh, 0
    int 10h 
    
    mov ah, 09h
    mov bh, 0
    mov bl, byte ptr color
    mov cx, 1
    int 10h
    
    inc byte ptr column
    cmp byte ptr column, 80
    jge __next_row       

    jmp color_loop
}
__next_row:
asm {
    inc byte ptr row
    mov byte ptr column, 0
    cmp byte ptr row, 25
    jl color_loop
    
    mov ah, 02h    
    mov bh, 0     
    mov dh, byte ptr n     
    mov dl, byte ptr m    
    int 10h
    
    ret
colorize endp
}
    
    return 0;
}