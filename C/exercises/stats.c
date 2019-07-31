/*
   Read a sequence of real numbers and report the minimum, maximum
   and average values.
 */
#include <stdio.h>
#include <stdlib.h>

int main( void )
{
    // Figure out how many values there are.
    int n;
    scanf("%d", &n);

    // Read in the first value into val.
    double val;
    scanf("%lf", &val);

    // That first value is our tentative min and max value.
    double minValue = val, maxValue = val, total = val;

    // Get the remaining n-1 values and update minValue, maxValue and total
    // based on each one.
    for (int i = 1; i < n; i++) {
        scanf("%lf", &val);
        if (val > maxValue) {
            maxValue = val;
        }
        if (val < minValue) {
            minValue = val;
        }
        total += val;
    }
    // Report the stats.
    printf("%s%8.2lf\n", "Minimum: ", minValue);
    printf("%s%8.2lf\n", "Maximum: ", maxValue);
    printf("%s%8.2lf", "Average: ", total / n);

    // Exit successfully.
    return 0;
}