#include <stdio.h>
#include <math.h>

float z1(float m, float n) {
    return \
    ((m-1)*sqrt(m) - (n-1)*sqrt(n)) \
    / \
    (sqrt(pow(m, 3)*n) + n*m + pow(m, 2) - m);
}

float z2(float m, float n) {
    return (sqrt(m) - sqrt(n)) / m;
}

int main() {

    float ms[] = {4, -2, 10, 6, 2}, 
          ns[] = {1, 7, 0, 2, 12};

    printf("Results:\n");
    for (int i=0; i < sizeof(ms)/sizeof(ms[0]); i++) {
        printf(
            "m =%10f| n =%10f| z1 =%10f| z2 =%10f|\n", 
            ms[i], ns[i], 
            z1(ms[i], ns[i]), 
            z2(ms[i], ns[i])
        );
    }

    return 0;
}