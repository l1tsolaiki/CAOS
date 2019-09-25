        .data
str:    .asciz  "%d %d %d\n"
        .text
        .global print_fib
print_fib:
        pushl   %ebp
        movl    %esp, %ebp
        movl    A, %eax
        movl    B, %ecx
        addl    %ecx, %eax
        addl    %eax, %ecx
        movl    %eax, %edx
        addl    %ecx, %edx
        push    %edx
        push    %ecx
        push    %eax
        push    $str
        call    printf
        addl    $16, %esp
        popl    %ebp
        ret
