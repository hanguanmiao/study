#extern "C" int CompareArrays_(const int *x, const int *y, int n);

.section .text
.globl CompareArrays_


.type CompareArrays_,@function
CompareArrays_:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    pushl %edi

    movl 8(%ebp),%esi
    movl 12(%ebp),%edi
    movl 16(%ebp),%ecx

    movl $-1,%eax
    test %ecx,%ecx
    jle CompareArrays_Out

    movl %ecx,%eax
    repe cmpsl
    je CompareArrays_Out
    subl %ecx,%eax
    decl %eax

CompareArrays_Out:
    popl %edi
    popl %esi
    popl %ebp
    ret
