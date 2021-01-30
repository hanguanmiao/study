#this is comment

.section .data

.equ LINUX_SYSCALL,0x80
.equ SYS_BRK,45

.equ MEMORY_HEAD_SIZE,8
.equ MEMORY_HEAD_FLAGS,0
.equ MEMORY_HEAD_MEMSIZE,4
.equ MEMORY_HEAD_FLAGS_UNUSED,0
.equ MEMORY_HEAD_FLAGS_USED,1

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

    movl heap_begin,%eax
    movl current_brk,%ebx
    cmpl %eax,%ebx
    je allocate_memory
allocate_search_loop:
    cmpl $MEMORY_HEAD_FLAGS_USED,MEMORY_HEAD_FLAGS(%eax)
    je allocate_search_loop_again
    movl ALLOCATE_SIZE(%ebp),%ecx
    cmpl MEMORY_HEAD_MEMSIZE(%eax),%ecx
    jg allocate_search_loop_again
    movl $MEMORY_HEAD_FLAGS_USED,MEMORY_HEAD_FLAGS(%eax)
    addl $MEMORY_HEAD_SIZE,%eax
    movl %ebp,%esp
    popl %ebp
    ret

allocate_search_loop_again:
    movl MEMORY_HEAD_MEMSIZE(%eax),%edx
    addl $MEMORY_HEAD_SIZE,%edx
    addl %edx,%eax
    cmpl %eax,current_brk
    jne allocate_search_loop

allocate_memory:
#%ebx存储当前的brk
    movl ALLOCATE_SIZE(%ebp),%ecx
    addl $MEMORY_HEAD_SIZE,%ebx
    addl %ecx,%ebx
    movl $SYS_BRK,%eax
    pushl %ebx
    pushl %ecx
    int $LINUX_SYSCALL
    popl %ecx
    popl %ebx
    cmpl %ebx,%eax
    jne allocate_error
    movl current_brk,%eax
    movl $MEMORY_HEAD_FLAGS_USED,MEMORY_HEAD_FLAGS(%eax)
    movl %ecx, MEMORY_HEAD_MEMSIZE(%eax)
    addl $MEMORY_HEAD_SIZE,%eax
    movl %ebx,current_brk

    movl %ebp,%esp
    popl %ebp
    ret

allocate_error:
    xorl %eax,%eax
    movl %ebp,%esp
    popl %ebp
    ret

.equ DEALLOCATE_ADDRESS,4
.globl deallocate
.type deallocate,@function
deallocate:
    movl DEALLOCATE_ADDRESS(%esp),%ebx
    movl %ebx,%ecx
    addl -4(%ebx),%ecx
    cmpl current_brk,%ecx
    je deallocate_free
    movl $MEMORY_HEAD_FLAGS_UNUSED,-MEMORY_HEAD_SIZE(%ebx)
    ret

deallocate_free:
    subl $MEMORY_HEAD_SIZE,%ebx
    movl $SYS_BRK,%eax
    int $LINUX_SYSCALL
    movl %eax,current_brk
    ret
