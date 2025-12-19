using Complex = System.Numerics.Complex;

namespace AHSEsim.Numerics.Providers.SparseSolver
{
    /// <summary>
    /// Structure option.
    /// </summary>
    public enum DssMatrixStructure : int
    {

        /// <summary>
        /// <para>实数对称矩阵：A = A^T</para>
        /// <para>示例：</para>
        /// <para>[2  1  0]  </para>
        /// <para>[1  3  2]  </para>
        /// <para>[0  2  4]  </para>
        /// <para>只需存储上三角或下三角部分</para>
        /// </summary>
        Symmetric = 536870976,
        /// <summary>
        ///非零元素位置对称，但值可能不同
        ///<para> 示例：</para>
        ///<para> [2  1  0]</para>
        ///<para> [3  4  2]  // 注意：A[0,1]=1 但 A[1,0]=3</para>
        ///<para> [0  5  6]</para>
        ///<para> 非零模式对称，但 A ≠ A^T</para>
        /// </summary>
        SymmetricStructure = 536871040,
        /// <summary>
        ///  一般矩阵，无特殊结构
        ///  <para> [2  1  0] </para> 
        ///  <para> [0  3  2]</para> 
        ///  <para> [4  0  5]</para> 
        /// </summary>
        Nonsymmetric = 536871104,
        /// <summary>
        /// 复数对称矩阵
        /// </summary>
        SymmetricComplex = 536871168,
        SymmetricStructureComplex = 536871232,
        NonsymmetricComplex = 536871296,

    }

    public enum Sparse_matrix_type_t : int
    {
        /// <summary>
        /// 没有特殊结构，需要处理所有元素
        /// </summary>
        SPARSE_MATRIX_TYPE_GENERAL = 20,
        /// <summary>
        /// 满足 A = A^T，只需存储/处理三角部分
        /// </summary>
        SPARSE_MATRIX_TYPE_SYMMETRIC = 21,
        /// <summary>
        /// 满足 A = A^H（共轭转置），只需处理三角部分
        /// </summary>
        SPARSE_MATRIX_TYPE_HERMITIAN = 22,
        /// <summary>
        /// 上三角或下三角矩阵
        /// </summary>
        SPARSE_MATRIX_TYPE_TRIANGULAR = 23,
        /// <summary>
        /// 只有对角线元素非零
        /// </summary>
        SPARSE_MATRIX_TYPE_DIAGONAL = 24,
        /// <summary>
        /// 以块为单位的三角结构
        /// </summary>
        SPARSE_MATRIX_TYPE_BLOCK_TRIANGULAR = 25,
        /// <summary>
        /// 只有对角块非零
        /// </summary>
        SPARSE_MATRIX_TYPE_BLOCK_DIAGONAL = 26    /* block-diagonal matrix; only diagonal blocks will be processed */
    }

    /// <summary>
    /// DSS (Direct Sparse Solver) 矩阵类型枚举
    /// 用于指定对称/埃尔米特矩阵的正定性，影响因子分解算法的选择
    /// </summary>
    public enum DssMatrixType : int
    {
        /// <summary>
        /// 对称正定矩阵 (Symmetric Positive Definite)
        /// <para>满足条件：A = A^T 且 x^T A x > 0 (对所有非零向量x)</para>
        /// <para>使用 Cholesky 分解：A = LL^T</para>
        /// <para>典型应用：有限元刚度矩阵、协方差矩阵</para>
        /// </summary>
        /// <remarks>对应 MKL_DSS_POSITIVE_DEFINITE = 0x08000040</remarks>
        PositiveDefinite = 134217792,

        /// <summary>
        /// 对称不定矩阵 (Symmetric Indefinite)
        /// <para>满足条件：A = A^T 但可能有正负特征值</para>
        /// <para>使用 Bunch-Kaufman 分解：A = LDL^T</para>
        /// <para>典型应用：鞍点问题、约束优化</para>
        /// </summary>
        /// <remarks>对应 MKL_DSS_INDEFINITE = 0x08000080</remarks>
        Indefinite = 134217856,

        /// <summary>
        /// 埃尔米特正定矩阵 (Hermitian Positive Definite)
        /// <para>满足条件：A = A^H (共轭转置) 且 x^H A x > 0</para>
        /// <para>使用复数 Cholesky 分解：A = LL^H</para>
        /// <para>典型应用：量子力学、信号处理中的复数系统</para>
        /// </summary>
        /// <remarks>对应 MKL_DSS_HERMITIAN_POSITIVE_DEFINITE = 0x080000C0</remarks>
        HermitianPositiveDefinite = 134217920,

