// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void rm_empties(char **words)
{
    int i=0, j, k, len, p = 0;
    
    while(words[i] != NULL)
    {
        len = 0;
        for(j=0; words[i][j] != '\0'; j++)
            len++;
        if(len == 0)
        {
            k = i;
            while(words[k+1] != NULL)
            {
                words[k] = words[k+1];
                k++;
            }
            p++;
        }
        else
            i++;
    }
    words[(i-p)] = NULL;
}

