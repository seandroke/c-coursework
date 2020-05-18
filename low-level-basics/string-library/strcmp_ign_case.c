// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int strcmp_ign_case (char *s1, char *s2) {
    unsigned char *p1 = (unsigned char *)s1;
    unsigned char *p2 = (unsigned char *)s2;
    
    while (*p1 != '\0') {
        if (*p2 == '\0') return  1;
        if (*p2 > *p1)   return -1;
        if (*p1 > *p2)   return  1;
        
        p1++;
        p2++;
    }
    
    if (*p2 != '\0') return -1;
    
    return 0;
}
