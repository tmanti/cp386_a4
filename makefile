#Do not edit the contents of this file.
CC = gcc
CFLAGS = -std=gnu99
TARGET = allocation  
OBJFILES = allocation.o
all: $(TARGET)

allocation: 200188260_190555710_allocation.c
	$(CC) $(CFLAGS) -o allocation 200188260_190555710_allocation.c
	
run: allocation
	./allocation 1048576
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 