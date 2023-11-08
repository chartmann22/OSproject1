# Project1PC
 Producer Consumer Problem

 The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ g++ producer.cpp -pthread -lrt -o producer
$ g++ consumer.cpp -pthread -lrt -o consumer
$ ./producer & ./consumer


#### Following the criteria
The files used in this project are producer.cpp, consumer.cpp, shared.hpp, shm.cpp, destroyshm.cpp (used seldomly for cleanup), and a Makefile. The command for the make is # make PCP #. This will compile the files using g++ and run them. The main focus for this project was understanding shared memory, and how to get it between two processes.

#### Overview
The main files, producer.cpp and consumer.cpp, are exactly what you'd imagine. They are the producer process and consumer process, respectively. The shared.hpp holds global definitions and includes, and the shm.cpp has the function definitions I created for managing memory. The Makefile and destroyshm.cpp were for convenience. 

#### The Challenges
I struggled for a long time to get the semaphore includes recognized. The path in my environment variables wasn't right. I had to change the compiler path, and then I gave up on going through VScode and worked directly through WSL (Windows Subsystem for Linux). The shared memory got a bit complicated and I spent most of my time on that, not yet getting it to compile. I intended to implement the threads better but I ran out of time here and wanted to get a good commit in. I'll continue working on this this week and hopefully I'll be able to complete it better.

#### Conclusion
This was rough, sorry.
