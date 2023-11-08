# Project1PC
 Producer Consumer Problem

 The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ g++ producer.cpp -pthread -lrt -o producer
$ g++ consumer.cpp -pthread -lrt -o consumer
$ ./producer & ./consumer


## Following the criteria
The files used in this project are producer.cpp, consumer.cpp, shm.hpp, shm.cpp, destroyshm.cpp (used seldomly for cleanup), and a Makefile. The command for the make is # make PCP #. This will compile the files using g++ and run them. The main focus for this project was understanding shared memory, and how to get it between two processes.

## The Challenges

