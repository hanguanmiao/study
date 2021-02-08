;extern "C" int CalcArraySquares_(int *y, const int *x, int n);
section .text
global CalcArraySquares_
CalcArraySquares_:
    push ebp
    mov ebp,esp
    push ebx
    push edi

    mov edx,[ebp+8] ;y
    mov ebx,[ebp+12] ;x
    mov ecx,[ebp+16];n
    xor eax,eax;sum

    cmp ecx,0
    jle CalcArraySquares_out

CalcArraySquares_loop:
    mov edi,[ebx]
    imul edi,edi
    mov [edx],edi
    add eax,edi
    add ebx,4
    add edx,4
    loop CalcArraySquares_loop

CalcArraySquares_out:
    pop edi
    pop ebx
    pop ebp
    ret
