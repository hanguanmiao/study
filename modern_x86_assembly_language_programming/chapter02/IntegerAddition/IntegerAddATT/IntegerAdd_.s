
.section .text
.globl IntergerAdd_
.type IntergerAdd_,@function

IntergerAdd_:
    pushl %ebp
    movl %esp,%ebp

    movb 8(%ebp),%al
    addb %al,GlChar
    movw 12(%ebp),%ax
    addw %ax,GlShort
    movl 16(%ebp),%eax
    addl %eax,GlInt
    movl 20(%ebp),%eax
    movl 24(%ebp),%edx
    addl %eax,GlLongLong
    adcl %edx,GlLongLong+4

    popl %ebp
    ret
