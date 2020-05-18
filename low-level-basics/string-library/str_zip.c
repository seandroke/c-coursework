// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void str_zip(char *s1, char *s2)
{
    while(*s1)
        s1++;
    
    while(*s2)
    {
        *s1 = *s2;
        s2++;
        s1++;
    }
    *s1 = '\0';
}
