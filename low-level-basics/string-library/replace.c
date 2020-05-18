// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

/*
char *replace(char *s, char *pat, char *rep){
    size_t i = 0;
    int length_2 = myStrlen(pat);
    int length_3 = myStrlen(rep);
    char *pointer;
    char *pointer_2;
    char result[500];
    for(; *s != '\0'; s++) {
        pointer = s;
        while (*pat != '\0') {
            if (*pat == *s) {
                s++;
                pat++;
            }
            else{
                s = pointer;
                result[i++] = *s;
                break;
            }
        }
        if (*pat == '\0') {
            pat = pointer_2;
            s = pointer;
            if (length_2 >= length_3) {
                while (*pat != '\0') {
                    if(*rep != '\0') {
                        result[i++]=*rep;
                        pat++;
                        rep++;
                        s++;
                    }
                    else {
                        pat++;
                        s++;
                    }
                }
                s--;
            }
            else if (length_3 >= length_2) {
                while(*rep != '\0') {
                    if (*pat != '\0') {
                        result[i++]=*rep;
                        pat++;
                        rep++;
                        s++;
                    }
                    else {
                        result[i++] = *rep;
                        rep++;
                    }
                }
                s--;
            }
        }
    }
    return result;
}
