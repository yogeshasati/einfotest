rm *.o
rm *exe
gcc -g -c master_slave1.c -o master_slave1.o
gcc -g -c master_slave1_async_cancellation.c -o master_slave1_async_cancellation.o
gcc -g master_slave1.o -o master_slave1.exe -lpthread
gcc -g master_slave1_async_cancellation.o -o master_slave1_async_cancellation.exe -lpthread
gcc -g -c master_slave1_async_cancellation_cleanup_handlers.c -o master_slave1_async_cancellation_cleanup_handlers.o
gcc -g master_slave1_async_cancellation_cleanup_handlers.o -o master_slave1_async_cancellation_cleanup_handlers.exe -lpthread
