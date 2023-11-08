// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023

#ifndef SHM_H
#define SHM_H

#include <stdbool.h>
/*
#include <pthread.h>
#include <time.h>
#include <sys/mman.h>
*/

//#include <sys/stat.h>        /* For mode constants */
//#include <fcntl.h>           /* For O_* constants */

#define THREAD_NUM 8

/*
// Semaphores
sem_t empty; // Number of empty slots on the table
sem_t full; // Number of filled slots on the table

pthread_mutex_t mutexBuffer; // Mutual exclusion for accessing the table

// Shared variables
int buffer[10];
int count = 0;
*/

// attach a shared memory block associated w/ file name
// create if it doesn't exist
char * attach_memory(char *filename, int size);
bool detach_memory(char *block);
bool destroy_memory(char *filename);

#define BLOCK_SIZE 4096
#define FILENAME "producer.cpp"
#define IPC_RESULT_ERROR (-1)

#define SEM_PRODUCER_FNAME "/myproducer"
#define SEM_CONSUMER_FNAME "/myconsumer"

#endif
