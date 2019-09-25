        .text
        .global satsum
satsum:
        pushl   %ebp
        movl    %esp, %ebp
        movl    8(%ebp), %eax
        addl    12(%ebp), %eax
        jc      overflow
        movl    %ebp, %esp
        popl    %ebp
        ret
overflow:
        movl    $0xffffffff, %eax
        movl    %ebp, %esp
        popl    %ebp
        ret
