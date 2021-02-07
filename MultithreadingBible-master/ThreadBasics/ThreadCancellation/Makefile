CC = gcc
CFLAGS = -Wall -g
LINKER = -o
LD = -lpthread

PROG1 = master_slave1.exe
PROG2 = master_slave1_async_cancellation.exe
PROG3 = master_slave1_async_cancellation_cleanup_handlers.exe

OBJ1 = master_slave1.o
OBJ2 = master_slave1_async_cancellation.o
OBJ3 = master_slave1_async_cancellation_cleanup_handlers.o

all:$(PROG1) $(PROG2) $(PROG3)
#obj:
#	gcc -g -c master_slave1.c  master_slave1_async_cancellation.c  master_slave1_async_cancellation_cleanup_handlers.c

$(PROG1): $(OBJ1)
	@echo "---------------------------------------------"
	@echo Compiling and creating master_slave executable
	@echo "---------------------------------------------"
	$(CC)  master_slave1.c $(LINKER) $(PROG1) $(LD)

$(PROG2): $(OBJ2)
	@echo "---------------------------------------------"
	@echo Compiling and creating  master_slave1_async_cancellation executable
	@echo "---------------------------------------------"
	$(CC)  master_slave1_async_cancellation.c $(LINKER)  $(PROG2) $(LD)

$(PROG3): $(OBJ3)
	@echo "---------------------------------------------"
	@echo Compiling and creating master_slave1_async_cancellation_cleanup_handlers executable
	@echo "---------------------------------------------"
	$(CC)  master_slave1_async_cancellation_cleanup_handlers.c $(LINKER)  $(PROG3) $(LD)

#	mv master_slave1.o $(pwd)/obj/ 
clean:
	@echo "---------------------------------------------"
	@echo Cleaning
	@echo "---------------------------------------------"
	rm -f *.o  *.exe

#%o:%c
#	$(CC) $<
#
#
#
