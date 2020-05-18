// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

char *pad(char *s, int d) {
    if (!s)
        return NULL;
    char *t = s;
    int i, len = 0;

    while (*t != '\0') {
        t++;
        len++;
    }
    t -= len;
    
    int a = (int)ceil((double)len/d);
    if ((a * d) % 2 == 1)
        a++;
    d *= a;
    char *new = (char *)malloc(sizeof(char) * (d + 1));
    if (new == NULL)
        return NULL;
    for (i = 0; i < d; i++) {
        if (i < len)
            new[i] = s[i];
        else
            new[i] = ' ';
    }
    new[i] = '\0';
    return new;
}