        /// <summary>
        /// 埃尔米特不定矩阵 (Hermitian Indefinite)
        /// <para>满足条件：A = A^H 但可能有正负特征值</para>
        /// <para>使用复数 Bunch-Kaufman 分解</para>
        /// <para>典型应用：复数域的鞍点问题</para>
        /// </summary>
        /// <remarks>对应 MKL_DSS_HERMITIAN_INDEFINITE = 0x08000100</remarks>
        HermitianIndefinite = 134217984
    }



    /// <summary>
    /// DSS 求解器的系统类型枚举
    /// 指定求解线性方程组时使用的矩阵形式（原矩阵、转置或共轭转置）
    /// </summary>
    /// <remarks>
    /// 在 dss_solve 步骤中使用，用于求解不同形式的线性系统
    /// </remarks>
    public enum DssSystemType : int
    {
        /// <summary>
        /// 求解原始系统：Ax = b
        /// <para>使用原矩阵 A 进行求解</para>
        /// <para>最常用的求解模式</para>
        /// </summary>
        /// <example>
        /// <code>
        /// // 求解 Ax = b
        /// dss_solve(handle, DssSystemType.DontTranspose, rhs, nrhs, solution);
        /// </code>
        /// </example>
        /// <remarks>对应 MKL_DSS_DEFAULTS = 0x00000000</remarks>
        DontTranspose = 0,

        /// <summary>
        /// 求解转置系统：A^T x = b
        /// <para>使用矩阵 A 的转置进行求解</para>
        /// <para>适用场景：伴随方程、灵敏度分析、最小二乘问题</para>
        /// </summary>
        /// <example>
        /// <code>
        /// // 求解 A^T x = b (不重新分解矩阵)
        /// dss_solve(handle, DssSystemType.Transpose, rhs, nrhs, solution);
        /// </code>
        /// </example>
        /// <remarks>对应 MKL_DSS_TRANSPOSE_SOLVE = 0x00040000</remarks>
        Transpose = 262144,

        /// <summary>
        /// 求解共轭转置系统：A^H x = b (A† x = b)
        /// <para>使用矩阵 A 的共轭转置（埃尔米特转置）进行求解</para>
        /// <para>仅适用于复数矩阵：A^H = (A^T)*（转置后取共轭）</para>
        /// <para>适用场景：复数域的伴随问题、量子力学、信号处理</para>
        /// </summary>
        /// <example>
        /// <code>
        /// // 求解 A^H x = b (复数矩阵)
        /// dss_solve(handle, DssSystemType.ConjugateTranspose, rhs, nrhs, solution);
        /// </code>
        /// </example>
        /// <remarks>对应 MKL_DSS_CONJUGATE_SOLVE = 0x00080000</remarks>
        ConjugateTranspose = 524288,
    }


    ///// <summary>
    ///// Status values
    ///// </summary>
    //public enum DssStatus : int
    //{
    //    /// <summary>
    //    /// The operation was successful.
    //    /// </summary>
    //    MKL_DSS_SUCCESS = 0, 
    //    MKL_DSS_ZERO_PIVOT = -1,
    //    MKL_DSS_OUT_OF_MEMORY = -2,
    //    MKL_DSS_FAILURE = -3,
    //    MKL_DSS_ROW_ERR = -4,
    //    MKL_DSS_COL_ERR = -5,
    //    MKL_DSS_TOO_FEW_VALUES = -6,
    //    MKL_DSS_TOO_MANY_VALUES = -7,
    //    MKL_DSS_NOT_SQUARE = -8,
    //    MKL_DSS_STATE_ERR = -9,
    //    MKL_DSS_INVALID_OPTION = -10,
    //    MKL_DSS_OPTION_CONFLICT = -11,
    //    MKL_DSS_MSG_LVL_ERR = -12,
    //    MKL_DSS_TERM_LVL_ERR = -13,
    //    MKL_DSS_STRUCTURE_ERR = -14,
    //    MKL_DSS_REORDER_ERR = -15,
    //    MKL_DSS_VALUES_ERR = -16,
    //    MKL_DSS_STATISTICS_INVALID_MATRIX = -17,
    //    MKL_DSS_STATISTICS_INVALID_STATE = -18,
    //    MKL_DSS_STATISTICS_INVALID_STRING = -19,
    //    MKL_DSS_REORDER1_ERR = -20,
    //    MKL_DSS_PREORDER_ERR = -21,
    //    MKL_DSS_DIAG_ERR = -22,
    //    MKL_DSS_I32BIT_ERR = -23,
    //    MKL_DSS_OOC_MEM_ERR = -24,
    //    MKL_DSS_OOC_OC_ERR = -25,
    //    MKL_DSS_OOC_RW_ERR = -26,
    //}

