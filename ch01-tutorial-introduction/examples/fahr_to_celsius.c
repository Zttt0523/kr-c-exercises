#include <stdio.h>

int main(void)
{
    int fahr, celsius;
    int lower, upper, step;

    // lower limit of temperature scale
    lower = 0;
    // upper limit of temperature scale
    upper = 300;
    //  step size
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = 5 * (fahr-32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
