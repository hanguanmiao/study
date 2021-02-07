.section .text
.globl SignedEq_
.type SignedEq_,@function

SignedEq_:
    pushl %ebp
    movl %esp,%ebp
    xorl %eax,%eax
    movl 8(%ebp),%ecx
    cmpl 12(%ebp),%ecx
    sete %al
    popl %ebp
    ret
