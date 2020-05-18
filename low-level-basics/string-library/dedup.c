// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

char *dedup(char *s) {
    if (!s)
        return NULL;
    char *t = s;
    char used[256];
    int i, j, len = 0;

    while (*t != '\0') {
        t++;
        len++;
    }
    t -= len;
    
    if (len < 2)
        return s;
    
    for (i = 0; i < 256; i++)
        used[i] = 0;
    
    char *new = (char *)malloc(sizeof(char) * len);
    if (new == NULL)
        return NULL;
    
    for (i = 0, j = 0; i < len; i++) {
        if (!used[s[i]]) {
            new[j++] = s[i];
            used[s[i]] = !0;
        }
    }
    new[j] = '\0';
    return new;
}
