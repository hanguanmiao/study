#this is comment

.section .data

.equ LINUX_SYSCALL,0x80
.equ SYS_EXIT,1
.equ SYS_BRK,45

.section .bss

.section .text

.globl _start
_start:
    xorl %ebx,%ebx
    movl $SYS_BRK,%eax
    int $LINUX_SYSCALL


pushl $1
call malloc
    pushl $4
    call malloc



    movl $SYS_EXIT,%eax
    xorl %ebx,%ebx
    int $LINUX_SYSCALL
