;extern "C int MemoryAddressing_(int i, int *v1, int *v2, int *v3, int *v4)
;0=error
;1=success

global NumFibVals_

section .data
FibVals dd 0,1,1,2,3,5,8,13
    dd 21,34,55,89,144,233,377,610
NumFibVals_ dd ($-FibVals)/4

section .text
global MemoryAddressing_
MemoryAddressing_:
    push ebp
    mov ebp,esp
    push ebx
    push esi
    push edi

    xor eax,eax
    mov edi,[ebp+8]
    cmp edi,0
    jl MemoryAddressing_out
    cmp edi,[NumFibVals_]
    jge MemoryAddressing_out

;示例1——基址寄存器
    mov ebx,FibVals
    mov esi,edi
    shl esi,2
    add ebx,esi
    mov edx,[ebx] ;基址寄存器
    mov ecx,[ebp+12]
    mov [ecx],edx

;示例2——基址寄存器+偏移量
    mov esi,edi
    shl esi,2
    mov edx,[esi+FibVals] ;基址寄存器+偏移量
    mov ecx,[ebp+16]
    mov [ecx],edx

;示例3——基址寄存器+索引寄存器
    mov ebx,FibVals
    mov esi,edi
    shl esi,2
    mov edx,[ebx+esi] ;基址寄存器+索引寄存器
    mov ecx,[ebp+20]
    mov [ecx],edx

;示例4——基址寄存器+索引寄存器*比例因子
    mov ebx,FibVals
    mov esi,edi
    mov edx,[ebx+esi*4] ;基址寄存器+索引寄存器*比例因子
    mov ecx,[ebp+24]
    mov [ecx],edx

    or eax,1
MemoryAddressing_out:
    pop edi
    pop esi
    pop ebx
    mov esp,ebp
    pop ebp
    ret


