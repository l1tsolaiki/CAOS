        .text
        .global forward.args
forward.args:
        pushl   %ebp
        movl    %esp, %ebp

        pushl   %eax
        pushl   %eax
        pushl   %eax
        movl    8(%ebp), %eax
        pushl   %eax
        movl    $0, %eax
        pushl   %eax
        movl    16(%ebp), %eax
        pushl   %eax
        movl    20(%ebp), %ecx
        call    process
        xorl    %edx, %edx

        movl    %ebp, %esp
        popl    %ebp
        ret
