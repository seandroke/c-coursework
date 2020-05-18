// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int myStrlen(char* s){
    int i=0;
    int length=0;
    while(s[i]!='\0')
    {length++;
        i++;
    }
    return length;
}
