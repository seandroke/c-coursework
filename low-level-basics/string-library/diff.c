// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int diff(char *s1, char *s2){
    int length_1=myStrlen(s1);
    int length_2=myStrlen(s2);
    int diffr=0;
    int i;
    if(length_1==length_2){
        for(i=0;i<length_1;i++){
            if(s1[i]!=s2[i])
                diffr++;
        }
    }
    else if(length_1 > length_2){
        for(i=0;i<length_2;i++){
            if(s1[i]!=s2[i])
                diffr++;
        }
        diffr=diffr+length_1-length_2;
    }
    else{
        for(i=0;i<length_1;i++){
            if(s1[i]!=s2[i])
                diffr++;
        }
        diffr=diffr+length_2-length_1;
    }
    return diffr;
}
