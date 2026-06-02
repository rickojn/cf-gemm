#include "../include/gemm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>


struct impl {
    const char *name;
    void (*func)(const float*, const float*, float*, size_t, size_t, size_t);
};

void run_test(impl &test, int t, int warmup, float *A, float *B, float *C, int M, int N, int K, int iterations);

int main(int argc, char *argv[])
{
    int M = 1024;  // Matrix size
    int N = 1024;  // Matrix size
    int K = 1024;  // Matrix size

    if (argc >= 4) { M = std::stoul(argv[1]); N = std::stoul(argv[2]); K = std::stoul(argv[3]); }
    int warmup = 5;
    int iterations = 10;

    printf("Matrix size: M=%d, N=%d, K=%d\n", M, N, K);
    printf("Warmup iterations: %d, Timed iterations: %d\n", warmup, iterations);


    
    // Allocate matrices
    float *A = new float[M * K];
    float *B = new float[K * N];
    float *C = new float[M * N];
    
    // Initialize with random values
    srand(42);
    for (int i = 0; i < M * K; i++) {
        A[i] = (float)rand() / RAND_MAX;
    }
    for (int i = 0; i < K * N; i++) {
        B[i] = (float)rand() / RAND_MAX;
    }
    
    // Define test cases
    std::vector<impl> tests = {
        {"naive",   naive_matmul},
        {"ikj",     ikj_matmul}
    };

    // display menu of implementations
    printf("Available implementations:\n");
    for (int i = 0; i < tests.size(); i++) {
        printf("%d: %s\n", i, tests[i].name);
    }
    printf("Enter the number of the implementation to run (or -1 for all): ");
    int choice;
    std::cin >> choice;

    if (choice == -1) {
        // Run all implementations
            for (int t = 0; t < tests.size(); t++) {
                run_test(tests[t], t, warmup, A, B, C, M, N, K, iterations);
    }
    } else if (choice >= 0 && choice < tests.size()) {
        // Run selected implementation
        run_test(tests[choice], choice, warmup, A, B, C, M, N, K, iterations);
    } else {
        printf("Invalid choice. Exiting.\n");
        delete[] A; delete[] B; delete[] C;
        return 1;
    }       
    // Run each implementation
    
    delete[] A; delete[] B; delete[] C;
    return 0;
}

void run_test(impl &test, int t, int warmup, float *A, float *B, float *C, int M, int N, int K, int iterations)
{
    printf("\n=== %s ===\n", test.name);

    // Warmup
    printf("Warming up...\n");
    for (int i = 0; i < warmup; i++)
        test.func(A, B, C, M, N, K);

    // Timed runs (for sanity check)
    printf("Running benchmark...\n");
    clock_t start = clock();
    for (int i = 0; i < iterations; i++)
        test.func(A, B, C, M, N, K);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC / iterations;
    printf("Time: %.4f ms\n", time * 1000);
}
