# Makefile for RVV 1.0 Verification Test on K1 Board

# Variables
CC = gcc
TARGET = rvv_test
SOURCE = rvv_test.c

# Compilation Flags:
# -march=rv64gcv: Enables RISC-V 64-bit general (g), and Vector (v) extensions.
# -O2: Optimization level to encourage vectorization.
# -g: Include debugging information (essential for GDB).
CFLAGS = -march=rv64imafdcv -mabi=lp64d -O2 -g
# -D__riscv_vector -std=gnu11
# -march=rv64imafdcv_zvl256b -mabi=lp64

# Default target: Compile the program
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(SOURCE) -o $(TARGET) $(CFLAGS)

# Run target: Execute the compiled program
run: $(TARGET)
	./$(TARGET)

# Debug target: Start GDB for the compiled program
debug: $(TARGET)
	gdb ./$(TARGET)

# Perf target: Run performance statistics using perf stat
perf: $(TARGET)
	perf stat ./$(TARGET)

# Clean target: Remove the executable
clean:
	rm -f $(TARGET)

.PHONY: all run debug perf clean
