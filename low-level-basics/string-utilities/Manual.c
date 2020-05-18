// Sean Droke
// CIS 2107
// October 11, 2018
// Lab 06

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void upperLower();
void convertStrtoInt();
void convertStrtoFloat();
void compareStr();
void comparePartialStr();
void randomize();
void tokenizeTelNum();
void reverse();
void countSubstr();
void countChar();
void countAlpha();
void countWords();
// void startsWithB
// void endsWithED

int main(void)
{
  upperLower();
  convertStrtoInt();
  convertStrtoFloat();
  compareStr();
  comparePartialStr();
  randomize();
  tokenizeTelNum();
  reverse();
  countSubstr();
  countChar();
  countAlpha();
  countWords();
 // startsWithB();
 // endsWithed();

  return(0);
}

void upperLower()
{
  char s[100] = {"this is the sentence"};

  printf("%s", "Upper Case: ");
  for(int u = 0; u < 100; u++)
  {
    if (islower(s[u]))
      printf("%c", toupper(s[u]));
    else
      printf("%c", s[u]);
  }

  printf("%s", "\nLower Case: ");
  for(int l = 0; l < 100; l++)
  {
    if (isupper(s[l]))
      printf("%c", tolower(s[l]));
    else
      printf("%c", s[l]);
  }
  puts("");
}

void convertStrtoInt(){
  char string1[10] = {"23"};
  char string2[10] = {"240"};
  char string3[10] = {"2"};
  char string4[10] = {"68"};


  int sum = strtol(string1, NULL, 10) + strtol(string2, NULL, 10) + strtol(string3, NULL, 10) + strtol(string4, NULL, 10);
  printf("\nSum of Strings = %d", sum);
  puts("");
}


void convertStrtoFloat(){
  char string1[10] = {"2.67"};
  char string2[10] = {"12.56"};
  char string3[10] = {"14.7"};
  char string4[10] = {"56.76"};

  double sum = strtod(string1, NULL) + strtod(string2, NULL) + strtod(string3, NULL) + strtod(string4, NULL);
  printf("\nSum of Strings (As Floats) = %.2f", sum);
  puts("");
}

void compareStr(){
  char string1[20] = {"12345"};
  char string2[20] = {"1234"};

  int compare = strcmp(string1, string2);

  if (compare == 0)
    puts("\nThe strings are the same");
  else if (compare < 0)
    puts("\nString 1 is less than string 2");
  else
    puts("\nString 1 is greater than String 2");
}

void comparePartialStr(){
  int compare = 3;
  char string1[21] = {"3456"};
  char string2[21] = {"3467"};

  for(int i = compare; i < 20; i++)
  {
    string1[i] = 0;
    string2[i] = 0;
  }

  int difference = strcmp(string1, string2);

  if (difference == 0)
    puts("\nThe strings are the same\n");
  else if (difference < 0)
    puts("\nString 1 is less than String 2\n");
  else
    puts("\nString 1 is larger than String 2\n");
}

void randomize()
{
  const char *article[] = {"the", "a", "one", "some", "any"};
  const char *noun[] = {"boy", "girl", "dog", "town", "car"};
  const char *verb[] = {"drove", "jumped", "ran", "walked", "skipped"};
  const char *preposition[] = {"to", "from", "over", "under", "on"};

  for(int k = 0; k < 20; k++)
  {
    const char *firstWord = article[rand()%5];

    const char *sentence[] = {firstWord, article[rand()%5], noun[rand()%5], verb[rand()%5], preposition[rand()%5], article[rand()%5], noun[rand()%5]};

    for(int i = 0; i < 5; i++)
    {
      printf("%s ", sentence[i]);
    }
    printf("%s.\n", sentence[5]);
  }
}


void tokenizeTelNum()
{

  char string[] = "(856) 504-1234";

  char tel[10];

  int areaCode = strtol(strtok(string,"()"), NULL, 10);

  strcpy(tel, strtok(NULL, "-"));
  strcat(tel, strtok(NULL, "-"));
  long phoneNum = strtol(tel, NULL, 10);

  printf("\nArea Code: %d\n", areaCode);
  printf("Phone Number: %ld\n\n", phoneNum);
}

void reverse()
{
  char string[] = "This is a string to be reversed";
  char *sentence[7] = {"0"};
  sentence[0] = strtok(string, " ");
  for(int i = 1; i < 7; i++)
  {
    sentence[i] = strtok(NULL, " ");
  }
  for(int k = 6; k >= 0; k--)
  {
    printf("%s ", sentence[k]);
  }
  puts("");
}

