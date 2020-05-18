// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void rm_space( char s[] ){
    rm_left_space(s);
    rm_right_space(s);
}
