// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

char *repeat(char *s, int x, char sep) {
    if(s){
        int i, count = 0;
        
        while(s[count] != '\0'){
            ++count;
        }
        
        char *newArray = malloc(count * x + 1);
        if(newArray){
            char *na = newArray;
            for(i = 0; i < x; ++i) {
                const char *p=s;
                char *x = &sep;
                while(*p)
                    *na++ = *p++;
                *na++ = *x;
            }
            *na = '\0';
        }
        return newArray;
    } else {
        return NULL;
    }
}
