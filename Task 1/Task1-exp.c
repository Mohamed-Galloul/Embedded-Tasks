#include <stdio.h>
#include <stdlib.h>


void main(){

    float e;
    int n;
    printf("Please enter the exponent and the number of terms you want \n");
    scanf("%f %d", &e, &n);

    float current_term = 1;
    printf("Taylor's expansion for exp(%.2f) for the first %d terms is:\n", e, n);

    for (int i = 1; i <= n; i++)
    {
        printf("%f\t", current_term);
        current_term *= (e/i);
    }
}
