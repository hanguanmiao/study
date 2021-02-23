#extern "C" bool CalcSphereAreaVolume_(double r, double *sa, double *v);

#CalcSphereAreaVolume_
.globl CalcSphereAreaVolume_

r8_4p0: .double 4.0
r8_3p0: .double 3.0

.section .text

.type CalcSphereAreaVolume_,@function
CalcSphereAreaVolume_:
    pushl %ebp
    movl %esp,%ebp

    xorl %eax,%eax
    fldl 8(%ebp)
    fldz
    fcomip %st(1),%st(0)
    fstp %st(0)
    jp CalcSphereAreaVolume_out
    ja CalcSphereAreaVolume_out

    fldl 8(%ebp)
    fld %st(0)
    fmul %st(0)
    fldpi
    fmull (r8_4p0)
    fmulp %st(1)
    movl 16(%ebp),%ecx
    fstl (%ecx)

    fmulp %st(1)
    fdivl (r8_3p0)
    movl 20(%ebp),%ecx
    fstpl (%ecx)
    movl $1,%eax

CalcSphereAreaVolume_out:
    popl %ebp
    ret
