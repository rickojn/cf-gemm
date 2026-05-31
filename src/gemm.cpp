#include <cstddef>


void naive_matmul(const float* A, const float* B, float* C, size_t M,
                  size_t N, size_t K) {
                    
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < K; ++k) {
                // C[i,j]+=A[i,k]*B[k,j]
                C[i * N + j] += A[i * K + k] * B[k * N + j];
            }

        }
    }
}

void ikj_matmul(const float* A, const float* B, float* C, size_t M,
                  size_t N, size_t K) {
                    
    for (size_t i = 0; i < M; ++i) {
        for (size_t k = 0; k < K; ++k) {
            for (size_t j = 0; j < N; ++j) {
                // C[i,j]+=A[i,k]*B[k,j]
                C[i * N + j] += A[i * K + k] * B[k * N + j];
            }
        }
    }
}