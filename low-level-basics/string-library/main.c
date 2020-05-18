// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stringLibrary.h"

int main() {
    char string_1[] = "Hello";
    printf("Result all_letters: %d\n", all_letters(string_1));
    
    char string_2[] = "This is a test of this function";
    char a = 'a';
    char b = 'c';
    printf("\nResult num_in_range: %d\n", num_in_range(string_2, a, b));
    
    char string_3[] = "Differ";
    char string_4[] = "Difference";
    printf("\nResult diff: %d\n", diff(string_3, string_4));
    
    char string_5[] = "This is the string we want to shorten";
    int length = 10;
    shorten(string_5, length);
    
    char string_6[] = "This is the longer string";
    char string_7[] = "This is shorter";
    printf("\nResult len_diff: %d\n", len_diff(string_6, string_7));
    
    char string_8[] = "      Remove Space";
    rm_left_space(string_8);
    printf("\nResult rm_left_space: %s\n", string_8);
    
    char string_9[] = "Remove Space     ";
    rm_right_space(string_9);
    printf("\nResult rm_right_space: %s\n", string_9);
    
    char string_10[] = "        Remove Space        ";
    rm_space(string_10);
    printf("\nResult rm_space: %s\n", string_10);
    
    char string_11[] = "Orange";
    char test[] = "r";
    printf("Result of find: %d\n", find(string_11, test));
    
    char string_12[] = "string of words";
    char string_13[] = "string";
    char *matchdPtr = ptr_to(string_12,string_13);
    printf("\nResult of ptr_to: %s\n",matchdPtr);
    
    char string_14[] = "        ";
    printf("\nResult of is_empty: %d\n", is_empty(string_14));
    
    char string_15[] = "FirstString";
    char string_16[] = "SecondString";
    str_zip(string_15, string_16);
    printf("\nResults of str_zip: %s\n", string_15);
    
    char string_17[] = "every letter capitalized";
    capitalize(string_17);
    printf("\nResult of capitalize: %s\n", string_17);
    
    char a2[] = "a";
    char b2[] = "b";
    printf("\nResult of strcmp_ign_case: %d\n", strcmp_ign_case(a2, b2));
    
    char string_18[] = "Brubeck";
    int n = 5;
    take_last(string_18, n);
    printf("\nResult of take_last: %s\n", string_18);
    
    char string_19[] = "There's always money in the banana stand.";
    printf("\nResult of dedup: %s\n", dedup(string_19));
    
    char string_20[] = "This is going to be a test of this function pad";
    int number = 7;
    printf("\nResult of pad: %s\n", pad(string_20, number));
    
    char string_21[] = "Testing";
    char string_22[] = "ing";
    printf("\nResult of ends_with_ignore_case: %d\n", ends_with_ignore_case(string_21, string_22));
    
    char string_23[] = "all right";
    int x = 3;
    char string_24 = ',';
    printf("\nResult of repeat: %s\n", repeat(string_23, x, string_24));
    

    char *stringptr[] = { "Test", "This", "Function" };
    char *res;
    res = str_connect(stringptr, 3, '-');
    printf("\nResult of str_connect: %s \n", res);
    
    char *string_25[] = { "Testing", "" ,"This", "" , "" , "Function", NULL };
    rm_empties(string_25);
    int var = 0;
    printf("\nResult of rm_empties: ");
    while(string_25[var] != NULL)
    {
        printf("%s\t", string_25[var]);
        var++;
    }
    printf("\n\n");
    
    //replace and str_chop_all left out, unable to complete.
    
}

