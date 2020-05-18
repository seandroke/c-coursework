// Sean Droke
// September 20, 2018
// CIS 2107
// lab5_droke_sean
// race.c

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define FINISHLINE 70

void moveTortoise(int* tortoisePointer );
void moveHare(int* harePointer );
void printPosition(const int* const tortoisePointer, const int* const harePointer);

int main(void) {

    puts ("ON YOUR MARK, GET SET");
    puts("BANG                !!!!");
    puts("AND THEY'RE OFF     !!!!");
   
    int tortoisePosition = 1;
    int harePosition = 1;
    
    while(tortoisePosition != FINISHLINE && harePosition != FINISHLINE){
      moveTortoise( &tortoisePosition );
      moveHare( &harePosition );
      printPosition( &tortoisePosition, &harePosition );
}
    if(tortoisePosition > harePosition){
      printf("TORTOISE WINS!!! YAY!!!\n");
   }
    else {
      printf("Hare wins. Yuch.\n");
   }
    return 0;
}

void moveHare(int* harePointer){
   int i;

   i = 1+rand() %10;
   if(i >= 1 && i <= 2){
      *harePointer = *harePointer;
   }
   else if(i >= 3 && i <= 4){
      *harePointer += 9;
   }
   else if(i == 5){
      *harePointer -= 12;
   }
   else if(i >= 6 && i<= 8){
      *harePointer += 1;
   }
   else{
      *harePointer -= 2;
   }
   if(*harePointer < 1)
      *harePointer = 1;
   
   else if(*harePointer > FINISHLINE)
      *harePointer = FINISHLINE;
}

void moveTortoise(int* tortoisePointer){
   int i;
    
   i = 1 +rand() % 10;
   if(i >= 1 && i <= 5){
      *tortoisePointer += 3;
   }else if(i >= 6 && i <= 7){
      *tortoisePointer -= 6;
   }else{
      *tortoisePointer += 1;
   }
   if(*tortoisePointer < 1){
      *tortoisePointer = 1;
   }
   else if(*tortoisePointer > FINISHLINE){
      *tortoisePointer = FINISHLINE;
   }
}
void printPosition(const int* const tortoisePointer, const int* const harePointer){
   int i;
    
   if(*tortoisePointer == *harePointer){
      for(i = 1; i < *tortoisePointer; i++){
         printf("%s", " " );
      }
      sleep(1);
      printf("OUCH!!!");    
      
   }
   else if(*tortoisePointer < *harePointer){
      for(i = 1; i < *tortoisePointer; i++ ){
         printf("%s", " " );
      }   
      sleep(1);
      printf("T");
       
      for(i = 1; i < (*harePointer - *tortoisePointer); i++){
         printf("%s", " " );
      }
      sleep(1);
      printf("H");
   }
   else{
      for(i = 1; i < *harePointer; i++){
         printf("%s", " ");      
      }  
      sleep(1);
      printf("H");
       
      for( i = 0; i < (*tortoisePointer - *harePointer); i++){
         printf("%s", " " );     
      }
      sleep(1);
      printf("T");
   }
    
   puts("");
}
