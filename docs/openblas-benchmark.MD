# OpenBLAS Simplified Benchmark Guideline

The whole guideline is based on Musebook(Spacemit M1) with Fedora 42.

## 1. Download
Clone the OpenBLAS repo with the lastest version
```bash
wget https://github.com/OpenMathLib/OpenBLAS/archive/refs/tags/v0.3.30.tar.gz
tar zxvf v0.3.30.tar.gz
```

## 2. Compilation
```bash
dnf install make gcc g++ gfortran
cd OpenBLAS-v0.3.30
# For RISCV64 GENERIC build
make TARGET=RISCV64_GENERIC -j $(nproc)
# For RISCV64 ZVL128B/256B build
make TARGET=RISCV64_ZVL128B -j $(nproc)
make TARGET=RISCV64_ZVL256B -j $(nproc)
```

## 3. Compiling the benchmark
No need to make install, just go to benchmark folder and compile.
```bash
cd benchmark
make TARGET=RISCV64_XXXX -j $(nproc)
```

## 4. Testing
```bash
OPENBLAS_LOOPS=1000 ./sgemm.goto 1 256 1
```
Here OPENBLAS_LOOPS means to loop 1000 times, and for matrix size 1 to 256 with the step set to 1

The results will be shown like the following:

```
           SIZE               Flops            Time
 M=   1, N=   1, K=   1 :        3.43 MFlops   0.000584 sec
 M=   2, N=   2, K=   2 :       26.44 MFlops   0.000605 sec
 M=   3, N=   3, K=   3 :       70.16 MFlops   0.000770 sec
 M=   4, N=   4, K=   4 :      146.02 MFlops   0.000877 sec
  M=   5, N=   5, K=   5 :      202.06 MFlops   0.001237 sec
```
