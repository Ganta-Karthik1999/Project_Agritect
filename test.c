#include<stdio.h>
#include<stdlib.h>


int main() {
    int *a = malloc(sizeof(int));
    if (a == NULL) {
        perror("malloc");
        return 1;
    }

    a[0] = 10;
    a[1] = 20; // This is an out-of-bounds write, but let's ignore it for this test
    printf("Value of a: %d\n", a[0]);
    printf("Value of a[1]: %d\n", a[1]); // This may cause undefined behavior

    // free(a);
    return 0;
}