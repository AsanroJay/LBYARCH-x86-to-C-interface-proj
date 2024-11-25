section .data
sdot dq 0
section .text
bits 64
default rel
global scalarmul


scalarmul:
    ;n (rcx), arr1 [rdx], arr2[r8], ptr [r9
    xorps xmm0, xmm0

computationloop:
    cmp rcx,0
    je end
    mov eax,[rdx]
    cvtsi2ss xmm1,eax
    mov eax,[r8]
    cvtsi2ss xmm2,eax

    mulss xmm1,xmm2 
    addss xmm0,xmm1 ;add prev scalar product to new scalar product
    movss [sdot],xmm0 ;move result to sdot

    dec rcx
    add rdx,4
    add r8,4
    jmp computationloop

end:
    movss xmm0,[sdot]
    movss [r9],xmm0
