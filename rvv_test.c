#include <stdio.h>
#include <riscv_vector.h>
#include <stdint.h>
#include <stdlib.h>

// Array size. N=303 is intentionally chosen to not be a multiple of typical VLEN
// (e.g., 4, 8, 16, 32, 64) to thoroughly test the loop's strip-mining
// and the correct handling of the vector tail (unaligned remainder).
#define N 303

/**
 * @brief Vector addition C = A + B using RVV Intrinsics
 * @param c Result array
 * @param a Input array A
 * @param b Input array B
 * @param n Array length
 */
void vector_add(int32_t *c, const int32_t *a, const int32_t *b, size_t n) {
	size_t i = 0;
	// n is the number of remaining elements to process
	for (; i < n; ) {
		// vsetvl_e32m1 determines the current vector length (vl)
		// vl is dynamically determined based on hardware VLEN and remaining elements (n - i)
		size_t vl = vsetvl_e32m1(n - i);

		// Load vectors a and b
		vint32m1_t va = vle32_v_i32m1(a + i, vl);
		vint32m1_t vb = vle32_v_i32m1(b + i, vl);

		// Vector addition: vc = va + vb
		vint32m1_t vc = vadd_vv_i32m1(va, vb, vl);

		// Store result c
		vse32_v_i32m1(c + i, vc, vl);

		i += vl;
	}
}

int main() {
	int32_t a[N], b[N], c[N];

	// Get and print hardware VLEN (maximum vector length)
	size_t vlen_max = vsetvlmax_e32m1();
	printf("Hardware VLEN (max for e32m1): %zu\n", vlen_max);

	// Initialization: Ensure a[i] + b[i] = N (303)
	for (int i = 0; i < N; i++) {
		a[i] = i;
		b[i] = N - i;
		c[i] = 0;
	}

	// Execute vector addition
	vector_add(c, a, b, N);

	// Verify results
	printf("RVV Vector Add Test Results:\n");
	int error = 0;
	for (int i = 0; i < N; i++) {
		// Expected result is a[i] + b[i] = i + (N - i) = N = 303
		if (c[i] != N) {
			printf("ERROR at index %d: %d + %d != %d (Expected: %d)\n", i, a[i], b[i], c[i], N);
			error = 1;
		}
	}

	if (!error) {
		printf("Success! All %d results matched the expected value (%d).\n", N, N);
	}

	return error;
}