    /// <summary>
    /// DSS 求解器状态码枚举
    /// 表示 DSS 函数调用的执行结果和错误类型
    /// </summary>
    /// <remarks>
    /// 所有 DSS 函数返回此状态码，用于诊断求解过程中的问题
    /// </remarks>
    public enum DssStatus : int
    {
        /// <summary>
        /// 操作成功完成
        /// <para>函数执行正常，无错误发生</para>
        /// </summary>
        MKL_DSS_SUCCESS = 0,

        /// <summary>
        /// 零主元错误（数值奇异）
        /// <para>矩阵在因子分解过程中遇到零主元，表明矩阵奇异或接近奇异</para>
        /// <para>可能原因：</para>
        /// <list type="bullet">
        /// <item>矩阵行列式为零（不可逆）</item>
        /// <item>矩阵条件数过大（病态）</item>
        /// <item>约束系统中存在冗余约束</item>
        /// </list>
        /// </summary>
        /// <example>
        /// 处理建议：检查矩阵定义、添加正则化、使用预条件
        /// </example>
        MKL_DSS_ZERO_PIVOT = -1,

        /// <summary>
        /// 内存不足错误
        /// <para>系统无法分配所需内存</para>
        /// <para>可能原因：矩阵过大、填充率过高、系统内存不足</para>
        /// </summary>
        /// <example>
        /// 处理建议：减小问题规模、使用 OOC 模式、增加物理内存
        /// </example>
        MKL_DSS_OUT_OF_MEMORY = -2,

        /// <summary>
        /// 一般性失败
        /// <para>未分类的内部错误</para>
        /// </summary>
        MKL_DSS_FAILURE = -3,

        /// <summary>
        /// 行索引错误
        /// <para>CSR 格式中的行指针 (rowIndex) 不合法</para>
        /// <para>常见问题：</para>
        /// <list type="bullet">
        /// <item>rowIndex[0] 不等于 1（基于1）或 0（基于0）</item>
        /// <item>rowIndex 不是严格递增</item>
        /// <item>rowIndex[nRows] 与非零元素数不匹配</item>
        /// </list>
        /// </summary>
        MKL_DSS_ROW_ERR = -4,

        /// <summary>
        /// 列索引错误
        /// <para>CSR 格式中的列索引 (columns) 不合法</para>
        /// <para>常见问题：</para>
        /// <list type="bullet">
        /// <item>列索引超出范围 [1, nCols] 或 [0, nCols-1]</item>
        /// <item>同一行内有重复的列索引</item>
        /// </list>
        /// </summary>
        MKL_DSS_COL_ERR = -5,

        /// <summary>
        /// 非零元素数量过少
        /// <para>提供的非零元素少于矩阵结构所需</para>
        /// <para>例如：对角矩阵至少需要 n 个非零元</para>
        /// </summary>
        MKL_DSS_TOO_FEW_VALUES = -6,

        /// <summary>
        /// 非零元素数量过多
        /// <para>提供的非零元素多于声明的数量</para>
        /// <para>检查：rowIndex[nRows] - rowIndex[0] 是否等于实际非零元数</para>
        /// </summary>
        MKL_DSS_TOO_MANY_VALUES = -7,

        /// <summary>
        /// 矩阵非方阵错误
        /// <para>DSS 仅支持方阵（nRows == nCols）</para>
        /// <para>最小二乘问题需先转换为法方程</para>
        /// </summary>
        MKL_DSS_NOT_SQUARE = -8,

        /// <summary>
        /// 求解器状态错误
        /// <para>DSS 函数调用顺序不正确</para>
        /// <para>正确顺序：Create → Define Structure → Reorder → Factor → Solve → Delete</para>
        /// </summary>
        /// <example>
        /// 错误示例：在 Factor 之前调用 Solve
        /// </example>
        MKL_DSS_STATE_ERR = -9,

        /// <summary>
        /// 无效选项参数
        /// <para>传递给 DSS 函数的选项标志不合法</para>
        /// <para>检查：选项宏定义是否正确、是否使用了已废弃的选项</para>
        /// </summary>
        MKL_DSS_INVALID_OPTION = -10,

        /// <summary>
        /// 选项冲突
        /// <para>多个选项标志互相矛盾</para>
        /// <para>例如：同时指定 SYMMETRIC 和 NON_SYMMETRIC</para>
        /// </summary>
        MKL_DSS_OPTION_CONFLICT = -11,

