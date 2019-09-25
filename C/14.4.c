#include <stdio.h>

int main(int argc, char const *argv[]) {
    unsigned long long size = 0;
    unsigned int vm_start, vm_end;

    while (scanf("%x-%x%*[^\n]", &vm_start, &vm_end) != EOF) {
        size += vm_end - vm_start;
    }
    printf("%llu\n", size);
    return 0;
}
