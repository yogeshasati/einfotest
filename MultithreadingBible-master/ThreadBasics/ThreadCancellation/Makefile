obj:
	gcc -g -c master_slave1.c  master_slave1_async_cancellation.c  master_slave1_async_cancellation_cleanup_handlers.c

all:master_slave1.exe master_slave1_async_cancellation.exe master_slave1_async_cancellation_cleanup_handlers.exe

master_slave1.exe:
	gcc -g master_slave1.o -o master_slave1.exe -lpthread

master_slave1_async_cancellation.exe:
	gcc -g master_slave1_async_cancellation.o -o master_slave1_async_cancellation.exe -lpthread

master_slave1_async_cancellation_cleanup_handlers.exe:
	gcc -g master_slave1_async_cancellation_cleanup_handlers.o -o master_slave1_async_cancellation_cleanup_handlers.exe -lpthread

clean:
	rm *.o
	rm *exe
