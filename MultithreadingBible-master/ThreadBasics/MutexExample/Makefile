MutexDemo:mutex_example_with_mutex.o
	gcc -g mutex_example_with_mutex.o -o MutexDemo -lpthread
mutex_example.o:mutex_example_with_mutex.c
	gcc -g -c mutex_example_with_mutex.c -o mutex_example_with_mutex.o
clean:
	rm mutex_example_with_mutex.o
	rm MutexDemo
