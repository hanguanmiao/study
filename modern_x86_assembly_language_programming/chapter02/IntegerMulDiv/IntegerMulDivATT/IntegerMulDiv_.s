# extern "C" int IntergerMulDiv_(int a, int b, int *prod, int *quo, int *rem);

.section .text
.globl IntergerMulDiv_
.type IntergerMulDiv_,@function
IntergerMulDiv_:
    pushl %ebp
    movl %esp,%ebp

    xorl %eax,%eax
    movl 12(%ebp),%ecx
    orl %ecx,%ecx
    jz IntergerMulDiv_ret
    movl 8(%ebp),%eax

    imull %eax,%ecx
    movl 16(%ebp),%edx
    movl %ecx,(%edx)

    movl 12(%ebp),%ecx
    cdq
    idivl %ecx
    movl 20(%ebp),%ecx
    movl %eax,(%ecx)
    movl 24(%ebp),%ecx
    movl %edx,(%ecx)
    movl $1,%eax

IntergerMulDiv_ret:
    popl %ebp
    ret
