// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int find(char *h, char *n){
    for(int i=0;i<h[i]!='\0';i++){
        int match=1;
        int i2 = i;
        
        for(int j = 0; n[j]!='\0';j++){
            if(h[i2]!='\0' && h[i2]==n[j]){
                i2++;
                continue;
            }
            else{
                match = 0;
                break;
            }
        }
        if(match==1){
            return i;
        }
    }
    return -1;
}
