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
    decl %eax
    movl %ecx,-4(%ebp)
    incl %ecx
    movl 8(%ebp),%edx
    fldz
CalcMeanStdev_add_loop:
    faddl (%edx)
    addl $8,%edx
    decl %ecx
    jnz CalcMeanStdev_add_loop
    fidivl 12(%ebp)
    movl 16(%ebp),%edx
    fstpl (%edx)
    movl $1,%eax

CalcMeanStdev_out:
    addl $4,%esp
    popl %ebp
    ret
