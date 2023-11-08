###############################################################
# Compile PCP
#
msg:
	@echo 'Targets are:'
	@echo '  PCP     - Compile


###############################################################
# Compile PCP
#
PCP: shm.hpp producer.cpp consumer.cpp shm.cpp
	$ g++ producer.cpp -pthread -lrt -o producer
	$ g++ consumer.cpp -pthread -lrt -o consumer
	$ ./producer & ./consumer

###############################################################
# Clean
#
Clean: destroyshm.cpp
	$ g++ destroyshm.cpp -pthread -lrt -o destroyshm
	$ ./destroyshm
