        .text
        .global main
main:
        call    readi32
        mov     %eax, %esi
        call    readi32
        addl    %esi, %eax
        call    writei32
        call    nl
        call    finish
