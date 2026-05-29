#include <cstddef>


void naive_matmul(const float* A, const float* B, float* C, size_t M,
                  size_t N, size_t K) {
                    
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < K; ++k) {
                C[i * N + j] += A[i * K + k] * B[k * N + j];
            }

        }
    }
}