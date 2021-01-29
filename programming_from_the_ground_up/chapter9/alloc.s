#this is comment

.section .data

.equ LINUX_SYSCALL,0x80
.equ SYS_BRK,45

heap_begin:
    .long 0
current_brk:
    .long 0

.section .bss

.section .text

.globl allocate_init
.type allocate_init,@function
allocate_init:
    xorl %ebx,%ebx
    movl $SYS_BRK,%eax
    int $LINUX_SYSCALL
    movl %eax,heap_begin
    movl %eax,current_brk
    ret

.equ ALLOCATE_SIZE,8
.globl allocate
.type allocate,@function
allocate:
    pushl %ebp
    movl %esp,%ebp

    movl ALLOCATE_SIZE(%ebp),%ebx
    addl current_brk,%ebx
    movl $SYS_BRK,%eax
    int $LINUX_SYSCALL
    movl %eax,current_brk

    movl %ebp,%esp
    popl %ebp
    ret
