//Sean Droke
// September 20, 2018
// CIS 2107
//lab3_droke_sean

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand(void);

void fillArray(int array[], int size) {
    
    int i;
    for(i=0; i<size;i++) {
        int c = rand() % 100 + 1;
            array[i]=c;
    }
}

void printArray(int array[], int size){
    int i;
    int arrayposition = 1;
    for(i=0;i<size;i++) {
        if (arrayposition % 10 != 0){
            printf("%d\t",array[i]);
            arrayposition++;
        }
        else {
            printf("%d\n",array[i]);
            arrayposition++;
        }
    }
}

int findWithRange(int array[], int lowrange, int highrange) {
    int i;
    int c = -1;
    for(i=lowrange; i<=highrange;i++) {
        if (array[i] > c) {
            c = array[i];
        }
    }
    return c;
}

void reverseArray(int array[], int size, int low, int high)
{
    int temp;
    if(high>low && 0<=low<=size && 0<=high<=size){
    while (low < high)
    {
        temp = array[low];
        array[low] = array[high];
        array[high] = temp;
        low++;
        high--;
    }
}
}

int findSequence(int array[], int size, int num1, int num2) {
    int i;
    for(i=0; i < size; i++) {
        if(array[i] == num1 && array[i+1] == num2){
            return i;
        }
    }
    return -1;
}


int main(void) {
    int array[40];
    int num1;
    int num2;
    int lowrange;
    int highrange;
    int low;
    int high;
    int a;
    printf("Array: \n");
    fillArray(array,40);
    printArray(array,40);
    printf("\nEnter Range of Index Values to Find Max: ");
    scanf("%d %d", &lowrange, &highrange);
    printf("\nMax = %d\n", findWithRange(array, lowrange, highrange));
    reverseArray(array,40, 0, 39);
    printf("\nArray Reversed:\n");
    printArray(array,40);
    printf("\nEnter Two Numbers LOW and HIGH as the index range to be reversed: ");
    scanf("%d %d",&low, &high);
    reverseArray(array,40, low,high);
    printArray(array, 40);
    printf("\nEnter Two Numbers to search for sequence: ");
    scanf("%d %d",&num1, &num2);
    a = findSequence(array, 40, num1, num2);
    if(a != -1){
        printf("sequence found at index ");
    }
    else {
        printf("sequence not found\n");
    }
    printf("%d\n", findSequence(array, 40, num1, num2));
    
}


