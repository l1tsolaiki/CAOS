        .text
        .global main
main:
while:
        call    readi32
        jc      eof
        testl   $1, %eax
        jnz     odd
        addl    %eax, %ebx
        jmp     while
eof:
        movl    %ebx, %eax
        call    writei32
        call    nl
        movl    %edi, %eax
        call    writei32
        call    nl
        call    finish
odd:
        addl    %eax, %edi
        jmp     while
