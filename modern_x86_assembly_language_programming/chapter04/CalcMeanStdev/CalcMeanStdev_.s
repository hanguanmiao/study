#extern bool CalcMeanStdev_(const double *a, int n, double *mean, double *stdev);

.globl CalcMeanStdev_

.section .text

.type CalcMeanStdev_,@function
CalcMeanStdev_:
    pushl %ebp
    movl %esp,%ebp
    subl $4,%esp

    xorl %eax,%eax
    movl 12(%ebp),%ecx
    cmpl $1,%ecx
    jle CalcMeanStdev_out
    decl %ecx
    movl %ecx,-4(%ebp)
    incl %ecx
    movl 8(%ebp),%edx
    fldz
CalcMeanStdev_mean_loop:
    faddl (%edx)
    addl $8,%edx
    decl %ecx
    jnz CalcMeanStdev_mean_loop
    fidivl 12(%ebp)


    fldz
    movl 8(%ebp),%edx
    movl 12(%ebp),%ecx
CalcMeanStdev_stdev_loop:
    fldl (%edx)
    fsub %st(2)
    fmul %st(0)
    faddp
    addl $8,%edx
    decl %ecx
    jnz CalcMeanStdev_stdev_loop
    fidivl -4(%ebp)
    fsqrt

    movl 20(%ebp),%edx
    fstpl (%edx)
    movl 16(%ebp),%edx
    fstpl (%edx)

    movl $1,%eax

CalcMeanStdev_out:
    addl $4,%esp
    popl %ebp
    ret
