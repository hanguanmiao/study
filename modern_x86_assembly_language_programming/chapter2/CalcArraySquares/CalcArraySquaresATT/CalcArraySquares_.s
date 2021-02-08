#extern "C" int CalcArraySquares_(int *y, const int *x, int n);
.section .text

.globl CalcArraySquares_
.type CalcArraySquares_,@function
CalcArraySquares_:
    pushl %ebp
    movl %esp,%ebp
    pushl %ebx
    pushl %edi

    movl 8(%ebp),%edx #y
    movl 12(%ebp),%ebx #x
    movl 16(%ebp),%ecx #n
    xorl %eax,%eax #sum

    cmpl $0,%ecx
    jle CalcArraySquares_out

CalcArraySquares_loop:
    movl (%ebx),%edi
    imul %edi,%edi
    movl %edi,(%edx)
    addl %edi,%eax
    addl $4,%ebx
    addl $4,%edx
    loop CalcArraySquares_loop

CalcArraySquares_out:
    popl %edi
    popl %ebx
    popl %ebp
    ret
