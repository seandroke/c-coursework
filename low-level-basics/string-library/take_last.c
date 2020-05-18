// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void take_last(char *s, int n) {
    if (!s)
        return;
    char *t = s;
    int i, j, len = 0;
    while (*t != '\0') {
        t++;
        len++;
    }
    if (len < n)
        return;
    for (i = 0, j = n; i < n; i++, j--)
        s[i] = s[len - j];
    s[i] = '\0';
    printf("%s", s);
}
