TARGET = serialization-test

MAKEFLAGS += --no-print-directory

LIBS = -lcspecs 

CC = gcc

CFLAGS = -L"libSerializacion/Debug" -o "serialization-test"  ./src/serialization-test.o   -lcspecs -llibSerializacion

INVFLAGS = -I"libSerializacion/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/serialization-test.d" -MT"src/serialization-test.o" -o "src/serialization-test.o" "src/serialization-test.c"

all: default

default:
	$(MAKE) libcompile
	$(MAKE) invoker
	$(MAKE) test

test:
	@echo "Building test ..."
	$(CC) $(CFLAGS)

invoker:
	@echo "Invoking libSerializacion ..."
	$(CC) $(INVFLAGS)

libcompile:
	@echo "Compiling libSerializacion ..."
	cd libSerializacion/Debug && $(MAKE) clean all

clean:
	-rm -f src/*.o
	-rm -f src/*.d
	-rm -f $(TARGET)