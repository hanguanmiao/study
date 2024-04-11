extern GlChar
extern GlShort
extern GlInt
extern GlLongLong

section .text

global IntergerAdd_

IntergerAdd_:
    push ebp
    mov ebp,esp

    mov byte al,[ebp+8]
    add byte [GlChar],al
    mov word ax,[ebp+12]
    add word [GlShort],ax
    mov dword eax,[ebp+16]
    add dword [GlInt],eax
    mov dword eax,[ebp+20]
    mov dword edx,[ebp+24]
    add dword [GlLongLong],eax
    adc dword [GlLongLong+4],edx

    pop ebp
    ret
