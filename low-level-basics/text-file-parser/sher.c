// Sean Droke
// December 09, 2018
// CIS 2107
// Lab 11

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OUTPUT 1000000
#define DEFAULT 10000

int parser(FILE *fp, char* dest);
void getDialogue(FILE *fp, char* dest);
void makeDialogueSouthie(char* string, char* dest);
void makeWordSouthie(char* string, int i);
int isVowel(char c);


int main() {
    FILE *Ptr1;
    FILE *Ptr2;
    char output[OUTPUT];
    char temp[DEFAULT];
    char southieDialogue[DEFAULT];
    
    if ((Ptr1 = fopen("sherlock.txt", "r")) == NULL) {
        puts("File can not be opened.");
    }
    else {
        while (parser(Ptr1, temp)) {
            strcat(output, temp);
            getDialogue(Ptr1, temp);
            makeDialogueSouthie(temp, southieDialogue);
            strcat(output, southieDialogue);
        }
        if ((Ptr2 = fopen("southie-sherlock.txt", "w")) == NULL) {
            puts("File can not be opened.");
        }
        else {
            fprintf(Ptr2, "%s", output);
        }
    }
}

int parser(FILE *sh, char* destination) {
    int i = 0;
    char ch;
    while((ch = fgetc(sh)) != EOF && ch != '"'){
        destination[i] = ch;
        ++i;
    }
    if (ch == EOF) {
        return 0;
    }
    destination[i] = ch;
    destination[++i] = '\0';
    return 1;
}

void getDialogue(FILE *sh, char* destination) {
    char ch;
    int i;
    for (i = 0; EOF != (ch = fgetc(sh)); ++i) {
        if (ch == '"') break;
        destination[i] = ch;
    }
    destination[i] = '"';
    destination[++i] = '\0';
}

void makeDialogueSouthie(char* string, char* destination) {
    char buffer[DEFAULT];
    char word[50];
    int i = 0;
    int j = 0;
    int k = 0;
    
    while (k < strlen(string)) {
        i = 0;
        while (!isblank(string[k]) && string[k] != '\0') {
            word[i] = string[k];
            ++i;
            ++k;
        }
        word[i] = '\0';
        i = 0;
        while (word[i] != '\0') {
            makeWordSouthie(word, i);
            ++i;
        }
        strncpy(&buffer[j], word, i);
        j += i;
        buffer[j++] = ' ';
        ++k;
    }
    buffer[j] = '\0';
    strcpy(destination, buffer);
}

void makeWordSouthie(char* str, int i) {
    if ((!strcmp(str, "very"))) {
        strcpy(str, "wicked");
    }
    else if (i!= 0 && str[i] == 'r' && isVowel(str[i - 1])) {
        if ((strlen(str) - 1 == i || ispunct(str[i+1])) && ((i >= 2 && str[i - 1] == 'e' && str[i - 2] == 'e') || str[i - 1] == 'i')) {
            if (ispunct(str[i + 1])) {
                char temp = str[i + 1];
                str[i] = 'y';
                str[i + 1] = 'a';
                str[i + 2] = 'h';
                str[i + 3] = temp;
                str[i + 4] = '\0';
            }
            else {
                str[i] = 'y';
                str[i + 1] = 'a';
                str[i + 2] = 'h';
                str[i + 3] = '\0';
            }
        }
        else if ((strlen(str) - 1 == i  || ispunct(str[i + 1]))&& i >= 2 && str[i - 1] == 'o' && str[i - 2] == 'o') {
            if (ispunct(str[i + 1])) {
                char temp = str[i + 1];
                str[i] = 'w';
                str[i + 1] = 'a';
                str[i + 2] = 'h';
                str[i + 3] = temp;
                str[i + 4] = '\0';
            }
            else {
                str[i] = 'w';
                str[i + 1] = 'a';
                str[i + 2] = 'h';
                str[i + 3] = '\0';
            }
            
        }
        else {
            str[i] = 'h';
        }
    }
    else if (i!= 0 && (strlen(str) -1 == i || ispunct(str[i + 1])) && str[i] == 'a') {
        if (ispunct(str[i + 1])) {
            char temp = str[i + 1];
            str[i + 1] = 'r';
            str[i + 1] = temp;
            str[i + 2] = '\0';
        }
        else {
            str[i + 1] = 'r';
            str[i + 2] = '\0';
        }
    }
}

int isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return 1;
    }
    else {
        return 0;
    }
}
