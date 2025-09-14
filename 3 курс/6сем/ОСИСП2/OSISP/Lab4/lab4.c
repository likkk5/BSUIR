#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#define NUM_BLOCKS 5
#define BLOCK_SIZE 100

typedef struct {
    int data[BLOCK_SIZE];
    pthread_mutex_t mutex;
} BlockData;

void process_data(BlockData *block) {
    printf("Processing block...\n");
    srand(time(NULL));
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block->data[i] = rand() % 100;
    }
    sleep(1);
    printf("Block processed.\n");
}

int main() {
    int shm_id;
    BlockData *shared_mem;
    int i;

    // Создание сегмента разделяемой памяти
    shm_id = shmget(IPC_PRIVATE, NUM_BLOCKS * sizeof(BlockData), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    // Присоединение сегмента к адресному пространству процесса
    shared_mem = shmat(shm_id, NULL, 0);
    if ((int)shared_mem == -1) {
        perror("shmat");
        exit(1);
    }

    // Инициализация блоков данных и мьютексов
    for (i = 0; i < NUM_BLOCKS; i++) {
        pthread_mutex_init(&shared_mem[i].mutex, NULL);
    }

    // Создание процессов для параллельной обработки данных
    for (i = 0; i < NUM_BLOCKS; i++) {
        if (fork() == 0) {
            // Дочерний процесс
            printf("Child process %d created.\n", getpid());
            printf("Child process %d is processing block %d.\n", getpid(), i);
            pthread_mutex_lock(&shared_mem[i].mutex); // Блокировка блока данных
            process_data(&shared_mem[i]);
            pthread_mutex_unlock(&shared_mem[i].mutex); // Разблокировка блока данных
            printf("Child process %d exiting.\n", getpid());
            exit(0);
        }
    }

    // Ожидание завершения всех дочерних процессов
    for (i = 0; i < NUM_BLOCKS; i++) {
        wait(NULL);
    }

    // Удаление мьютексов
    for (i = 0; i < NUM_BLOCKS; i++) {
        pthread_mutex_destroy(&shared_mem[i].mutex);
    }

    // Отключение сегмента от адресного пространства процесса
    shmdt(shared_mem);

    // Удаление сегмента разделяемой памяти
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}