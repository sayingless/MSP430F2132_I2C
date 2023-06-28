# Makefile for MSP430 project
DEVICE = msp430f2132

SUPPORT_FILE_DIRECTORY = /Users/giancui/ti/msp430-gcc/include
# Compiler
CC = msp430-elf-gcc
CC_HEX = msp430-elf-objcopy

# Compiler flags
CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -T $(DEVICE).ld

# Source files
SRCS = *.c

# Target file
TARGET = builds/output.elf
TARGET_HEX = builds/output.hex

# Default target
all:
	$(CC) $(CFLAGS) $(LFLAGS) -o $(TARGET) $(SRCS) && ${CC_HEX} -O ihex $(TARGET) $(TARGET_HEX)

# Clean up
clean:
	rm -f $(TARGET) $(TARGET_HEX)
