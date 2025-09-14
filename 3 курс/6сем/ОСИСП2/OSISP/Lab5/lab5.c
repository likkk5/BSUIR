#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_THREADS 10

int *arr;
int arr_size;
int num_threads;

// Структура для передачи параметров в поток
struct ThreadArgs {
    int start;
    int end;
};

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void *thread_sort(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs*)arg;
    printf("Поток сортирует кусок массива с %d по %d\n", args->start, args->end);
    
    printf("Массив до сортировки в потоке:\n");
    for (int i = args->start; i <= args->end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    qsort(&arr[args->start], args->end - args->start + 1, sizeof(int), compare);
    
    printf("Массив после сортировки в потоке:\n");
    for (int i = args->start; i <= args->end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_exit(NULL);
}

// Функция слияния отсортированных фрагментов массива
void merge(int left, int mid, int right) {
    int temp[right - left + 1];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i - left];
    }
}

// Рекурсивная функция сортировки слиянием
void merge_sort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main() {
    struct timeval start_time, end_time;
    pthread_t threads[MAX_THREADS];
    struct ThreadArgs thread_args[MAX_THREADS];
    int i;

    printf("Введите размер массива: ");
    scanf("%d", &arr_size);
    arr = (int*)malloc(arr_size * sizeof(int));

    printf("Введите количество потоков (не более %d): ", MAX_THREADS);
    scanf("%d", &num_threads);

    if (num_threads > MAX_THREADS || num_threads <= 0) {
        printf("Неверное количество потоков\n");
        return 1;
    }

    printf("Исходный массив:\n");
    srand(time(NULL));
    for (i = 0; i < arr_size; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    gettimeofday(&start_time, NULL); // Начало отсчета времени

    // Разбиение массива и создание потоков для сортировки каждого фрагмента
    for (i = 0; i < num_threads; i++) {
        thread_args[i].start = i * (arr_size / num_threads);
        thread_args[i].end = (i == num_threads - 1) ? arr_size - 1 : (i + 1) * (arr_size / num_threads) - 1;
        pthread_create(&threads[i], NULL, thread_sort, (void*)&thread_args[i]);
    }

    // Ожидание завершения всех потоков
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Слияние отсортированных фрагментов
    merge_sort(0, arr_size - 1);

    gettimeofday(&end_time, NULL); // Конец отсчета времени
    
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Отсортированный массив:\n");
    for (i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Время выполнения: %.5f секунд\n", execution_time);

    free(arr);
    return 0;
}