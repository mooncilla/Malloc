#include "malloc.h"

int roundUp(int numToRound)
{
    if (ALLIGN == 0)
        return numToRound;

    int remainder = numToRound % ALLIGN;
    if (remainder == 0)
        return numToRound;

    return numToRound + ALLIGN - remainder;
}

int         main()
{
    printf("%d\n", sizeof(t_malloc));
}
