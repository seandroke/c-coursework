// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

char *ptr_to(char *h, char *n){
    for(int i=0;i<h[i]!='\0';i++){
        int match=1;
        int prev_i = i;
        for(int j = 0; n[j]!='\0';j++){
            if(h[prev_i]!='\0' && h[prev_i]==n[j]){
                prev_i++;
                continue;
            }
            else{
                match = 0;
                break;
            }
        }
        if(match==1){
            return h+i;
        }
    }
    return NULL;
}
