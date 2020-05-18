// Sean Droke
// CIS 2107
// October 12, 2018
// Lab 07 - String Library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int myStrlen(char* s){
    int i=0;
    int length=0;
    while(s[i]!='\0')
    {length++;
        i++;
    }
    return length;
}

int all_letters(char *s){
    int len=myStrlen(s);
    int uppercase=0,lowercase=0;
    int i=0;
    for(i=0;i<len;i++)
    {
        if(s[i]>='a' && s[i]<='z')
            lowercase++;
        else if(!(s[i]>='a' && s[i]<='z'))
            uppercase++;
    }
    if(uppercase==len || lowercase==len)
        return 1;
    else
        return 0;
}

int num_in_range(char *s1, char b, char t){
    int len=myStrlen(s1);
    
    int range=0;
    int i;
    for(i=0;i<len;i++)
    {
        if(s1[i]>='b' && s1[i]<='t')
            range++;
    }
    return range;
}

int diff(char *s1, char *s2){
    int len1=myStrlen(s1);
    int len2=myStrlen(s2);
    int diffr=0;
    int i;
    if(len1==len2){
        for(i=0;i<len1;i++){
            if(s1[i]!=s2[i])
                diffr++;
        }
    }
    else if(len1 > len2){
        for(i=0;i<len2;i++){
            if(s1[i]!=s2[i])
                diffr++;
        }
        diffr=diffr+len1-len2;
    }
    else{
        for(i=0;i<len1;i++){
            if(s1[i]!=s2[i])
                diffr++;
        }
        diffr=diffr+len2-len1;
    }
    return diffr;
}

void shorten(char *s, int new_len){
    int len=myStrlen(s);
    if(len<=new_len)
        printf("string is unchanged");
    else{int i; //else
        for(i=new_len;i<len;i++)
            s[i]='\0';
        
    }
}

int len_diff( char s1[], char s2[] ){
    int l1 = 0;
    char* c = s1;
    while( *c != '\0' ){
        l1++;
        c++;
    }
    int l2 = 0;
    c = s2;
    while( *c != '\0' ){
        l2++;
        c++;
    }
    return l1-l2;
}

void rm_left_space( char s[] ){
    int blankSpaceEndAt = 0;
    char* c = s;
    while( *c != '\0' && *c == ' ' ){ c++; blankSpaceEndAt++; }
    c = s + blankSpaceEndAt;
    while( *c != '\0' ){
        *s = *c;
        c++; s++;
    }
    *s = '\0';
}

void rm_right_space( char s[] ){
    char* c = s;
    while( *c != '\0' ){ c++; }
    c--;
    while( *c == ' ' ){ c--;}
    c++;
    *c = '\0';
}

void rm_space( char s[] ){
    rm_left_space(s);
    rm_right_space(s);
}

int find (char *h, char *n) {
    int i = 0;
    while (h[i]) {
        if (h[i] == *n) {
            return i;
        }
        i++;
    }
    return -1;
}

char *ptr_to(char *h, char *n) {
    for (;; h++) {
        if (*h == *n) return h;
        if (!*h) return NULL;
    }
    return NULL;
}

int is_empty(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
        return 0;
    }
    return 1; }

void str_zip(char *s1, char *s2)
{
    while(*s1)
        s1++;
    
    while(*s2)
    {
        *s1 = *s2;
        s2++;
        s1++;
    }
    *s1 = '\0';
}

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
    printf("String Capitalized Is: %s", s);
        }

int strcmp_ign_case (char *s1, char *s2) {
    unsigned char *p1 = (unsigned char *)s1;
    unsigned char *p2 = (unsigned char *)s2;
    
    while (*p1 != '\0') {
        if (*p2 == '\0') return  1;
        if (*p2 > *p1)   return -1;
        if (*p1 > *p2)   return  1;
        
        p1++;
        p2++;
    }
    
    if (*p2 != '\0') return -1;
    
    return 0;
}

void take_last(char *s, int n) {
    if (!s) // if string is empty, simply return.
        return;
    char *t = s;
    int i, j, len = 0;
    while (*t != '\0') { // find out the string length
        t++;
        len++;
    }
    if (len < n) // if string length less than n, then no need to truncate the string.
        return;
    for (i = 0, j = n; i < n; i++, j--)
        s[i] = s[len - j];
    s[i] = '\0';
}

char *dedup(char *s) {
    if (!s) // If string is empty, return NULL
        return NULL;
    char *t = s;
    char used[256];
    int i, j, len = 0;
    
    // Get length
    while (*t != '\0') {
        t++;
        len++;
    }
    t -= len;
    
    if (len < 2)
        return s;
    
    // Array of used chars
    for (i = 0; i < 256; i++)
        used[i] = 0;
    
    char *new = (char *)malloc(sizeof(char) * len);
    if (new == NULL)
        return NULL;
    
    for (i = 0, j = 0; i < len; i++) {
        if (!used[s[i]]) { // Check if character has been used
            new[j++] = s[i];
            used[s[i]] = !0;
        }
    }
    new[j] = '\0';
    return new;
}

char *pad(char *s, int d) {
    if (!s) // if string is empty, return NULL
        return NULL;
    char *t = s;
    int i, len = 0;
    
    // Get length
    while (*t != '\0') {
        t++;
        len++;
    }
    t -= len;
    
    int a = (int)ceil((double)len/d);
    if ((a * d) % 2 == 1)
        a++;
    d *= a;
    char *new = (char *)malloc(sizeof(char) * (d + 1));
    if (new == NULL) // if memory is not allocated, then return NULL
        return NULL;
    for (i = 0; i < d; i++) {
        if (i < len)
            new[i] = s[i];
        else
            new[i] = ' ';
    }
    new[i] = '\0';
    return new;
}



int main() {
    char string_1[] = "A";
    char string_2[] = "B";
    printf("%d", strcmp_ign_case(string_1, string_2));
}






