// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int num_in_range(char *s1, char b, char t)
{
    int length=myStrlen(s1);
    
    int range=0;
    int i;
    for(i=0;i<length;i++)
    {
        if(s1[i]>= b && s1[i]<= t)
            range++;
    }
    return range;
}
