// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

char *str_connect(char **strs, int n, char c)
{
    char *str;
    int i, j, k, len = 0;
    for(i=0; i<n; i++)
    {
        for(j=0; strs[i][j] != '\0'; j++)
            len++;
    }
    str = (char*) malloc(sizeof(char)*(len+n+1));
    k=0;
    for(i=0; i<n; i++)
    {
        for(j=0; strs[i][j] != '\0'; j++)
        {
            str[k] = strs[i][j];
            k++;
        }
        if(i < n-1)
        {
            str[k] = c;
            k++;
        }
    }
    str[k] = '\0';
    return str;
}
