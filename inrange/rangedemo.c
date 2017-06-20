#include <stdio.h>
#include <stdlib.h>

#define RUTILS_INRANGE_IMPL
#include "inrange.h"

int main(void) {
    int value, in_range;
    RANGE(age_range, 1, 120);
    RANGE(valid_range, 0, 200);

    /* Input a value to check */
    printf("\nValue to check: ");
    scanf("%d", &value);

    /* Check if in range */
    in_range = rutils_isinranges(value, 1, age_range, valid_range);
    if (in_range)
        printf("\nValue %d is in range!\n", value);
    else
        printf("\nValue is not in range!\n");

    return 0;
}
