//
//  myStrlen.h
//  lab07_Droke_Sean
//
//  Created by Sean Droke on 10/25/18.
//  Copyright © 2018 Sean Droke. All rights reserved.
//

#ifndef stringLibrary_h_
#define stringLibrary_h_

int myStrlen(char* s);
int all_letters(char *s);
int num_in_range(char *s1, char b, char t);
int diff(char *s1, char *s2);
void shorten(char *s, int new_len);
int len_diff( char s1[], char s2[] );
void rm_left_space( char s[] );
void rm_right_space( char s[] );
void rm_space( char s[] );
int find (char *h, char *n);
char *ptr_to(char *h, char *n);
int is_empty(char *s);
void str_zip(char *s1, char *s2);
void capitalize(char *s);
int strcmp_ign_case (char *s1, char *s2);
void take_last(char *s, int n);
char *dedup(char *s);
char *pad(char *s, int d);
int ends_with_ignore_case(char *s, char *suff);
char *repeat(char *s, int x, char sep);
// char *replace(char *s, char *pat, char *rep);
char *str_connect(char **strs, int n, char c);
void rm_empties(char **words);
// char **str_chop_all(char *s, char c)

#endif
