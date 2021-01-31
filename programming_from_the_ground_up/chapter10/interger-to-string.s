.section .data
.equ LINUX_SYSCALL,0x80
.equ SYS_EXIT,1
.equ SYS_WRITE,4

.equ STDOUT,1

.section .bss
.lcomm buffer_data,11

.section .text
.globl _start
_start:
    pushl $buffer_data
    pushl $824
    call integer_to_string
    movb $'\n',buffer_data(,%eax,1)
    incl %eax
    movl %eax,%edx
    movl $buffer_data,%ecx
    movl $STDOUT,%ebx
    movl $SYS_WRITE,%eax
    int $LINUX_SYSCALL

    addl $8,%esp
    pushl $buffer_data
    pushl $0
    call integer_to_string
    movb $'\n',buffer_data(,%eax,1)
    incl %eax
    movl %eax,%edx
    movl $buffer_data,%ecx
    movl $STDOUT,%ebx
    movl $SYS_WRITE,%eax
    int $LINUX_SYSCALL

    addl $8,%esp
    pushl $buffer_data
    pushl $1
    call integer_to_string
    movb $'\n',buffer_data(,%eax,1)
    incl %eax
    movl %eax,%edx
    movl $buffer_data,%ecx
    movl $STDOUT,%ebx
    movl $SYS_WRITE,%eax
    int $LINUX_SYSCALL

    addl $8,%esp
    pushl $buffer_data
    pushl $-1
    call integer_to_string
    movb $'\n',buffer_data(,%eax,1)
    incl %eax
    movl %eax,%edx
    movl $buffer_data,%ecx
    movl $STDOUT,%ebx
    movl $SYS_WRITE,%eax
    int $LINUX_SYSCALL

    movl $SYS_EXIT,%eax
    int $LINUX_SYSCALL

.equ ST_VALUE,8
.equ ST_BUFFER,12
.type integer_to_string,@function
integer_to_string:
    pushl %ebp
    movl %esp,%ebp

    movl ST_VALUE(%ebp),%eax
    movl $10,%edi
    xorl %ecx,%ecx

div_loop:
    xorl %edx,%edx
    divl %edi
    incl %ecx
    addl $'0',%edx
    pushl %edx
    cmpl $0,%eax
    jne div_loop

    movl %ecx,%eax
    movl ST_BUFFER(%ebp),%ebx
div_writeback:
    popl %edx
    movb %dl,(%ebx)
    incl %ebx
    decl %ecx
    cmpl $0,%ecx
    jne div_writeback

    #movl %ebp,%esp
    popl %ebp
    ret
