#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main (int argc, char const *argv[]) {
    int num;
    double denominator = 7;
    double sum = 0;
    bool point = false;
    bool end = false;

    while ((num = getchar()) != EOF) {
        if (isspace(num)) {
            if (end == false) {
                printf("%.10g\n", sum);
                sum = 0;
                point = false;
                denominator = 7;
                end = true;
            }
        } else {
            end = false;
            if (num == '.') {
                point = true;
            } else {
                if (point == false) {
                    sum *= 7;
                    sum += num - (int)'0';
                } else {
                    sum += (num - (int)'0') * (1 / denominator);
                    denominator *= 7;
                }
            }
        }
    }
    return 0;
}
