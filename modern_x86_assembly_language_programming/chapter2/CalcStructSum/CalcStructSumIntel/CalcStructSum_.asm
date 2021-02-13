%include "TestStruct_.inc"

section .text
;extern "C" long long CalcStructSum_(const TestStruct *ts);

global CalcStructSum_
CalcStructSum_:
    push ebp
    mov ebp,esp
    push esi
    push ebx

    mov esi,[ebp+8]
    movsx eax,byte [esi+TestStruct.Val8]
    movsx ecx,word [esi+TestStruct.Val16]
    add eax,ecx

    cdq
    mov ebx,eax
    mov ecx,edx

    mov eax,[esi+TestStruct.Val32]
    cdq
    add eax,ebx
    adc edx,ecx

    add eax,[esi+TestStruct.Val64]
    adc edx,[esi+TestStruct.Val64+4]

    pop ebx
    pop esi
    mov esp,ebp
    pop ebp
    ret
;运行有错误
