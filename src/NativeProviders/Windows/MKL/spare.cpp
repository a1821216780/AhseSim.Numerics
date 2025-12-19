#include "spare.h"
#include <mkl.h>
#include <mkl_spblas.h>
#include <string>
#include <cstring>

static inline std::string lastError;

extern "C" {

    //const char* GetLastError() {
    //    return lastError.c_str();
    //}

    // 稀疏矩阵 * 稠密矩阵
    DLLEXPORT int sp_mkl_sparse_d_create_csr(
        int m, int k, int n,
        const double* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        const double* denseB,
        double* resultC)
    {
        try {
            lastError.clear();

            // 创建稀疏矩阵句柄
            sparse_matrix_t A;
            sparse_status_t status;

            // 创建CSR格式的稀疏矩阵
            // MKL使用0-based索引
            status = mkl_sparse_d_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, k,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<double*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            // 设置矩阵乘法hint
            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            // 执行稀疏矩阵 * 稠密矩阵
            // C = alpha * A * B + beta * C
            double alpha = 1.0;
            double beta = 0.0;

            status = mkl_sparse_d_mm(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                SPARSE_LAYOUT_COLUMN_MAJOR,  // B是列优先
                denseB,
                n,      // B的列数
                k,      // B的leading dimension
                beta,
                resultC,
                m       // C的leading dimension
            );

            // 销毁稀疏矩阵句柄
            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Dense multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sparse_s_create_csr(
        int m, int k, int n,
        const float* values,      // CSR值数组
        const int* rowIndex,       // CSR行索引
        const int* columns,        // CSR列索引
        int nnz,                   // 非零元素个数
        const float* denseB,      // 稠密矩阵B (列优先)
        float* resultC            // 结果矩阵C (列优先)
    )
    {
        try {
            lastError.clear();

            // 创建稀疏矩阵句柄
            sparse_matrix_t A;
            sparse_status_t status;

            // 创建CSR格式的稀疏矩阵
            // MKL使用0-based索引
            status = mkl_sparse_s_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, k,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<float*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            // 设置矩阵乘法hint
            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            // 执行稀疏矩阵 * 稠密矩阵
            // C = alpha * A * B + beta * C
            float alpha = 1.0;
            float beta = 0.0;

            status = mkl_sparse_s_mm(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                SPARSE_LAYOUT_COLUMN_MAJOR,  // B是列优先
                denseB,
                n,      // B的列数
                k,      // B的leading dimension
                beta,
                resultC,
                m       // C的leading dimension
            );

            // 销毁稀疏矩阵句柄
            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Dense multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sparse_c_create_csr(
        int m, int k, int n,
        const MKL_Complex8* values,      // CSR值数组
        const int* rowIndex,       // CSR行索引
        const int* columns,        // CSR列索引
        int nnz,                   // 非零元素个数
        const MKL_Complex8* denseB,      // 稠密矩阵B (列优先)
        MKL_Complex8* resultC            // 结果矩阵C (列优先)
    )
    {
        try {
            lastError.clear();

            // 创建稀疏矩阵句柄
            sparse_matrix_t A;
            sparse_status_t status;

            // 创建CSR格式的稀疏矩阵
            // MKL使用0-based索引
            status = mkl_sparse_c_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, k,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<MKL_Complex8*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            // 设置矩阵乘法hint
            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            // 执行稀疏矩阵 * 稠密矩阵
            // C = alpha * A * B + beta * C
            MKL_Complex8 alpha = { 1.0f, 0.0f };
            MKL_Complex8 beta = { 0.0f, 0.0f };

            status = mkl_sparse_c_mm(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                SPARSE_LAYOUT_COLUMN_MAJOR,  // B是列优先
                denseB,
                n,      // B的列数
                k,      // B的leading dimension
                beta,
                resultC,
                m       // C的leading dimension
            );

            // 销毁稀疏矩阵句柄
            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Dense multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sparse_z_create_csr(
        int m, int k, int n,
        const MKL_Complex16* values,      // CSR值数组
        const int* rowIndex,       // CSR行索引
        const int* columns,        // CSR列索引
        int nnz,                   // 非零元素个数
        const MKL_Complex16* denseB,      // 稠密矩阵B (列优先)
        MKL_Complex16* resultC            // 结果矩阵C (列优先)
    )
    {
        try {
            lastError.clear();

            // 创建稀疏矩阵句柄
            sparse_matrix_t A;
            sparse_status_t status;

            // 创建CSR格式的稀疏矩阵
            // MKL使用0-based索引
            status = mkl_sparse_z_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, k,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<MKL_Complex16*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            // 设置矩阵乘法hint
            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            // 执行稀疏矩阵 * 稠密矩阵
            // C = alpha * A * B + beta * C
            MKL_Complex16 alpha = { 1.0f, 0.0f };
            MKL_Complex16 beta = { 0.0f, 0.0f };

            status = mkl_sparse_z_mm(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                SPARSE_LAYOUT_COLUMN_MAJOR,  // B是列优先
                denseB,
                n,      // B的列数
                k,      // B的leading dimension
                beta,
                resultC,
                m       // C的leading dimension
            );

            // 销毁稀疏矩阵句柄
            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Dense multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }


    // 稠密矩阵 * 稀疏矩阵
    DLLEXPORT int sp_mkl_dDenseSparseMultiply(
        int m, int k, int n,
        const double* denseA,
        const double* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        double* resultC)
    {
        try {
            lastError.clear();

            // 创建稀疏矩阵B的句柄
            sparse_matrix_t B;
            sparse_status_t status;

            status = mkl_sparse_d_create_csr(&B,
                SPARSE_INDEX_BASE_ZERO,
                k, n,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<double*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            // 使用转置技巧: A * B = (B^T * A^T)^T
            // 但MKL不直接支持Dense*Sparse，我们需要逐列计算

            // 初始化结果矩阵
            memset(resultC, 0, m * n * sizeof(double));

            // 对B的每一列进行SpMV (稀疏矩阵-向量乘法)
            for (int col = 0; col < n; ++col) {
                // 提取B的第col列
                double* bColumn = new double[k];
                memset(bColumn, 0, k * sizeof(double));

                // 从CSR格式中提取第col列
                for (int row = 0; row < k; ++row) {
                    for (int idx = rowIndex[row]; idx < rowIndex[row + 1]; ++idx) {
                        if (columns[idx] == col) {
                            bColumn[row] = values[idx];
                            break;
                        }
                    }
                }

                // 计算 A * bColumn，结果存入resultC的第col列
                // 使用BLAS的矩阵-向量乘法
                cblas_dgemv(CblasColMajor, CblasNoTrans,
                    m, k,
                    1.0,
                    denseA, m,
                    bColumn, 1,
                    0.0,
                    resultC + col * m, 1);

                delete[] bColumn;
            }

            mkl_sparse_destroy(B);
            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sDenseSparseMultiply(
        int m, int k, int n,
        const float* denseA,
        const float* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        float* resultC)
    {
        try {
            lastError.clear();

            // 创建稀疏矩阵B的句柄
            sparse_matrix_t B;
            sparse_status_t status;

            status = mkl_sparse_s_create_csr(&B,
                SPARSE_INDEX_BASE_ZERO,
                k, n,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<float*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            // 使用转置技巧: A * B = (B^T * A^T)^T
            // 但MKL不直接支持Dense*Sparse，我们需要逐列计算

            // 初始化结果矩阵
            memset(resultC, 0, m * n * sizeof(float));

            // 对B的每一列进行SpMV (稀疏矩阵-向量乘法)
            for (int col = 0; col < n; ++col) {
                // 提取B的第col列
                float* bColumn = new float[k];
                memset(bColumn, 0, k * sizeof(float));

                // 从CSR格式中提取第col列
                for (int row = 0; row < k; ++row) {
                    for (int idx = rowIndex[row]; idx < rowIndex[row + 1]; ++idx) {
                        if (columns[idx] == col) {
                            bColumn[row] = values[idx];
                            break;
                        }
                    }
                }

                // 计算 A * bColumn，结果存入resultC的第col列
                // 使用BLAS的矩阵-向量乘法
                cblas_sgemv(CblasColMajor, CblasNoTrans,
                    m, k,
                    1.0,
                    denseA, m,
                    bColumn, 1,
                    0.0,
                    resultC + col * m, 1);

                delete[] bColumn;
            }

            mkl_sparse_destroy(B);
            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }



    // 稀疏矩阵 * 稠密向量
    DLLEXPORT  int sp_mkl_sparse_d_mv(
        int m, int n,
        const double* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        const double* denseVector,
        double* resultVector)
    {
        try {
            lastError.clear();

            sparse_matrix_t A;
            sparse_status_t status;

            status = mkl_sparse_d_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, n,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<double*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            double alpha = 1.0;
            double beta = 0.0;

            status = mkl_sparse_d_mv(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                denseVector,
                beta,
                resultVector);

            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Vector multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sparse_s_mv(
        int m, int n,
        const float* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        const float* denseVector,
        float* resultVector)
    {
        try {
            lastError.clear();

            sparse_matrix_t A;
            sparse_status_t status;

            status = mkl_sparse_s_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, n,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<float*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            float alpha = 1.0;
            float beta = 0.0;

            status = mkl_sparse_s_mv(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                denseVector,
                beta,
                resultVector);

            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Vector multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sparse_c_mv(
        int m, int n,
        const MKL_Complex8* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        const MKL_Complex8* denseVector,
        MKL_Complex8* resultVector)
    {
        try {
            lastError.clear();

            sparse_matrix_t A;
            sparse_status_t status;

            status = mkl_sparse_c_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, n,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<MKL_Complex8*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            MKL_Complex8 alpha = { 1.0,0.0 };
            MKL_Complex8 beta = { 0.0,0.0 };

            status = mkl_sparse_c_mv(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                denseVector,
                beta,
                resultVector);

            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Vector multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }

    DLLEXPORT int sp_mkl_sparse_z_mv(
        int m, int n,
        const MKL_Complex16* values,
        const int* rowIndex,
        const int* columns,
        int nnz,
        const MKL_Complex16* denseVector,
        MKL_Complex16* resultVector)
    {
        try {
            lastError.clear();

            sparse_matrix_t A;
            sparse_status_t status;

            status = mkl_sparse_z_create_csr(&A,
                SPARSE_INDEX_BASE_ZERO,
                m, n,
                const_cast<int*>(rowIndex),
                const_cast<int*>(rowIndex + 1),
                const_cast<int*>(columns),
                const_cast<MKL_Complex16*>(values));

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Failed to create sparse matrix";
                return -1;
            }

            struct matrix_descr descr;
            descr.type = SPARSE_MATRIX_TYPE_GENERAL;

            MKL_Complex16 alpha = { 1.0,0.0 };
            MKL_Complex16 beta = { 0.0,0.0 };

            status = mkl_sparse_z_mv(
                SPARSE_OPERATION_NON_TRANSPOSE,
                alpha,
                A,
                descr,
                denseVector,
                beta,
                resultVector);

            mkl_sparse_destroy(A);

            if (status != SPARSE_STATUS_SUCCESS) {
                lastError = "Sparse-Vector multiplication failed";
                return -2;
            }

            return 0;
        }
        catch (const std::exception& e) {
            lastError = std::string("Exception: ") + e.what();
            return -99;
        }
    }
}
