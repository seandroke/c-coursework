// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int all_letters(char *s){
    int length=myStrlen(s);
    int uppercase=0,lowercase=0;
    int i=0;
    for(i=0;i<length;i++)
    {
        if(s[i]>='a' && s[i]<='z')
            lowercase++;
        else if(!(s[i]>='a' && s[i]<='z'))
            uppercase++;
    }
    if(uppercase==length || lowercase==length)
        return 1;
    else
        return 0;
}
