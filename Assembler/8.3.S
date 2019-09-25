        .text
        .global main
main:
        call    readi32
        movl    %eax, %ebx
while:
        cmpl    $0, %eax
        jl      then
        call    writei32
        call    nl
        decl    %ebx
        movl    %ebx, %eax
        jmp     while
then:
        call    finish
