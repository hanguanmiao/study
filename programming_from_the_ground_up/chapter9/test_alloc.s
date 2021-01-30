#this is comment

.section .data

.equ LINUX_SYSCALL,0x80
.equ SYS_EXIT,1

.section .bss

.section .text

.globl _start
_start:
    call allocate_init

    pushl $1
    call allocate
    movb $100,(%eax)
    pushl %eax
    call deallocate
    addl $8,%esp

    pushl $1
    call allocate
    movb $100,(%eax)
    pushl $2
    call allocate
    movb $100,(%eax)
    pushl $3
    call allocate
    movb $100,(%eax)
    push %eax
    push $4
    call allocate
    movl $100,(%eax)
    addl $4,%esp
    call deallocate
    push $3
    call allocate
    movb $100,(%eax)

    movl $SYS_EXIT,%eax
    xorl %ebx,%ebx
    int $LINUX_SYSCALL

