#ifndef GEMM_H
#define GEMM_H

#include <cstddef>

void naive_matmul(const float* A, const float* B, float* C, size_t M, size_t N, size_t K);
void ikj_matmul(const float* A, const float* B, float* C, size_t M, size_t N, size_t K);

#endif // GEMM_H