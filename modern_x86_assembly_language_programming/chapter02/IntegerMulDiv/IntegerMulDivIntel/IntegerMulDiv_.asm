; extern "C" int IntergerMulDiv_(int a, int b, int *prod, int *quo, int *rem);
section .text
global IntergerMulDiv_
IntergerMulDiv_:
    push ebp
    mov ebp,esp

    xor eax,eax
    mov ecx,[ebp+12]
    or ecx,ecx
    jz IntergerMulDiv_out
    mov eax,[ebp+8]
    imul ecx,eax
    mov edx,[ebp+16]
    mov [edx],ecx

    cdq
    mov ecx,[ebp+12]
    idiv dword ecx
    mov ecx,[ebp+20]
    mov [ecx],eax
    mov ecx,[ebp+24]
    mov [ecx],edx
    mov eax,1

IntergerMulDiv_out:
    pop ebp
    ret
