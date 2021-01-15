CC = gcc
CFLAGS = -Wall
LDFLAGS = -lpthread
OBJFILES = sema_test.o
TARGET = semaptest

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~

