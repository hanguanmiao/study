# this is a test
#extern "C" int CalcMatrixRowColSums_(const int *x, int nrows, int ncols,
#int *row_sums, int *col_sums);

.section .text
.globl CalcMatrixRowColSums_
.type CalcMatrixRowColSums_,@function
CalcMatrixRowColSums_:
    xorl %eax,%eax

    #init col_sums
    movl %edi,24(%ebp)
    rep stosl

    ret
