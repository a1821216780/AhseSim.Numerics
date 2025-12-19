#pragma once

#include "mkl_spblas.h"
#include "mkl_dss.h"
#include "wrapper_common.h"
#include "mkl_types.h"

#define sp_int             MKL_INT
#define sp_double          double
#define sp_float           float
#define sp_complex_float   MKL_Complex8
#define sp_complex_double  MKL_Complex16

sparse_layout_t sp_sparse_layout = SPARSE_LAYOUT_ROW_MAJOR;
