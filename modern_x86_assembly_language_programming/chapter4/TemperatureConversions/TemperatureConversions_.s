
r8_SfFtoC: .double 0.5555555556
r8_SfCtoF: .double 1.8
i4_32:  .long 32

.section .text
.globl FtoC_
.globl CtoF_

.type FtoC_,@function
FtoC_:
    pushl %ebp
    movl %esp,%ebp

    fldl (r8_SfFtoC)
    fildl (i4_32)
    fldl 8(%ebp)

    fsubp
    fmulp

    popl %ebp
    ret


.type CtoF_,@function
CtoF_:
    pushl %ebp
    movl %esp,%ebp

    fldl 8(%ebp)
    fmull (r8_SfCtoF)
    fiaddl (i4_32)

    popl %ebp
    ret

