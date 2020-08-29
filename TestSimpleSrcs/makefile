TARGET = serialization-test

LIBS = -lcspecs

CC = gcc

CFLAGS = -g -Wall

.PHONY: default all clean

default: clean $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

%.o: %.c $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)