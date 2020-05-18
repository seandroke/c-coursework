//  Sean Droke
//  September 13, 2018
//  CIS 2107
//  lab2_droke_sean


#include <stdio.h>
int attempts = 0;
int attempts2 = 0;
int attempts3 = 0;
int balance(void);
int balanceamount = 5000;
int transaction = 0;
int menu(void);
int selection = 0;
int acceptence = 0;
int withdraw(void);
int deposit(void);
int limitwithdraw = 0;
int limitdeposit = 0;
int recipts = 0;

int main(void)
{
    int pin;
    printf("Welcome to the Temple University ATM.\n");
    printf("Please enter your 4 digit pin\n");
    scanf("%d", &pin);
    
    while (attempts <= 1) {
        if (pin == 3014) {
            while(acceptence == 0) {
                selection = menu();
                if (selection == 1) {
                    printf("Your balance is: $%d\n\n", balance());
                }
                if (selection == 2) {
                    if (limitwithdraw < 1000) {
                        printf("Thanks, your remaining balance is: $%d\n", withdraw());
                    }
                    else {
                        printf("Your withdraw limit has been met\n");
                    }
                }
                if (selection == 3) {
                    if (limitdeposit < 10000) {
                        printf("Thanks, your remaining balance is: $%d\n", deposit());
                    }
                    else {
                        printf("Your deposit limit has been reached.\n");
                    }
                }
                if (selection == 4) {
                    printf("Thank you, you have made %d transactions.\n", transaction);
                    if (recipts == 0){
                        printf("Chose 1 to print your recipt, or 2 if you do not wish to have a recipt:\n");
                        scanf("%d", &recipts);
                        printf("Goodbye!\n");
                    }
                    else {
                        printf("Your recipt has been printed, goodbye!\n");
                    }
                    acceptence = 1;
                    return 0;
                }
                if (selection < 0) {
                    printf("You have entered an incorrect menu option, try again.\n");
                }
                if (selection > 4) {
                    printf("You have entered an incorrect menu option, try again.\n");
                }
            }
    
            }
        
        else {
            attempts++;
            printf("Your response was invalid! Please try again.\n\n");
            main();
    }
    
        if (attempts == 1) {
            break;
        }
    }
    }

int menu(void) {
    int selection;
    printf("How can we help you today?\n\n");
    printf("1. Check the balance of your account.\n");
    printf("2. Complete a cash withdraw.\n");
    printf("3. Complete a cash deposit.\n");
    printf("4. Exit your account. \n\n");
    scanf("%d", &selection);

    return selection;
}

int balance(void) {
    transaction++;
    return balanceamount;
}

int withdraw(void) {
    int amountw;
    printf("How much would you like to withdraw today?\n\n");
    scanf("%d", &amountw);
    if (attempts2 >= 3) {
        main();
    }
    if (amountw <= 0) {
        printf("Pease enter a number greater than or equal to 0, in multiples of $20\n");
        attempts2++;
        withdraw();
    }
    if (amountw > 1000) {
        printf("Error above your withdraw limit\n");
        attempts2++;
        withdraw();
    }
    if (amountw % 20 == 0 && amountw > 0 && amountw < 1000 && limitwithdraw +amountw < 1000) {
        balanceamount = balanceamount - amountw;
        transaction++;
        recipts = 1;
        limitwithdraw = limitwithdraw + amountw;
    }
    if (amountw % 20 != 0) {
        printf("Pease enter a number greater than or equal to 0, in multiples of $20\n");
        attempts2++;
        withdraw();
    }
        return balanceamount;
    }


int deposit(void) {
    int amountd;
    printf("How much would you like to deposit today?\n\n");
    scanf("%d", &amountd);
    
    if (attempts3 >= 3){
        main();
    }
    if (amountd > 10000) {
        printf("Error above your deposit limit\n");
        attempts3++;
        deposit();
    }
    if (amountd % 1 == 0 && amountd > 0 && amountd < 10000 && amountd + limitdeposit < 10000) {
        balanceamount = balanceamount + amountd;
        transaction++;
        recipts = 1;
        limitdeposit = limitdeposit + amountd;
    }
    else {
        printf("Your deposit limit has been reached or you entered an invalid input\n");
        attempts3++;
        menu();
    }
    return balanceamount;
}




