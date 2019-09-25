        .data
        .global A, B, C, D, R
A:      .int    0
B:      .int    0
C:      .int    0
D:      .int    0
R:      .int    0

        .text
        .global process
process:
        movl    C, %eax
        movl    D, %ebx
        imull   %ebx
        movl    %eax, %esi
        movl    A, %eax
        movl    B, %ebx
        imull   %ebx
        subl    %esi, %eax
        movl    %eax, R
        ret
