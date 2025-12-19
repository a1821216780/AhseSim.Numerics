#pragma once
#include "mkl_types.h"
#include "wrapper_common.h"

//#ifdef MKLWRAPPER_EXPORTS
//#define MKLWRAPPER_API __declspec(dllexport)
//#else
//#define MKLWRAPPER_API __declspec(dllimport)
//#endif
//
//extern "C" {
//    // 稀疏矩阵 * 稠密矩阵 (CSR格式)
//    // A(m x k) * B(k x n) = C(m x n)
//    MKLWRAPPER_API int sp_mkl_sparse_d_create_csr(
//        int m, int k, int n,
//        const double* values,      // CSR值数组
//        const int* rowIndex,       // CSR行索引
//        const int* columns,        // CSR列索引
//        int nnz,                   // 非零元素个数
//        const double* denseB,      // 稠密矩阵B (列优先)
//        double* resultC            // 结果矩阵C (列优先)
//    );
//    // A(m x k) * B(k x n) = C(m x n)
//    MKLWRAPPER_API int sp_mkl_sparse_s_create_csr(
//        int m, int k, int n,
//        const float* values,      // CSR值数组
//        const int* rowIndex,       // CSR行索引
//        const int* columns,        // CSR列索引
//        int nnz,                   // 非零元素个数
//        const float* denseB,      // 稠密矩阵B (列优先)
//        float* resultC            // 结果矩阵C (列优先)
//    );
//    // A(m x k) * B(k x n) = C(m x n)
//    MKLWRAPPER_API int sp_mkl_sparse_c_create_csr(
//        int m, int k, int n,
//        const MKL_Complex8* values,      // CSR值数组
//        const int* rowIndex,       // CSR行索引
//        const int* columns,        // CSR列索引
//        int nnz,                   // 非零元素个数
//        const MKL_Complex8* denseB,      // 稠密矩阵B (列优先)
//        MKL_Complex8* resultC            // 结果矩阵C (列优先)
//    );
//    // A(m x k) * B(k x n) = C(m x n)
//    MKLWRAPPER_API int sp_mkl_sparse_z_create_csr(
//        int m, int k, int n,
//        const MKL_Complex16* values,      // CSR值数组
//        const int* rowIndex,       // CSR行索引
//        const int* columns,        // CSR列索引
//        int nnz,                   // 非零元素个数
//        const MKL_Complex16* denseB,      // 稠密矩阵B (列优先)
//        MKL_Complex16* resultC            // 结果矩阵C (列优先)
//    );
//
//
//    // 稠密矩阵 * 稀疏矩阵 (CSR格式)
//    // A(m x k) * B(k x n) = C(m x n)
//    MKLWRAPPER_API int dDenseSparseMultiply(
//        int m, int k, int n,
//        const double* denseA,      // 稠密矩阵A (列优先)
//        const double* values,      // CSR值数组
//        const int* rowIndex,       // CSR行索引
//        const int* columns,        // CSR列索引
//        int nnz,                   // 非零元素个数
//        double* resultC            // 结果矩阵C (列优先)
//    );
//    // A(m x k) * B(k x n) = C(m x n)
//    MKLWRAPPER_API int sDenseSparseMultiply(
//        int m, int k, int n,
//        const float* denseA,      // 稠密矩阵A (列优先)
//        const float* values,      // CSR值数组
//        const int* rowIndex,       // CSR行索引
//        const int* columns,        // CSR列索引
//        int nnz,                   // 非零元素个数
//        float* resultC            // 结果矩阵C (列优先)
//    );
//
//
//
//
//
//
//
//    // 稀疏矩阵 * 稠密向量 (CSR格式)
//    MKLWRAPPER_API int dSparseDenseVectorMultiply(
//        int m, int n,
//        const double* values,
//        const int* rowIndex,
//        const int* columns,
//        int nnz,
//        const double* denseVector,
//        double* resultVector
//    );
//
//    // 稀疏矩阵 * 稠密向量 (CSR格式)
//    MKLWRAPPER_API int sSparseDenseVectorMultiply(
//        int m, int n,
//        const float* values,
//        const int* rowIndex,
//        const int* columns,
//        int nnz,
//        const float* denseVector,
//        float* resultVector
//    );
//
//    // 稀疏矩阵 * 稠密向量 (CSR格式)
//    MKLWRAPPER_API int cSparseDenseVectorMultiply(
//        int m, int n,
//        const MKL_Complex8* values,
//        const int* rowIndex,
//        const int* columns,
//        int nnz,
//        const MKL_Complex8* denseVector,
//        MKL_Complex8* resultVector
//    );
//    // 稀疏矩阵 * 稠密向量 (CSR格式)
//    MKLWRAPPER_API int zSparseDenseVectorMultiply(
//        int m, int n,
//        const MKL_Complex16* values,
//        const int* rowIndex,
//        const int* columns,
//        int nnz,
//        const MKL_Complex16* denseVector,
//        MKL_Complex16* resultVector
//    );
//}
