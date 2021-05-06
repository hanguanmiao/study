.section .text
.globl IntegerAdd_
.globl IntegerMul_
.globl IntegerDiv_

.type IntegerAdd_,@function
IntegerAdd_:
    addq %rdi,%rsi
    addq %rdx,%rcx
    addq %r9,%r8

    addq %r8,%rcx
    addq %rcx,%rsi
    movq %rsi,%rax

    ret


.type IntegerMul_,@function
IntegerMul_:
    movsx %dil,%r10
    movsx %si,%r11
    imulq %r11,%r10

    movsx %edx,%r11
    imulq %r11,%rcx

    movsx %r8b,%r11
    movsx %r9w,%r12
    imulq %r12,%r11

    movsxl 8(%rsp),%rax
    imulq 16(%rsp),%rax

    imulq %r11,%rax
    imulq %r10,%rax
    imulq %rcx,%rax

    ret


.type IntegerDiv_,@function
IntegerDiv_:
    mov %rdx, %r10
    mov %rdi, %rax
    cqo
    idiv %rsi
    mov %rax, (%r10)
    mov %rdx, 8(%r10)

    mov %rcx, %rax
    cqo
    idiv %r8
    mov %rax, (%r9)
    mov %rdx, 8(%r9)

    ret
