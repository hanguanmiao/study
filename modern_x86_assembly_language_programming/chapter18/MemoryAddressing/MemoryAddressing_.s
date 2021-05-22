.globl MemoryAddressing_
.globl NumFibVals_
.globl FibValsSum_

.section .data
FibValsSum_:
    .int 0

.section .text


FibVals:
    .int 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597
NumFibVals_:
    .int (.-FibVals)/4

.type MemoryAddressing_,@function
MemoryAddressing_:
    cmp $0,%eax
    jl InvalidIndex
    cmp (NumFibVals_),%eax
    jge InvalidIndex

    mov $1,%eax
    ret

InvalidIndex:
    xor %eax,%eax
    ret
