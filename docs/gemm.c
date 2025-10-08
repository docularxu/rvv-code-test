#include "bench.h"
#include <stdio.h>
#include <stdlib.h>

#undef GEMM

#ifndef COMPLEX

#ifdef DOUBLE
#define GEMM BLASFUNC(dgemm)
#elif defined(BFLOAT16) && defined(BGEMM)
#define GEMM BLASFUNC(bgemm)
#elif defined(BFLOAT16)
#define GEMM BLASFUNC(sbgemm)
#undef IFLOAT
#define IFLOAT bfloat16
#elif defined(HFLOAT16)
#define GEMM BLASFUNC(shgemm)
#undef IFLOAT
#define IFLOAT hfloat16
#else
#define GEMM BLASFUNC(sgemm)
#define IFLOAT float
#endif

#else

#ifdef DOUBLE
#define GEMM BLASFUNC(zgemm)
#else
#define GEMM BLASFUNC(cgemm)
#endif

#endif

int main(int argc, char *argv[]) {

    IFLOAT *a, *b;
    FLOAT *c;
#ifdef BGEMM
    blasint one = 1;
    blasint two = 2;
    float alpha_in[] = {1.0, 0.0};
    float beta_in[] = {0.0, 0.0};
    FLOAT alpha[2], beta[2];
    sbstobf16_(&two, alpha_in, &one, alpha, &one);
    sbstobf16_(&two, beta_in, &one, beta, &one);
#else
    FLOAT alpha[] = {1.0, 0.0};
    FLOAT beta[] = {0.0, 0.0};
#endif
    char transa = 'N';
    char transb = 'N';
    blasint m, n, k, i, j, lda, ldb, ldc;
    int loops = 1;
    int has_param_m = 0;
    int has_param_n = 0;
    int has_param_k = 0;
    char *p;

    int from = 1;
    int to = 200;
    int step = 1;

    double time1, timeg;

    argc--;
    argv++;

    if (argc > 0) { from = atol(*argv); argc--; argv++; }
    if (argc > 0) { to = MAX(atol(*argv), from); argc--; argv++; }
    if (argc > 0) { step = atol(*argv); argc--; argv++; }

    if ((p = getenv("OPENBLAS_TRANS"))) {
        transa = *p;
        transb = *p;
    }
    if ((p = getenv("OPENBLAS_TRANSA"))) {
        transa = *p;
    }
    if ((p = getenv("OPENBLAS_TRANSB"))) {
        transb = *p;
    }
    TOUPPER(transa);
    TOUPPER(transb);

    fprintf(stderr, "From : %3d  To : %3d Step=%d : Transa=%c : Transb=%c\n", from, to, step, transa, transb);

    p = getenv("OPENBLAS_LOOPS");
    if (p != NULL) {
        loops = atoi(p);
    }

    if (loops > 1) {
        fprintf(stderr, "Looping %d times.\n", loops);
    }

    if ((p = getenv("OPENBLAS_PARAM_M"))) {
        m = atoi(p);
        has_param_m = 1;
    } else {
        m = to;
    }
    if ((p = getenv("OPENBLAS_PARAM_N"))) {
        n = atoi(p);
        has_param_n = 1;
    } else {
        n = to;
    }
    if ((p = getenv("OPENBLAS_PARAM_K"))) {
        k = atoi(p);
        has_param_k = 1;
    } else {
        k = to;
    }

    if ((a = (IFLOAT *)malloc(sizeof(IFLOAT) * m * k * COMPSIZE)) == NULL) {
        fprintf(stderr, "Out of Memory!!\n");
        exit(1);
    }
    if ((b = (IFLOAT *)malloc(sizeof(IFLOAT) * k * n * COMPSIZE)) == NULL) {
        fprintf(stderr, "Out of Memory!!\n");
        exit(1);
    }
    if ((c = (FLOAT *)malloc(sizeof(FLOAT) * m * n * COMPSIZE)) == NULL) {
        fprintf(stderr, "Out of Memory!!\n");
        exit(1);
    }

#ifdef __linux
    srandom(getpid());
#endif

    for (i = 0; i < m * k * COMPSIZE; i++) {
        a[i] = ((IFLOAT)rand() / (IFLOAT)RAND_MAX) - 0.5;
    }
    for (i = 0; i < k * n * COMPSIZE; i++) {
        b[i] = ((IFLOAT)rand() / (IFLOAT)RAND_MAX) - 0.5;
    }
    for (i = 0; i < m * n * COMPSIZE; i++) {
        c[i] = ((FLOAT)rand() / (FLOAT)RAND_MAX) - 0.5;
    }

    // Print CSV header to stdout for plotting
    printf("Size,Flops,Time\n");

    fprintf(stderr, "           SIZE               Flops            Time\n");

    for (i = from; i <= to; i += step) {

        timeg = 0;

        if (!has_param_m) { m = i; }
        if (!has_param_n) { n = i; }
        if (!has_param_k) { k = i; }

        if (transa == 'N') { lda = m; } else { lda = k; }
        if (transb == 'N') { ldb = k; } else { ldb = n; }
        ldc = m;

        fprintf(stderr, " M=%4d, N=%4d, K=%4d : ", (int)m, (int)n, (int)k);
        begin();

        for (j = 0; j < loops; j++) {
            GEMM(&transa, &transb, &m, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc);
        }

        end();
        time1 = getsec();

        timeg = time1 / loops;
        double flops = COMPSIZE * COMPSIZE * 2. * (double)k * (double)m * (double)n / timeg * 1.e-6;
        fprintf(stderr,
                " %10.2f MFlops %10.6f sec\n",
                flops, time1);

        // Print plotting data (Size,TotalTime) to stdout
        printf("%d,%f,%f\n", i, flops, time1);
    }

    // Free allocated memory
    free(a);
    free(b);
    free(c);

    return 0;
}