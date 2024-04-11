#extern bool CalcMinMax_(const float *a, int n, float *min, float *max);

.section .text

#r4_MinFloat: .long 0ff7fffffh
#r4_MaxFloat: .long 7f7fffffh

.globl CalcMinMax_

.type CalcMinMax_,@function
CalcMinMax_:
    pushl %ebp
    movl %esp,%ebp

    xorl %eax,%eax
    movl 12(%ebp),%ecx
    cmpl $0,%ecx
    jle CalcMinMax_out

    movl 8(%ebp),%edx
    fld (%edx)
    fld %st(0)
    decl %ecx
    addl $4,%edx
CalcMinMax_loop:
    cmpl $0,%ecx
    jle CalcMinMax_out2
    fld (%edx)
    fld %st(0)
    fcomi %st(2),%st(0)
    fcmovnbe %st(2),%st(0) #为了演示？
    fstp %st(2)
    fcomi %st(2),%st(0)
    fcmovb %st(2),%st(0)
    fstp %st(2)
    decl %ecx
    addl $4,%edx
    jmp CalcMinMax_loop

CalcMinMax_out2:
    movl $1,%eax
    movl 16(%ebp),%edx
    fstp (%edx)
    movl 20(%ebp),%edx
    fstp (%edx)
CalcMinMax_out:
    popl %ebp
    ret