        /// <summary>
        /// 消息级别错误
        /// <para>设置的诊断消息输出级别无效</para>
        /// </summary>
        MKL_DSS_MSG_LVL_ERR = -12,

        /// <summary>
        /// 终止级别错误
        /// <para>设置的错误终止级别无效</para>
        /// </summary>
        MKL_DSS_TERM_LVL_ERR = -13,

        /// <summary>
        /// 矩阵结构定义错误
        /// <para>dss_define_structure 调用失败</para>
        /// <para>可能原因：结构类型与实际数据不匹配</para>
        /// </summary>
        MKL_DSS_STRUCTURE_ERR = -14,

        /// <summary>
        /// 重排序（Reorder）错误
        /// <para>矩阵重排序步骤失败</para>
        /// <para>可能原因：矩阵结构不适合所选重排序算法</para>
        /// </summary>
        MKL_DSS_REORDER_ERR = -15,

        /// <summary>
        /// 矩阵数值错误
        /// <para>dss_factor_real/complex 中的数值有问题</para>
        /// <para>可能原因：NaN、Inf 或数值范围超限</para>
        /// </summary>
        MKL_DSS_VALUES_ERR = -16,

        /// <summary>
        /// 统计信息：矩阵无效
        /// <para>请求统计信息时矩阵状态不正确</para>
        /// </summary>
        MKL_DSS_STATISTICS_INVALID_MATRIX = -17,

        /// <summary>
        /// 统计信息：状态无效
        /// <para>当前求解器状态不支持请求的统计信息</para>
        /// </summary>
        MKL_DSS_STATISTICS_INVALID_STATE = -18,

        /// <summary>
        /// 统计信息：字符串参数无效
        /// <para>dss_statistics 的 statistic 参数字符串不合法</para>
        /// </summary>
        MKL_DSS_STATISTICS_INVALID_STRING = -19,

        /// <summary>
        /// 第一次重排序错误
        /// <para>初始符号重排序失败</para>
        /// </summary>
        MKL_DSS_REORDER1_ERR = -20,

        /// <summary>
        /// 预排序错误
        /// <para>矩阵预处理排序失败</para>
        /// </summary>
        MKL_DSS_PREORDER_ERR = -21,

        /// <summary>
        /// 对角元素错误
        /// <para>对角占优检查失败或对角元素缺失</para>
        /// <para>某些算法要求对角元素非零</para>
        /// </summary>
        MKL_DSS_DIAG_ERR = -22,

        /// <summary>
        /// 32位整数溢出错误
        /// <para>矩阵规模超过 32 位整数表示范围</para>
        /// <para>需要使用 64 位索引版本</para>
        /// </summary>
        MKL_DSS_I32BIT_ERR = -23,

        /// <summary>
        /// OOC（Out-of-Core）内存错误
        /// <para>核外求解模式下的内存分配失败</para>
        /// </summary>
        MKL_DSS_OOC_MEM_ERR = -24,

        /// <summary>
        /// OOC 打开/关闭错误
        /// <para>核外文件打开或关闭失败</para>
        /// </summary>
        MKL_DSS_OOC_OC_ERR = -25,

        /// <summary>
        /// OOC 读写错误
        /// <para>核外文件读写操作失败</para>
        /// <para>检查：磁盘空间、文件权限、I/O 子系统</para>
        /// </summary>
        MKL_DSS_OOC_RW_ERR = -26,
    }

    public interface ISparseSolverProvider :
        ISparseSolverProvider<double>,
        ISparseSolverProvider<float>,
        ISparseSolverProvider<Complex>,
        ISparseSolverProvider<Complex32>
    {
        /// <summary>
        /// Try to find out whether the provider is available, at least in principle.
        /// Verification may still fail if available, but it will certainly fail if unavailable.
        /// </summary>
        bool IsAvailable();

        /// <summary>
        /// Initialize and verify that the provided is indeed available. If not, fall back to alternatives like the managed provider
        /// </summary>
        void InitializeVerify();

        /// <summary>
        /// Frees memory buffers, caches and handles allocated in or to the provider.
        /// Does not unload the provider itself, it is still usable afterwards.
        /// </summary>
        void FreeResources();
    }

    public interface ISparseSolverProvider<T>
        where T : struct
    {
        DssStatus Solve(DssMatrixStructure matrixStructure, DssMatrixType matrixType, DssSystemType systemType, int rows, int cols, int nnz, int[] rowIdx, int[] colPtr, T[] values, int nRhs, T[] rhs, T[] solution);
    }
}

