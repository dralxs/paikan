CC=gcc
CFLAGS= -Wall
TARGET = paikan

all: $(TARGET)

$(TARGET): paikan.o
	$(CC) $(CFLAGS) -o $(TARGET) paikan.o

paikan.o: paikan.c paikan.h
	$(CC) $(CFLAGS) -c paikan.c

clean:
	rm -f *.o $(TARGET)