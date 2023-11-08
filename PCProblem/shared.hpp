// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023

#ifndef SHM_HP
#define SHM_HP

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>


#define THREAD_NUM 8

pthread_mutex_t mutexBuffer; // Mutual exclusion for accessing the table


// attach a shared memory block associated w/ file name
// create if it doesn't exist
char * attach_memory(char *filename, int size);
bool detach_memory(char *block);
bool destroy_memory(char *filename);

#define BLOCK_SIZE 4096
//#define FILE "producer.cpp"
char filename[] = "producer.cpp";
#define IPC_RESULT_ERROR (-1)

#define SEM_PRODUCER_FNAME "/myproducer" // names for semaphores
#define SEM_CONSUMER_FNAME "/myconsumer"

#endif
