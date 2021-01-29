#this is comment

.section .data

.equ LINUX_SYSCALL,0x80
.equ SYS_EXIT,1

.section .bss

.section .text

.globl _start
_start:
    call allocate_init
    pushl $4
    call allocate
    movl $100,(%eax)

    movl $SYS_EXIT,%eax
    xorl %ebx,%ebx
    int $LINUX_SYSCALL

