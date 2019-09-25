#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    unsigned int num, sum = 0;
    while (scanf("%x", &num) != EOF) {
        while (scanf("%x", &num) != '\n') {
            // for (size_t i = 3; i >= 0; --i) {
                // sum += num * 16;
            // }
            printf("%x\n", sum);
            sum = 0;
        }
    }
    return 0;
}
/*
000000 3c 3f 78 6d 6c 20 76 65 72 73 69 6f 6e 3d 22 31
000010 2e 30 22 20 65 6e
*/
