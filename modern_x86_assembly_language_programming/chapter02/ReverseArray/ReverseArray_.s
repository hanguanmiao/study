#extern "C" void ReverseArray_(int *y, const int *x, int n);

.section .text
.globl ReverseArray_

.type ReverseArray_,@function
ReverseArray_:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    pushl %edi
    pushfl

    movl 8(%ebp),%edi
    movl 12(%ebp),%esi
    movl 16(%ebp),%ecx

    xorl %eax,%eax
    test %ecx,%ecx
    jle ReverseArray_out
    lea -4(%esi,%ecx,4),%esi
    std
ReverseArray_loop:
    lodsl
    movl %eax,(%edi)
    addl $4,%edi
    decl %ecx
    test %ecx,%ecx
    jne ReverseArray_loop
    movl $1,%eax

ReverseArray_out:
    popfl
    popl %edi
    popl %esi
    popl %ebp
    ret
