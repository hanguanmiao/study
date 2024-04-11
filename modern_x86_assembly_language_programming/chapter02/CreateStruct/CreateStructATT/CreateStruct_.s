#extern TestStruct *CreateStruct_(signed char val8, short val16, int val32, long long val64);
#extern void ReleaseTestStruct_(TestStruct *p);
.include "TestStruct_.s"

.section .text
.globl CreateStruct_
.globl ReleaseTestStruct_

.type CreateStruct_,@function
CreateStruct_:
    pushl %ebp
    movl %esp,%ebp
    pushl $TestStructSize
    call malloc
    add $4,%esp
    orl %eax,%eax
    jz CreateStruct_OUT
    movb 8(%ebp),%dl
    movb %dl,Val8(%eax)
    movw 12(%ebp),%dx
    movw %dx,Val16(%eax)
    movl 16(%ebp),%edx
    movl %edx,Val32(%eax)
    movl 20(%ebp),%edx
    movl %edx,Val64(%eax)
    movl 24(%ebp),%edx
    movl %edx,Val64+4(%eax)

CreateStruct_OUT:
    popl %ebp
    ret


.type ReleaseTestStruct_,@function
ReleaseTestStruct_:
    pushl %ebp
    movl %esp,%ebp
    pushl 8(%ebp)
    call free
    addl $4,%esp
    popl %ebp
    ret
