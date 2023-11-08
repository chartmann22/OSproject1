// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023

#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include "shared.hpp"

#define IPC_RESULT_ERROR (-1)

static int get_shared(char *filename, int size) {
    key_t key;

    // request a key
    // the key is linked to a filename, so that the other process can access it
    key = ftok(filename, 0);
    if (key == IPC_RESULT_ERROR) {
        return IPC_RESULT_ERROR;
    }

    // get shared block, create if it doesn't exist
    return shmget(key, size, 0644 | IPC_CREAT);

}

char * attach_memory(char *filename, int size) {
    int shared_bid = get_shared(filename, size);
    char *result;

    if(shared_bid == IPC_RESULT_ERROR) {
        return 0;
    }

    // map the shared block into this process's memory
    // and give a pointer to it
    result = shmat(shared_bid, NULL, 0);
    if (result == (char *)IPC_RESULT_ERROR) {
        return 0;
    }

    return result;
}

bool detach_memory(char *block) {
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory(char *filename) {
    int shared_bid = get_shared(filename, 0);

    if (shared_bid == IPC_RESULT_ERROR) {
        return NULL;
    }
    return (shmctl(shared_bid, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}
