
#include <iostream.h>
#include <stdio.h>

extern "C" void taimer();
extern "C" void exit();
extern "C" void colorize();
void print() {
    printf("Notification Settings:  \n");
    printf("1. Call signal           \n");
    printf("2. Change color of       \n");
    printf("    notification         \n");
    printf("3. Exit                  \n");
}
int main()
{
    int choice;
    short  color = 7;

    do {
        print();
        colorize();

        cout << "Choose the operation:\n";
        cin >> choice;

        switch (choice) {
        case 1:
            taimer();
            printf("Signal done!\n\n");
            break;
        case 2:
            color++;
            printf("You choose to change color!\n\n");
            break;
        case 3:
            exit();
            printf("Programm terminated!\n\n");
            break;           

        default:
            cout << "Invalid choice. Please choose a number between 1 and 3.\n";
            break;
        }
        cout << "If you want to continue press 1, else the program is finished:\n";
        cin >> choice;

    } while (choice == 1);


    return 0;
}
