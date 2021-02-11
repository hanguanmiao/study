; this is a test
;extern "C" int CalcMatrixRowColSums_(const int *x, int nrows, int ncols,
;int *row_sums, int *col_sums);

section .text
global CalcMatrixRowColSums_
CalcMatrixRowColSums_:
    push ebp
    mov ebp,esp
    push ebx
    push edi
    push esi

    ;test nrows,ncols
    xor eax,eax
    mov ecx,[ebp+12]
    cmp ecx,0
    jle CalcMatrixRowColSums_out
    mov ecx,[ebp+16]
    cmp ecx,0
    jle CalcMatrixRowColSums_out

    ;init col_sums
    mov edi,[ebp+24]
    rep stosd

    mov ebx,[ebp+8];x
    mov esi,0;i=0
loop1:
    mov ecx,[ebp+20]
    xor eax,eax
    mov [ecx+esi*4],eax;row_sums[i]=0
    mov edx,[ebp+16]
    imul edx,esi;k=i*inols
    mov edi,0;j
loop2:
    mov eax,edx
    add eax,edi;k+j
    mov eax,[ebx+eax*4];temp=x[k+j]
    mov ecx,[ebp+20]
    add [ecx+esi*4],eax
    mov ecx,[ebp+24]
    add [ecx+edi*4],eax
    inc edi
    cmp edi,[ebp+16]
    jl loop2
    inc esi
    cmp esi,[ebp+12]
    jl loop1
    mov eax,1

CalcMatrixRowColSums_out:
    pop esi
    pop edi
    pop ebx
    mov esp,ebp
    pop ebp
    ret
