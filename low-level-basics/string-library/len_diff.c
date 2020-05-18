// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int len_diff( char s1[], char s2[] ){
    int l1 = 0;
    char* x = s1;
    while( *x != '\0' ){
        l1++;
        x++;
    }
    int l2 = 0;
    x = s2;
    while( *x != '\0' ){
        l2++;
        x++;
    }
    return l1-l2;
}
