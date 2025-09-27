# RISC-V V (RVV) 1.0 Verification Test

This project contains a simple C program that uses $\text{RISC-V V}$ (Vector) extension intrinsics to perform vector addition. It is intended to verify the following on the $\text{K1}$ development board running $\text{GCC 15.1}$:

1.  Successful compilation of $\text{RVV 1.0}$ code.

2.  Correct execution of $\text{RVV}$ instructions, including proper handling of the vector tail (strip-mining).

3.  Compatibility with the $\text{GDB}$ debugger for inspecting vector registers.

4.  Functionality of the $\text{Perf}$ performance analysis tool.

## Files

  * `rvv_test.c`: The vector addition test program.

  * `Makefile`: Automates the build, run, and cleanup processes.

## Build and Run

### 1\. Build the Executable

The compilation command uses $\text{-march=rv64gcv}$ to enable the vector extension and $\text{-g}$ for $\text{GDB}$ debugging.

```
make

```

### 2\. Run the Test

The program will execute the vector addition, print the hardware's $\text{VLEN}$ capability, and report success or failure.

```
./rvv_test

```

### 3\. Debugging (GDB)

Use the built-in debugging target to launch the program under $\text{GDB}$:

```
make debug

```

Once inside $\text{GDB}$, use commands like `b vector_add`, `run`, and `info all-registers` to verify $\text{RVV}$ register visibility.

### 4\. Performance Analysis (Perf)

Measure the program's basic performance metrics using the $\text{Perf}$ tool:

```
make perf

```

### 5\. Clean Up

Remove the generated executable file:

```
make clean

```
