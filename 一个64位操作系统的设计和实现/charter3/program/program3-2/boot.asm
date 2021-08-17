org 0x7c00

BaseOfStack     equ     0x7c00
BaseOfLoader    equ     0x1000
OffsetOfLoader  equ     0x00

RootDirSectors              equ     14
SectorNumOfRootDirStart     equ     19
SectorNumOfFAT1Start        equ     1
SectorBalance               equ     17

    jmp short   Label_Start
    nop
    BS_OEMNAME          db      'MINEboot'
    BPB_BytesPerSec     dw      512
    BPB_SecPerClus      db      1
    BPB_RsvdSecCnt      dw      1
    BPB_NumFATs         db      2
    BPB_RootEntCnt      dw      224
    BPB_TotSec16        dw      2880
    BPB_Media           db      0xf0
    BPB_FATSz16         dw      9
    BPB_SecPerTrk       dw      18
    BPB_NumHeads        dw      2
    BPB_hiddSec         dd      0
    BPB_TotSec32        dd      0
    BS_DrvNum            db      0
    BS_Reserved1        db      0
    BS_BootSig          db      29h
    BS_VolId            dd      0
    BS_VolLab           db      'boot loader'
    BS_FileSysType      db      'FAT12   '


;=========== read on sector from floppy
Func_ReadOneSector:
    push bp
    mov bp, sp
    sub esp, 2
    mov byte [bp-2], cl ;保存读入的扇区数
    push bx
    mov bl, [BPB_SecPerTrk]
    div bl
    inc ah
    mov cl, ah  ;扇区号
    mov dh, al
    shr al, 1
    mov ch, al  ;磁道号
    and dh, 1   ;磁头号
    pop bx
    mov dl, [BS_DrvNum] ;驱动器号

Label_Go_On_Reading:
    mov ah, 2   ;13h功能号
    mov al, byte [bp-2] ;读入的扇区数
    int 13h
    jc Label_Go_On_Reading

    add esp, 2
    pop bp
    ret

;======== search loader.bin
