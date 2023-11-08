// Caitlyn Hartmann
// Producer Consumer Problem
// Professor Guan
// 7 November 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shm.hpp"

int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("usage - %s (no args)", argv[0]);
        return -1;
    }

    if (destroy_memory(FILENAME)) {
        printf("Destroyed block: %s\n", FILENAME);
    } else {
        printf("Could not destroy block: %s\n", FILENAME);
    }
    return 0;
}