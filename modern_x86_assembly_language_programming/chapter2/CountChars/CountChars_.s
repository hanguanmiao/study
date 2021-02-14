#extern "C" int CountChars_(wchar_t *s, wchar_t c);
.section .text
.globl CountChars_
.globl CountWChars_

.type CountChars_,@function
CountChars_:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    movl 8(%ebp),%esi
    movb 12(%ebp),%cl
    xorl %edx,%edx
CountChars_loop:
    lodsb
    orb %al,%al
    jz CountChars_out
    cmpb %al,%cl
    jne CountChars_loop
    incl %edx
    jmp CountChars_loop

CountChars_out:
    movl %edx,%eax
    popl %esi
    popl %ebp
    ret


.type CountWChars_,@function
CountWChars_:
    pushl %ebp
    movl %esp,%ebp
    pushl %esi
    movl 8(%ebp),%esi
    movl 12(%ebp),%ecx
    xorl %edx,%edx
CountWChars_loop:
    lodsl
    orl %eax,%eax
    jz CountWChars_out
    cmpl %eax,%ecx
    jne CountWChars_loop
    incl %edx
    jmp CountWChars_loop

CountWChars_out:
    movl %edx,%eax
    popl %esi
    popl %ebp
    ret
