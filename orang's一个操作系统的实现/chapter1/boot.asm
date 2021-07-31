    org 7c00h       ; 告诉编译器程序加载到7c00h处
    mov ax, cs
    mov ds, ax
    mov es, ax
    call DispStr
    jmp $       ; 无限循环

DispStr:
    mov ax, BootMessage
    mov bp, ax
    mov cx, 16
    mov ax, 1301h
    mov bx, 0ch
    mov dl, 0
    int 10h
    ret

BootMessage: db "Hello, Os world!"
times 510-($-$$) db 0
dw 0xaa55
