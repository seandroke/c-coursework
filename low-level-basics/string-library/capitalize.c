// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

void capitalize(char *s) {
    int i;
    
    for(i = 0; s[i] != '\0'; i++) {
        if (i == 0) {
            if ((s[i] >= 'a' && s[i] <= 'z'))
                s[i] = s[i] - 32;
            continue;
        }
        if (s[i] == ' ') {
            ++i;
            if (s[i] >= 'a' && s[i] <= 'z') {
                s[i] = s[i] - 32;
                continue;
            }
        }
        else {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] + 32;
        }
    }
}
