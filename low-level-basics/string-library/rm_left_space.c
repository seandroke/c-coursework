// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void rm_left_space( char s[] ){
    int blankSpace = 0;
    char* x = s;
    while( *x != '\0' && *x == ' ' ){ x++; blankSpace++; }
    x = s + blankSpace;
    while( *x != '\0' ){
        *s = *x;
        x++; s++;
    }
    *s = '\0';
}
