gcc -m32 FILE.S -c -g

bash
gcc -m32 prog.S -o prog

gcc -m32 prog.S simpleio_x86.S -o prog
gcc -m32 prog.S -nostdlib -o prog

simpleio_x86_64.S
