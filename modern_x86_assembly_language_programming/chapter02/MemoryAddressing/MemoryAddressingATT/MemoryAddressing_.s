#extern "C int MemoryAddressing_(int i, int *v1, int *v2, int *v3, int *v4)
#0=error
#1=success

.globl NumFibVals_

.section .data
FibVals:
    .long 0,1,1,2,3,5,8,13
    .long 21,34,55,89,144,233,377,610
NumFibVals_:
    .long (.-FibVals)/4

.section .text
.globl MemoryAddressing_
MemoryAddressing_:
    pushl %ebp
    movl %esp,%ebp
    pushl %ebx
    pushl %esi
    pushl %edi

    xorl %eax,%eax
    movl 8(%ebp),%edi
    cmpl $0,%edi
    jl MemoryAddressing_out
    cmpl (NumFibVals_),%edi
    jge MemoryAddressing_out

#示例1——基址寄存器
    movl $FibVals,%ebx
    movl %edi,%esi
    shll $2,%esi
    addl %esi,%ebx
    movl (%ebx),%edx #基址寄存器
    movl 12(%ebp),%ecx
    movl %edx,(%ecx)

#示例2——基址寄存器+偏移量
    movl %edi,%esi
    shll $2,%esi
    movl FibVals(%esi),%edx #基址寄存器+偏移量
    movl 16(%ebp),%ecx
    movl %edx,(%ecx)

#示例3——基址寄存器+索引寄存器
    movl $FibVals,%ebx
    movl %edi,%esi
    shll $2,%esi
    movl (%ebx,%esi),%edx #基址寄存器+索引寄存器
    movl 20(%ebp),%ecx
    movl %edx,(%ecx)

#示例4——基址寄存器+索引寄存器*比例因子
    movl $FibVals,%ebx
    movl %edi,%esi
    movl (%ebx,%esi,4),%edx #基址寄存器+索引寄存器*比例因子
    movl 24(%ebp),%ecx
    movl %edx,(%ecx)

    orl $1,%eax
MemoryAddressing_out:
    popl %edi
    popl %esi
    popl %ebx
    movl %ebp,%esp
    popl %ebp
    ret


