.section .text

.globl _start
_start:
    movq $5,%rax
    sar %rax
    nop
