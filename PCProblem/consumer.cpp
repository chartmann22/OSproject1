// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023


//
//consumer shared

#include "shared.hpp"
#include "shm.cpp"

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
    char *block = attach_memory(filename, BLOCK_SIZE);
    if(block == NULL) {
        printf("ERROR: couldn't get block\n");
        return -1;
    }

    while (true) {
        sem_wait(sem_prod);
        // pthread_mutex_lock(&mutexBuffer);

        if (strlen(block) > 0) {
            printf("Consuming: \"%s\"\n", block);
            bool done = (strcmp(block, "quit")==0);
            block[0] = 0;
            if (done) { break; }
        }
        // pthread_mutex_unlock(&mutexBuffer);
        sem_post(sem_cons);
    }

    sem_close(sem_cons);
    sem_close(sem_prod);

    detach_memory(block);

    return 0;
}



/*

int main(int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];

    // Initialize pthread
    pthread_mutex_init(&mutexBuffer, NULL);

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

    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}
*/
