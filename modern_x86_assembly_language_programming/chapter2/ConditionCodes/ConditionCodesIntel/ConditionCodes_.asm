section .text
global SignedMinA_
global SignedMaxA_
global SignedMinB_
global SignedMaxB_

;extern int SignedMinA_(int a, int b, int c);
SignedMinA_:
    push ebp
    mov ebp,esp

    mov eax,[ebp+8]
    mov ecx,[ebp+12]
    cmp eax,ecx
    jle SignedMinA_nextcmp
    mov eax,ecx

SignedMinA_nextcmp:
    mov ecx,[ebp+16]
    cmp eax,ecx
    jle SignedMinA_ret
    mov eax,ecx

SignedMinA_ret:
    pop ebp
    ret

;extern int SignedMaxA_(int a, int b, int c);
SignedMaxA_:
    push ebp
    mov ebp,esp

    mov eax,[ebp+8]
    mov ecx,[ebp+12]
    cmp eax,ecx
    jge SignedMaxA_nextcmp
    mov eax,ecx

SignedMaxA_nextcmp:
    mov ecx,[ebp+16]
    cmp eax,ecx
    jge SignedMaxA_ret
    mov eax,ecx

SignedMaxA_ret:
    pop ebp
    ret

;extern int SignedMinB_(int a, int b, int c);
SignedMinB_:
    push ebp
    mov ebp,esp

    mov eax,[ebp+8]
    mov ecx,[ebp+12]
    cmp eax,ecx
    cmovg eax,ecx

    mov ecx,[ebp+16]
    cmp eax,ecx
    cmovg eax,ecx

    pop ebp
    ret

;extern int SignedMaxB_(int a, int b, int c);
SignedMaxB_:
    push ebp
    mov ebp,esp

    mov eax,[ebp+8]
    mov ecx,[ebp+12]
    cmp eax,ecx
    cmovl eax,ecx

    mov ecx,[ebp+16]
    cmp eax,ecx
    cmovl eax,ecx

    pop ebp
    ret
