#this is test

.section .text
.globl _start
_start:
    mov $101,%eax
    testl $1,%eax
    jz  aaa
    nop

    xorl %eax,%eax
    testl $1,%eax
    jz aaa
    nop
aaa:
    movl $1,%eax
    int $0x80
