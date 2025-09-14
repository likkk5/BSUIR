#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

void bubbleSort(long list[], long n) {
    long c, d, t;
    int i = 0;
    while (i < 10) {
        i++;
    }
    for (c = 0; c < (n - 1); c++) {
        for (d = 0; d < n - c - 1; d++) {
            if (list[d] > list[d + 1]) {
                t = list[d];
                list[d] = list[d + 1];
                list[d + 1] = t;
            }
        }
    }
}

int main() {
    int x = 0;
    int z = 1;
    if (x >= 1) {
        int y = 0;
    } else {
        x++;
        x = x + z;
        z += x;
    }
    int c = sum(2, 3);
    printf("Characters: %c %c \n", 'a', 65);
    long arr[] = {1, 2, 3};
    bubbleSort(arr, 3);
    z++;
    return 0;
}
