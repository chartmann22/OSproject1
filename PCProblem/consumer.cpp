// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023



//consumer shared
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#include "shm.hpp"

int main(int argc, char *argv[0]){
    if (argc != 1) {
        printf("usage = %s //no args", argv[0]);
        return -1;
    }
    // setup semaphores
    sem_unlink(SEM_CONSUMER_FNAME);
    sem_unlink(SEM_PRODUCER_FNAME);

    sem_t *sem_prod = sem_open(SEM_PRODUCER_FNAME, IPC_CREAT, 0660, 0);
    if (sem_prod == SEM_FAILED) {
        perror("sem_open/producer");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_cons = sem_open(SEM_CONSUMER_FNAME, IPC_CREAT, 0660, 1);
    if (sem_cons == SEM_FAILED) {
        perror("sem_open/consumer");
        exit(EXIT_FAILURE);
    }

    // grab the shared memory block
    char *block = attach_memory(FILENAME, BLOCK_SIZE);
    if(block == NULL) {
        printf("ERROR: couldn't get block\n");
        return -1;
    }

    while (true) {
        sem_wait(sem_prod);
        if (strlen(block) > 0) {
            printf("Consuming: \"%s\"\n", block);
            bool done = (strcmp(block, "quit")==0);
            block[0] = 0;
            if (done) { break; }
        }
        sem_post(sem_cons);
    }

    sem_close(sem_cons);
    sem_close(sem_prod);

    detach_memory(block);

    return 0;
}



/*

#include "shm.hpp"

// Consumer function
void* consumer(void* args) {
    while (1) {
        int y;

        // Wait for a filled slot
        sem_wait(&full);
        pthread_mutex_lock(&mutexBuffer);

        // Consume an item from the table
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&empty);

        // Out
        std::cout << "Consumer consumed item: " << y << std::endl;
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[THREAD_NUM];

    // Initialize pthread
    pthread_mutex_init(&mutexBuffer, NULL);

    // Initialize semaphores
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    int i;

    // Create producer and consumer threads
    for (i = 0; i < THREAD_NUM; i++) {
        if (i > 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    // Join threads
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    // Clean up semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}
*/