#include "spare.h"


DLLEXPORT sparse_status_t mkl_sparse_d_convert_csr2dense(sparse_matrix* csrA, matrix_descr descrA, sp_int ldA, sp_double* denseMatrix)
{
    return mkl_sparse_d_convert_dense(csrA, descrA, sp_sparse_layout, ldA, denseMatrix);
}
DLLEXPORT sparse_status_t mkl_sparse_s_convert_csr2dense(sparse_matrix* csrA, matrix_descr descrA, sp_int ldA, sp_float* denseMatrix)
{
    return mkl_sparse_s_convert_dense(csrA, descrA, sp_sparse_layout, ldA, denseMatrix);
}
DLLEXPORT sparse_status_t mkl_sparse_c_convert_csr2dense(sparse_matrix_t csrA, matrix_descr descrA, sp_int ldA, sp_complex_float* denseMatrix)
{
    return mkl_sparse_c_convert_dense(csrA, descrA, sp_sparse_layout, ldA, denseMatrix);
}
DLLEXPORT sparse_status_t mkl_sparse_z_convert_csr2dense(sparse_matrix_t csrA, matrix_descr descrA, sp_int ldA, sp_complex_double* denseMatrix)
{
    return mkl_sparse_z_convert_dense(csrA, descrA, sp_sparse_layout, ldA, denseMatrix);
}
