// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023


//producer shared
#include "shared.hpp"
#include "shm.cpp"

#define BLOCK_SIZE 4096
#define NUM_ITERATIONS 10

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("usage - %s [stuff to produce]", argv[0]);
        return -1;
    }

    // setup
    sem_t *sem_prod = sem_open(SEM_PRODUCER_FNAME, 0);
    if (sem_prod == SEM_FAILED) {
        perror("sem_open/producer");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_cons = sem_open(SEM_CONSUMER_FNAME, 0);
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

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(sem_cons); //wait for signal from consumer
        // pthread_mutex_lock(&mutexBuffer);

        printf("Producing: \"%s\"\n", argv[1]);
        strncpy(block, argv[1], BLOCK_SIZE);
        
        // pthread_mutex_unlock(&mutexBuffer);
        sem_post(sem_prod); //signal that something has been produced
    }

    sem_close(sem_cons);
    sem_close(sem_prod);

    detach_memory(block);

    return 0;
}

