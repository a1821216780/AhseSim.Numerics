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

#include <stdio.h>
#include "mkl_pardiso.h"
#include "mkl_types.h"

    DLLEXPORT MKL_INT sp_pardiso_d_solve(
        const MKL_INT matrixStructure,  // 矩阵结构类型
        const MKL_INT matrixType,       // 矩阵类型
        const MKL_INT nRows,            // 矩阵行数
        const MKL_INT nnz,              // 非零元素个数
        const MKL_INT rowPtr[],         // CSR格式：行指针（大小：nRows+1）
        const MKL_INT colIdx[],         // CSR格式：列索引
        const double values[],          // 非零元素值
        const MKL_INT nRhs,             // 右端向量个数
        const double rhsValues[],       // 右端向量
        double solValues[])             // 解向量（输出）
    {
        // PARDISO内部参数
        void* pt[64] = { 0 };              // 内部求解器内存指针
        MKL_INT iparm[64] = { 0 };         // PARDISO参数数组
        MKL_INT maxfct = 1;        // 最大因子化数量
        MKL_INT mnum = 1;          // 使用哪个因子化
        MKL_INT mtype;             // 矩阵类型
        MKL_INT phase;             // 求解阶段
        MKL_INT n = nRows;         // 矩阵维度
        MKL_INT nrhs = nRhs;       // 右端向量数量
        MKL_INT msglvl = 0;        // 消息级别（0=无输出）
        MKL_INT error = 0;         // 错误标志
        MKL_INT idum;              // 虚拟变量
        double ddum;               // 虚拟变量

        // 设置矩阵类型
        switch (matrixType) {
        case 1:  // 实对称正定矩阵
            mtype = 2;
            break;
        case 2:  // 实对称不定矩阵
            mtype = -2;
            break;
        case 3:  // 实非对称矩阵
            mtype = 11;
            break;
        case 4:  // 复Hermite正定矩阵
            mtype = 4;
            break;
        case 5:  // 复Hermite不定矩阵
            mtype = -4;
            break;
        case 6:  // 复对称矩阵
            mtype = 6;
            break;
        case 7:  // 复非对称矩阵
            mtype = 13;
            break;
        default:
            mtype = 11; // 默认为非对称
        }

        // 配置PARDISO参数
        iparm[0] = 1;   // 不使用求解器默认值
        iparm[1] = 2;   // 使用METIS重排序
        iparm[3] = 0;   // 不进行预处理
        iparm[4] = 0;   // 不使用用户填充减少排列
        iparm[5] = 0;   // 解写入x
        iparm[7] = 2;   // 最大迭代精化步数
        iparm[9] = 13;  // 透视阈值（10^-13）
        iparm[10] = 1;  // 使用缩放（对称矩阵）
        iparm[12] = 1;  // 使用匹配（非对称矩阵）
        iparm[17] = -1; // 输出非零元素数量
        iparm[18] = -1; // 输出MFlops
        iparm[34] = 1;  // 使用从0开始的索引
        iparm[36] = 0;  // CSR格式

        // 阶段1：分析（符号分解）
        phase = 11;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &ddum, &ddum, &error);

        if (error != 0) {
            printf("PARDISO分析阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段2：数值分解
        phase = 22;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &ddum, &ddum, &error);

        if (error != 0) {
            printf("PARDISO分解阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段3：求解和迭代精化
        phase = 33;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, (double*)rhsValues, solValues, &error);

        if (error != 0) {
            printf("PARDISO求解阶段错误: %d\n", error);
            goto cleanup;
        }

    cleanup:
        // 阶段-1：释放内存
        phase = -1;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            &ddum, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &ddum, &ddum, &error);

        return error;
    }

    DLLEXPORT MKL_INT sp_pardiso_s_solve(
        const MKL_INT matrixStructure,  // 矩阵结构类型
        const MKL_INT matrixType,       // 矩阵类型
        const MKL_INT nRows,            // 矩阵行数
        const MKL_INT nnz,              // 非零元素个数
        const MKL_INT rowPtr[],         // CSR格式：行指针（大小：nRows+1）
        const MKL_INT colIdx[],         // CSR格式：列索引
        const float values[],           // 非零元素值
        const MKL_INT nRhs,             // 右端向量个数
        const float rhsValues[],        // 右端向量
        float solValues[])              // 解向量（输出）
    {
        // PARDISO内部参数
        void* pt[64] = { 0 };              // 内部求解器内存指针
        MKL_INT iparm[64] = { 0 };         // PARDISO参数数组
        MKL_INT maxfct = 1;        // 最大因子化数量
        MKL_INT mnum = 1;          // 使用哪个因子化
        MKL_INT mtype;             // 矩阵类型
        MKL_INT phase;             // 求解阶段
        MKL_INT n = nRows;         // 矩阵维度
        MKL_INT nrhs = nRhs;       // 右端向量数量
        MKL_INT msglvl = 0;        // 消息级别（0=无输出）
        MKL_INT error = 0;         // 错误标志
        MKL_INT idum;              // 虚拟变量
        float sdum;                // 单精度虚拟变量

        // 设置矩阵类型
        switch (matrixType) {
        case 1:  // 实对称正定矩阵
            mtype = 2;
            break;
        case 2:  // 实对称不定矩阵
            mtype = -2;
            break;
        case 3:  // 实非对称矩阵
            mtype = 11;
            break;
        case 4:  // 复Hermite正定矩阵
            mtype = 4;
            break;
        case 5:  // 复Hermite不定矩阵
            mtype = -4;
            break;
        case 6:  // 复对称矩阵
            mtype = 6;
            break;
        case 7:  // 复非对称矩阵
            mtype = 13;
            break;
        default:
            mtype = 11; // 默认为非对称
        }

        // 配置PARDISO参数
        iparm[0] = 1;   // 不使用求解器默认值
        iparm[1] = 2;   // 使用METIS重排序
        iparm[3] = 0;   // 不进行预处理
        iparm[4] = 0;   // 不使用用户填充减少排列
        iparm[5] = 0;   // 解写入x
        iparm[7] = 2;   // 最大迭代精化步数
        iparm[9] = 13;  // 透视阈值（10^-13）
        iparm[10] = 1;  // 使用缩放（对称矩阵）
        iparm[12] = 1;  // 使用匹配（非对称矩阵）
        iparm[17] = -1; // 输出非零元素数量
        iparm[18] = -1; // 输出MFlops
        iparm[34] = 1;  // 使用从0开始的索引
        iparm[36] = 0;  // CSR格式

        // 阶段1：分析（符号分解）
        phase = 11;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &sdum, &sdum, &error);

        if (error != 0) {
            printf("PARDISO分析阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段2：数值分解
        phase = 22;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &sdum, &sdum, &error);

        if (error != 0) {
            printf("PARDISO分解阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段3：求解和迭代精化
        phase = 33;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, (float*)rhsValues, solValues, &error);

        if (error != 0) {
            printf("PARDISO求解阶段错误: %d\n", error);
            goto cleanup;
        }

    cleanup:
        // 阶段-1：释放内存
        phase = -1;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            &sdum, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &sdum, &sdum, &error);

        return error;
    }

    DLLEXPORT MKL_INT sp_pardiso_c_solve(
        const MKL_INT matrixStructure,  // 矩阵结构类型
        const MKL_INT matrixType,       // 矩阵类型
        const MKL_INT nRows,            // 矩阵行数
        const MKL_INT nnz,              // 非零元素个数
        const MKL_INT rowPtr[],         // CSR格式：行指针（大小：nRows+1）
        const MKL_INT colIdx[],         // CSR格式：列索引
        const MKL_Complex8 values[],    // 非零元素值
        const MKL_INT nRhs,             // 右端向量个数
        const MKL_Complex8 rhsValues[], // 右端向量
        MKL_Complex8 solValues[])       // 解向量（输出）
    {
        // PARDISO内部参数
        void* pt[64] = { 0 };              // 内部求解器内存指针
        MKL_INT iparm[64] = { 0 };         // PARDISO参数数组
        MKL_INT maxfct = 1;        // 最大因子化数量
        MKL_INT mnum = 1;          // 使用哪个因子化
        MKL_INT mtype;             // 矩阵类型
        MKL_INT phase;             // 求解阶段
        MKL_INT n = nRows;         // 矩阵维度
        MKL_INT nrhs = nRhs;       // 右端向量数量
        MKL_INT msglvl = 0;        // 消息级别（0=无输出）
        MKL_INT error = 0;         // 错误标志
        MKL_INT idum;              // 虚拟变量
        MKL_Complex8 cdum;         // 单精度复数虚拟变量

        // 设置矩阵类型
        switch (matrixType) {
        case 1:  // 实对称正定矩阵（注意：复数函数不应处理实数矩阵）
        case 2:  // 实对称不定矩阵
        case 3:  // 实非对称矩阵
            printf("错误：复数求解器不能用于实数矩阵类型\n");
            return -1;
        case 4:  // 复Hermite正定矩阵
            mtype = 4;
            break;
        case 5:  // 复Hermite不定矩阵
            mtype = -4;
            break;
        case 6:  // 复对称矩阵
            mtype = 6;
            break;
        case 7:  // 复非对称矩阵
            mtype = 13;
            break;
        default:
            mtype = 13; // 默认为复非对称
        }

        // 配置PARDISO参数
        iparm[0] = 1;   // 不使用求解器默认值
        iparm[1] = 2;   // 使用METIS重排序
        iparm[3] = 0;   // 不进行预处理
        iparm[4] = 0;   // 不使用用户填充减少排列
        iparm[5] = 0;   // 解写入x
        iparm[7] = 2;   // 最大迭代精化步数
        iparm[9] = 13;  // 透视阈值（10^-13）
        iparm[10] = 1;  // 使用缩放（对称矩阵）
        iparm[12] = 1;  // 使用匹配（非对称矩阵）
        iparm[17] = -1; // 输出非零元素数量
        iparm[18] = -1; // 输出MFlops
        iparm[34] = 1;  // 使用从0开始的索引
        iparm[36] = 0;  // CSR格式

        // 阶段1：分析（符号分解）
        phase = 11;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &cdum, &cdum, &error);

        if (error != 0) {
            printf("PARDISO分析阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段2：数值分解
        phase = 22;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &cdum, &cdum, &error);

        if (error != 0) {
            printf("PARDISO分解阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段3：求解和迭代精化
        phase = 33;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, (MKL_Complex8*)rhsValues, solValues, &error);

        if (error != 0) {
            printf("PARDISO求解阶段错误: %d\n", error);
            goto cleanup;
        }

    cleanup:
        // 阶段-1：释放内存
        phase = -1;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            &cdum, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &cdum, &cdum, &error);

        return error;
    }

    DLLEXPORT MKL_INT sp_pardiso_z_solve(
        const MKL_INT matrixStructure,  // 矩阵结构类型
        const MKL_INT matrixType,       // 矩阵类型
        const MKL_INT nRows,            // 矩阵行数
        const MKL_INT nnz,              // 非零元素个数
        const MKL_INT rowPtr[],         // CSR格式：行指针（大小：nRows+1）
        const MKL_INT colIdx[],         // CSR格式：列索引
        const MKL_Complex16 values[],   // 非零元素值
        const MKL_INT nRhs,             // 右端向量个数
        const MKL_Complex16 rhsValues[], // 右端向量
        MKL_Complex16 solValues[])       // 解向量（输出）
    {
        // PARDISO内部参数
        void* pt[64] = { 0 };              // 内部求解器内存指针
        MKL_INT iparm[64] = { 0 };         // PARDISO参数数组
        MKL_INT maxfct = 1;        // 最大因子化数量
        MKL_INT mnum = 1;          // 使用哪个因子化
        MKL_INT mtype;             // 矩阵类型
        MKL_INT phase;             // 求解阶段
        MKL_INT n = nRows;         // 矩阵维度
        MKL_INT nrhs = nRhs;       // 右端向量数量
        MKL_INT msglvl = 0;        // 消息级别（0=无输出）
        MKL_INT error = 0;         // 错误标志
        MKL_INT idum;              // 虚拟变量
        MKL_Complex16 zdum;        // 双精度复数虚拟变量

        // 设置矩阵类型
        switch (matrixType) {
        case 1:  // 实对称正定矩阵（注意：复数函数不应处理实数矩阵）
        case 2:  // 实对称不定矩阵
        case 3:  // 实非对称矩阵
            printf("错误：复数求解器不能用于实数矩阵类型\n");
            return -1;
        case 4:  // 复Hermite正定矩阵
            mtype = 4;
            break;
        case 5:  // 复Hermite不定矩阵
            mtype = -4;
            break;
        case 6:  // 复对称矩阵
            mtype = 6;
            break;
        case 7:  // 复非对称矩阵
            mtype = 13;
            break;
        default:
            mtype = 13; // 默认为复非对称
        }

        // 配置PARDISO参数
        iparm[0] = 1;   // 不使用求解器默认值
        iparm[1] = 2;   // 使用METIS重排序
        iparm[3] = 0;   // 不进行预处理
        iparm[4] = 0;   // 不使用用户填充减少排列
        iparm[5] = 0;   // 解写入x
        iparm[7] = 2;   // 最大迭代精化步数
        iparm[9] = 13;  // 透视阈值（10^-13）
        iparm[10] = 1;  // 使用缩放（对称矩阵）
        iparm[12] = 1;  // 使用匹配（非对称矩阵）
        iparm[17] = -1; // 输出非零元素数量
        iparm[18] = -1; // 输出MFlops
        iparm[34] = 1;  // 使用从0开始的索引
        iparm[36] = 0;  // CSR格式

        // 阶段1：分析（符号分解）
        phase = 11;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &zdum, &zdum, &error);

        if (error != 0) {
            printf("PARDISO分析阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段2：数值分解
        phase = 22;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &zdum, &zdum, &error);

        if (error != 0) {
            printf("PARDISO分解阶段错误: %d\n", error);
            goto cleanup;
        }

        // 阶段3：求解和迭代精化
        phase = 33;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            values, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, (MKL_Complex16*)rhsValues, solValues, &error);

        if (error != 0) {
            printf("PARDISO求解阶段错误: %d\n", error);
            goto cleanup;
        }

    cleanup:
        // 阶段-1：释放内存
        phase = -1;
        pardiso(pt, &maxfct, &mnum, &mtype, &phase, &n,
            &zdum, rowPtr, colIdx, &idum, &nrhs,
            iparm, &msglvl, &zdum, &zdum, &error);

        return error;
    }
}
