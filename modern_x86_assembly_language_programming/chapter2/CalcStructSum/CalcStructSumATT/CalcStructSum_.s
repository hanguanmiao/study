.include "TestStruct_.s"

.section .text
#extern "C" long long CalcStructSum_(const TestStruct *ts);

.globl CalcStructSum_
.type CalcStructSum_,@function
CalcStructSum_:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    pushl %ebx

    movl 8(%ebp),%esi
#    movl Val8(%esi),%eax
    movsbl Val8(%esi),%eax
    movswl Val16(%esi),%ecx
    add %ecx,%eax

    cdq
    movl %eax,%ebx
    movl %edx,%ecx

    movl Val32(%esi),%eax
    cdq
    addl %ebx,%eax
    addl %ecx,%edx

    addl Val64(%esi),%eax
    adcl Val64+4(%esi),%edx

    popl %ebx
    popl %esi
    movl %ebp,%esp
    pop %ebp
    ret