void countSubstr(){
  char search[] = "is";
  char line1[] = "This is the first line of text";
  char line2[] = "This is the second line of text, with more words";
  char line3[] = "This is the third line of text with less";

  int oneCounter = 0;
  int twoCounter = 0;
  int fourCounter = 0;

  for(int i = 0; i < strlen(line1); i++)
  {
    if(strstr(&line1[i], search) != NULL)
    {
      int remainingC = strlen(strstr(&line1[i], search));

      if(strlen(&line1[i]) > remainingC)
      {
        oneCounter++;
        i = strlen(line1) - remainingC;
      }
    }
    else
      continue;
  }

  for(int i = 0; i < strlen(line2); i++)
  {
    if(strstr(&line2[i], search) != NULL)
    {
      int remainingC = strlen(strstr(&line2[i], search));

      if(strlen(&line2[i]) > remainingC)
      {
        twoCounter++;
        i = strlen(line2) - remainingC;
      }
    }
    else
      continue;
  }

  for(int i = 0; i < strlen(line3); i++)
  {
    if(strstr(&line3[i], search) != NULL)
    {
      int remainingC = strlen(strstr(&line3[i], search));

      if(strlen(&line3[i]) > remainingC)
      {
        fourCounter++;
        i = strlen(line3) - remainingC;
      }
    }
    else
      continue;
  }

  printf("\nLine one has %d\nLine two has %d\nLine three has %d\n", oneCounter, twoCounter, fourCounter);
}

void countChar()
{
  char search = 's';

    char line1[] = "This is the first line of text";
    char line2[] = "This is the second line of text, with more words";
    char line3[] = "This is the third line of text with less";

  int oneCounter = 0;
  int twoCounter = 0;
  int fourCounter = 0;

  for(int i = 0; i < strlen(line1); i++)
  {
    if(strchr(&line1[i], search) != NULL)
    {
      int remainingC = strlen(strchr(&line1[i], search));

      if(strlen(&line1[i]) > remainingC)
      {
        oneCounter++;
        i = strlen(line1) - remainingC;
      }
    }
    else
      continue;
  }

  for(int i = 0; i < strlen(line2); i++)
  {
    if(strchr(&line2[i], search) != NULL)
    {
      int remainingC = strlen(strchr(&line2[i], search));

      if(strlen(&line2[i]) > remainingC)
      {
        twoCounter++;
        i = strlen(line2) - remainingC;
      }
    }
    else
      continue;
  }

  for(int i = 0; i < strlen(line3); i++)
  {
    if(strchr(&line3[i], search) != NULL)
    {
      int remainingC = strlen(strchr(&line3[i], search));

      if(strlen(&line3[i]) > remainingC)
      {
        fourCounter++;
        i = strlen(line3) - remainingC;
      }
    }
    else
      continue;
  }

  printf("\nLine one has %d\nLine two has %d\nLine three has %d\n", oneCounter, twoCounter, fourCounter);
}

void countAlpha()
{
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  int numbers[26] = {0};

    char line1[] = "This is the first line of text";
    char line2[] = "This is the second line of text, with more words";
    char line3[] = "This is the third line of text with less";

  for(int o = 0; o < strlen(line1); o++)
  {
    for(int i = 0; i < 26; i++)
    {
      if(line1[o] == alphabet[i])
        numbers[i]++;
    }
  }
  for(int t = 0; t < strlen(line2); t++)
  {
    for(int i = 0; i < 26; i++)
    {
      if(line2[t] == alphabet[i])
        numbers[i]++;
    }
  }
  for(int f = 0; f < strlen(line3); f++)
  {
    for(int i = 0; i < 26; i++)
    {
      if(line1[f] == alphabet[i])
        numbers[i]++;
    }
  }

  puts("\nCharacter Count");

  for(int j = 0; j < 26; j++)
  {
    printf(" %c \t%d\n", alphabet[j], numbers[j]);
  }
}

void countWords()
{
  int wordTotal = 0;

    char line1[] = "This is the first line of text";
    char line2[] = "This is the second line of text, with more words";
    char line3[] = "This is the third line of text with less";

  char *tokenPtr = strtok(line1, " \n");
  while (tokenPtr != NULL)
  {
    wordTotal++;
    tokenPtr = strtok(NULL, " \n");
  }

  tokenPtr = strtok(line2, " \n");
  while (tokenPtr != NULL)
  {
    wordTotal++;
    tokenPtr = strtok(NULL, " \n");
  }
  tokenPtr = strtok(line3, " \n");
  while (tokenPtr != NULL)
  {
    wordTotal++;
    tokenPtr = strtok(NULL, " \n");
  }

  printf("\nThe total number of words is %d\n", wordTotal);
}

