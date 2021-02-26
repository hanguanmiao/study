#extern void RectToPolar_(double x, double y, double *r, double *a);
#extern void PolarToRect_(double r, double a, double *x, double *y);

.section .text

DegToRad: .double 0.01745329252
RadToDeg: .double 57.2957795131

.globl RectToPolar_
.globl PolarToRect_

.type RectToPolar_,@function
RectToPolar_:
    pushl %ebp
    movl %esp,%ebp

    fldl 16(%ebp)
    fldl 8(%ebp)
    fpatan
    fmull (RadToDeg)
    movl 28(%ebp),%eax
    fstpl (%eax)

    fldl 8(%ebp)
    fmul %st(0),%st(0)
    fldl 16(%ebp)
    fmul %st(0),%st(0)
    faddp %st(1)
    fsqrt
    movl 24(%ebp),%eax
    fstpl (%eax)

    popl %ebp
    ret

.type PolarToRect_,@function
PolarToRect_:
    pushl %ebp
    movl %esp,%ebp

    fldl 16(%ebp)
    fmull (DegToRad)
    fsincos

    fmull 8(%ebp)
    movl 24(%ebp),%eax
    fstpl (%eax)

    fmull 8(%ebp)
    movl 28(%ebp),%eax
    fstpl (%eax)

    popl %ebp
    ret
