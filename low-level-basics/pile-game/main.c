// Sean Droke
// November 15, 2018
// CIS 2107
// Lab 10

#include <stdio.h>
#include <string.h>

#define NEXT_PLAYER(x) ((x % 2) + 1)
#define PILE_INIT 0
#define ITEMS_TO_TAKE 1
#define CHOOSE_PILE 2
#define NONE 0
#define POSITIVE 1
#define POSITIVE_FOR_PILE 0
#define MAX_ITEMS_FOR_TURN 3
#define FIRST_PILE 'A'
#define SECOND_PILE 'B'
#define THIRD_PILE 'C'
#define TRUE 1
#define FALSE 0
#define FIRST_PLAYER 1

int gFirstPile;
int gSecondPile;
int gThirdPile;
char player1[20];
char player2[20];
int gCurrentPlayer = FIRST_PLAYER;

char * identifyPlayer(int gCurrentPlayer)
{
    char *ptr1 = player1;
    char *ptr2 = player2;
    if (gCurrentPlayer == 1)
    {
        return ptr1;
    }
    else
    {
        return ptr2;
    }
}

int verifyInput(int inputType, int inputToVerify, int pile)
{
    if (inputType == PILE_INIT)
    {
        if (inputToVerify < POSITIVE_FOR_PILE)
        {
            printf("Pile must be positive.\n");
            return TRUE;
        }
    }
    else if (inputType == CHOOSE_PILE)
    {
        if (inputToVerify != FIRST_PILE && inputToVerify != SECOND_PILE && inputToVerify != THIRD_PILE)
        {
            return TRUE;
        }
        else if (inputToVerify > POSITIVE_FOR_PILE && inputToVerify == FIRST_PILE && gFirstPile == 0)
        {
            printf("Nice try %s, That pile is empty. \n", identifyPlayer(gCurrentPlayer));
            return TRUE;
        }
        else if (inputToVerify > POSITIVE_FOR_PILE && inputToVerify == SECOND_PILE && gSecondPile == 0)
        {
            printf("Nice try %s, That pile is empty. \n", identifyPlayer(gCurrentPlayer));
            return TRUE;
        }
        else if (inputToVerify > POSITIVE_FOR_PILE && inputToVerify == THIRD_PILE && gThirdPile == 0)
         {
         printf("Nice try %s, That pile is empty. \n", identifyPlayer(gCurrentPlayer));
         return TRUE;
         }
        
    }
    else if (inputType == ITEMS_TO_TAKE)
    {
        if (inputToVerify < POSITIVE)
        {
            printf("You must choose at least 1.\n");
            return TRUE;
        }
        else if (inputToVerify > MAX_ITEMS_FOR_TURN)
        {
            printf("Cannot take more than 3 at a time.\n");
            return TRUE;
        }
        else if (inputToVerify > pile)
        {
            printf("Pile doesn't have that many.\n");
            return TRUE;
        }
    }
    return FALSE;
}

void printItems(int itemsNumber)
{
    int items;
    for (items = 0; items < itemsNumber; ++items)
    {
        printf("*");
    }
}

void printPiles()
{
    printf("---------------\n");
    printf("A: ");
    printItems(gFirstPile);
    printf("\nB: ");
    printItems(gSecondPile);
    printf("\nC: ");
    printItems(gThirdPile);
    printf("\n---------------\n");
}

void pileChooser(int pileNumber)
{
    if (pileNumber == FIRST_PILE)
    {
        scanf("%i", &gFirstPile);
    }
    else if (pileNumber == SECOND_PILE)
    {
        scanf("%i", &gSecondPile);
    }
    else if (pileNumber == THIRD_PILE)
    {
        scanf("%i", &gThirdPile);
    }
}

int pileInit()
{
    int pile;
    char temp = 'A';
    for (pile = FIRST_PILE; pile <= THIRD_PILE; ++pile)
    {
        printf("How many in pile %c?\n", temp);
        temp++;
        pileChooser(pile);
        if (verifyInput(PILE_INIT, gFirstPile, NONE))
        {
            return TRUE;
        }
    }
    return FALSE;
}

char choosePile(int playerNumber)
{
    printf("%s, it's your turn.\n", identifyPlayer(playerNumber));
    printf("%s, choose a pile (A, B, or C):\n", identifyPlayer(playerNumber));
    char choice;
    getchar();
    scanf("%c", &choice);
    while (verifyInput(CHOOSE_PILE, choice, NONE))
    {
        printf("%s, it's your turn.\n", identifyPlayer(playerNumber));
        printf("%s, choose a pile (A, B, or C):\n", identifyPlayer(playerNumber));
        getchar();
        scanf("%c", &choice);
    }
    return choice;
}

int takeItems(int itemsInChosenPile, char pileNumber)
{
    printf("%s, how many do you want to take from pile %c?\n", identifyPlayer(gCurrentPlayer),
           pileNumber);
    int numOfItems;
    scanf("%i", &numOfItems);
    while (verifyInput(ITEMS_TO_TAKE, numOfItems, itemsInChosenPile))
    {
        printf("%s, how many do you want to take from pile %c?\n", identifyPlayer(gCurrentPlayer),
               pileNumber);
        scanf("%i", &numOfItems);
    }
    return (itemsInChosenPile - numOfItems);
}

void playerTurn(int playerNumber)
{
    char chosenPile = choosePile(playerNumber);
    if (chosenPile == FIRST_PILE)
    {
        gFirstPile = takeItems(gFirstPile, FIRST_PILE);
    }
    else if (chosenPile == SECOND_PILE)
    {
        gSecondPile = takeItems(gSecondPile, SECOND_PILE);
    }
    else if (chosenPile == THIRD_PILE)
    {
        gThirdPile = takeItems(gThirdPile, THIRD_PILE);
    }
    gCurrentPlayer = NEXT_PLAYER(gCurrentPlayer);
}

void playGame()
{
    int temp_final = 0;
    while (temp_final != 1)
    {
        if(gFirstPile != 0 || gSecondPile != 0 || gThirdPile != 0)
        {
            if(gFirstPile == 0 && gSecondPile == 0 && gThirdPile == 1)
            {
                gCurrentPlayer = NEXT_PLAYER(gCurrentPlayer);
                temp_final = 1;
            }
            else if(gFirstPile == 0 && gSecondPile == 1 && gThirdPile == 0)
            {
                gCurrentPlayer = NEXT_PLAYER(gCurrentPlayer);
                temp_final = 1;
            }
            else if(gFirstPile == 1 && gSecondPile == 0 && gThirdPile == 0)
            {
                gCurrentPlayer = NEXT_PLAYER(gCurrentPlayer);
                temp_final = 1;
            }
            else
            {
                playerTurn(gCurrentPlayer);
                printPiles();
            }
        }
        else
        {
            temp_final = 1;
        }
    }
}

void getPlayerNames()
{
    printf("Player 1, enter your name: ");
    scanf("%s", player1);
    printf("Player 2, enter your name: ");
    scanf("%s", player2);
}

int main()
{
    getPlayerNames();
    if (pileInit())
    {
        return TRUE;
    }
    printPiles();
    playGame();
    printf("%s wins the game.\n", identifyPlayer(gCurrentPlayer));
    return NONE;
}

