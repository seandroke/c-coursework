// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int ends_with_ignore_case(char *s, char *suff)
{
    char *temp = suff;
    int count = 0;
    while(*(count + temp) != '\0')
        count++;
    int StringCount = 0;
    while(*(StringCount + s) != '\0')
        StringCount++;
    for(int i = count - 1; i >= 0; i--)
        if(*(s + --StringCount) != *(suff + i))
            return 0;
    return 1;
}
