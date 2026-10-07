CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = $(wildcard *.c)
TARGET = cpu

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)