.section .text
.globl CalcSum_
.type CalcSum_,@function
CalcSum_:
    pushl %ebp
    movl %esp,%ebp

    movl 8(%ebp),%eax
    movl 12(%ebp),%edx
    movl 16(%ebp),%ecx

    addl %edx,%eax
    addl %ecx,%eax

    popl %ebp
    ret
