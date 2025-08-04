# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./..

# Source files
SRC = main.c ../ads1015.c ../ads1015_platform.c

# Output executable name
TARGET = ads1015_example

# Libraries to link (i2c-dev for I2C)
LDLIBS = -li2c

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Clean build artifacts
clean:
	rm -f $(TARGET)
