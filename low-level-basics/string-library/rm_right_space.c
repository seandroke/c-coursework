// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void rm_right_space( char s[] ){
    char* x = s;
    while( *x != '\0' ){ x++; }
    x--;
    while( *x == ' ' ){ x--;}
    x++;
    *x = '\0';
}
