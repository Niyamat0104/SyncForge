CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = syncforge
SRC = src/main.c
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)