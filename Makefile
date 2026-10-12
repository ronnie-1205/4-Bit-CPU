CC       := gcc
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -O2
TARGET   := cpu_tests
SOURCES  := main.c gates.c adder.c mux.c alu.c latches.c flipflop.c clock.c registers.c
OBJECTS  := $(SOURCES:.c=.o)
HEADERS  := $(wildcard *.h)

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

test run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
