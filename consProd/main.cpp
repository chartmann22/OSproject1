#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/fcntl.h>

const int TABLE_SIZE = 2;
const int MAX_ITEMS = 10;

// Shared variables
int table[TABLE_SIZE];
int tableIndex = 0;

// Semaphores
sem_t empty;  // Number of empty slots on the table
sem_t full;   // Number of filled slots on the table
sem_t mutex;  // Mutual exclusion for accessing the table

// Producer function
void producer() {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        // Produce an item
        int item = i + 1;

        // Wait for an empty slot
        sem_wait(&empty);
        sem_wait(&mutex);

        // Put the item on the table
        table[tableIndex] = item;
        tableIndex = (tableIndex + 1) % TABLE_SIZE;

        std::cout << "Producer produced item: " << item << std::endl;

        sem_post(&mutex);
        sem_post(&full);
    }
}

// Consumer function
void consumer() {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        // Wait for a filled slot
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume an item from the table
        int item = table[(tableIndex - 1 + TABLE_SIZE) % TABLE_SIZE];

        std::cout << "Consumer consumed item: " << item << std::endl;

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, TABLE_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    // Join threads
    producerThread.join();
    consumerThread.join();

    // Clean up semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
