//Sean Droke
// September 20, 2018
// CIS 2107
//lab4_droke_sean

#include <stdio.h>

void minimum(int students, int exams, int studentGrades[students][exams])
{
    int lowGrade = 100;
    size_t i, j;
    for (i = 0; i < students; ++i) {
        for (j = 0; j < exams; ++j) {
            if (studentGrades[i][j] < lowGrade) {
                lowGrade = studentGrades[i][j];
            }
        }
    }
    printf("Minimum grade : %d\n\n", lowGrade);
    return;
}

void maximum(int students, int exams, int studentGrades[students][exams])
{
    int highGrade = 0;
    size_t i, j;
    for (i = 0; i < students; ++i) {
        for (j = 0; j < exams; ++j) {
            if (studentGrades[i][j] > highGrade) {
                highGrade = studentGrades[i][j];
            }
        }
    }
    printf("Maximum grade : %d\n\n", highGrade);
    return;
}

void average(int students, int exams, int studentGrades[students][exams])
{
    double total = 0.0; // sum of test grades
    size_t i, j;
    for (i = 0; i < students; ++i) {
        for (j = 0; j < exams; ++j) {
            total += studentGrades[i][j];
        }
        printf ("Average of student %lu : %f\n", i, total / exams);
        total = 0;
    }
    printf("\n");
    return;
}

void printArray(int students, int exams, int studentGrades[students][exams])
{
    size_t i, j;
    int c;
    printf("\t\t  ");
    for(c = 0; c < exams; c++) {
        printf("[%d]  ", c);
    }
    for (i = 0; i < students; ++i) {
        printf("\nStudent[%lu] ", i);
        for (j = 0; j < exams; ++j) {
            printf("%-5d", studentGrades[i][j]);
        }
    }
    printf("\n\n");
    return;
}

int main(void)
{
    int choice;
    int students;
    int exams;
    printf("Let's create a 2Dim array!\n\n");
    printf("How many students? ");
    scanf("%d", &students);
    printf("\nHow many exams? ");
    scanf("%d", &exams);
    printf("\n");
    int studentGrades[students][exams];
    int i;
    int j;
    int entry;
    for (i = 0; i < students; i++){
        for (j=0; j < exams; j++) {
            printf("enter [%d] [%d]: ", i,j);
            scanf("%d",&entry);
            studentGrades[i][j] = entry;
        }
    }
    void (*processGrades[4]) (int, int, int[][exams]);
    processGrades[0] = printArray;
    processGrades[1] = minimum;
    processGrades[2] = maximum;
    processGrades[3] = average;
    int stop = 0;
    while(stop != 1) {
    printf("Enter a choice:\n");
    printf("0 Print the array of grades\n");
    printf("1 Find the minimum grade\n");
    printf("2 Find the maximum grade\n");
    printf("3 Print the average on all tests for each student\n");
    printf("4 End Program\n");
    scanf("%d", &choice);
        if(choice == 4){
            stop = 1;
        }
        else{
        (*processGrades[choice])(students,exams,studentGrades);
    }
}
}
