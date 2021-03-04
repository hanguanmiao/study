#extern "C" MmxVal MmxAdd_(MmxVal a, MmxVal b, MmxAddOp op);
.section .data
#AddOpTable:
#    .long MmxPaddb,MmxPaddsb,MmxPaddusb,MmxPaddw,MmxPaddsw,MmxPaddusw,MmxPaddd
#    AddOpTableCount = .-AddOpTable
#.equ AddOpTableCount,($ - AddOpTable)/4
AddOpTable:
    .equ MmxPaddb,0
    .equ MmxPaddsb,1
    .equ MmxPaddusb,2
    .equ MmxPaddw,3
    .equ MmxPaddsw,4
    .equ MmxPaddusw,5
    .equ MmxPaddd,6
    AddOpTableCount = (.-AddOpTable)/4

.section .text
.globl MmxAdd_

.type MmxAdd_,@function
MmxAdd_:
    pushl %ebp
    movl %esp,%ebp

    movl 24(%ebp),%eax
    cmpl AddOpTableCount,%eax
    jae BadAddOp


BadAddOp:
    pxor %mm0,%mm0

SaveResult:
    movd %mm0,%eax
#    pshufw %mm2,%mm0,$01001110b
    movd %mm2,%eax
