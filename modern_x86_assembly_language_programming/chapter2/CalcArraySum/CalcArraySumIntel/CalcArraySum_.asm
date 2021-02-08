;extern "C" int CalcArraySum_(const int *x, int n);
section .text
global CalcArraySum_

CalcArraySum_:
    push ebp
    mov ebp,esp
    mov edx,[ebp+8]
    mov ecx,[ebp+12]
    xor eax,eax
    cmp ecx,0
    jle   CalcArraySum_out

CalcArraySum_loop:
    add eax,[edx]
    add edx,4
    loop CalcArraySum_loop

CalcArraySum_out:
    pop ebp
    ret
