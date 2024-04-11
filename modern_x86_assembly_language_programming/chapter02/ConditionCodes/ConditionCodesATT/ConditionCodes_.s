.section .text
.globl SignedMinA_
.globl SignedMaxA_
.globl SignedMinB_
.globl SignedMaxB_

#extern int SignedMinA_(int a, int b, int c);
.type SignedMinA_,@function
SignedMinA_:
    pushl %ebp
    movl %esp,%ebp

    movl 8(%ebp),%eax
    movl 12(%ebp),%ecx
    cmpl %ecx,%eax
    jle SignedMinA_cmpnext
    movl %ecx,%eax

SignedMinA_cmpnext:
    movl 16(%ebp),%ecx
    cmpl %ecx,%eax
    jle  SignedMinA_ret
    movl %ecx,%eax

SignedMinA_ret:
    popl %ebp
    ret

#extern int SignedMaxA_(int a, int b, int c);
.type SignedMaxA_,@function
SignedMaxA_:
    pushl %ebp
    movl %esp,%ebp

    movl 8(%ebp),%eax
    movl 12(%ebp),%ecx
    cmpl %ecx,%eax
    jge SignedMaxA_cmpnext
    movl %ecx,%eax

SignedMaxA_cmpnext:
    movl 16(%ebp),%ecx
    cmpl %ecx,%eax
    jge SignedMaxA_ret
    movl %ecx,%eax

SignedMaxA_ret:
    popl %ebp
    ret

#extern int SignedMinB_(int a, int b, int c);
.type SignedMinB_,@function
SignedMinB_:
    pushl %ebp
    movl %esp,%ebp

    movl 8(%ebp),%eax
    movl 12(%ebp),%ecx
    cmpl %ecx,%eax
    cmovg %ecx,%eax

    movl 16(%ebp),%ecx
    cmpl %ecx,%eax
    cmovg %ecx,%eax

    popl %ebp
    ret

#extern int SignedMaxB_(int a, int b, int c);
.type SignedMaxB_,@function
SignedMaxB_:
    pushl %ebp
    movl %esp,%ebp

    movl 8(%ebp),%eax
    movl 12(%ebp),%ecx
    cmpl %ecx,%eax
    cmovl %ecx,%eax

    movl 16(%ebp),%ecx
    cmpl %ecx,%eax
    cmovl %ecx,%eax

    popl %ebp
    ret
