// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void shorten(char *s, int new_len){
    int length=myStrlen(s);
    if(length<=new_len)
        printf("string is unchanged");
    else{int i;
        for(i=new_len;i<length;i++)
            s[i]='\0';
        
    }
    printf("\nResult of shorten: %s\n", s);
}
