#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    uint32_t num;

    while (scanf("%u", &num) != EOF) {
        int tmp = 0;
        // int checker = 31;
        int degree = 6;
        int start = 0;
        for (int i = 31; i >= 0; --i) {
            // for (int i = 31; i >= 0; --i) {
            //     tmp += ((num >> i) & 1)
            // printf("%u", (num >> i) & 1);
            tmp += ((num >> i) & 1) * pow(2, degree);
            --degree;
            if (i % 7 == 0) {
                degree = 7;
                if (tmp) {
                    start = 1;
                    printf("%x ", tmp);
                }
                if (start && tmp) {
                    tmp += pow(2, 7);
                    printf("%x ", tmp);
                }
                tmp = 0;
            }
            // --checker;
	    }
        // printf("%d\n", tmp);
        // int a = 10000001;
        // printf("%x\n", a);
    }
    return 0;
}
// 0000 0000000 0000000 0000001 0000010
