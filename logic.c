#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic.h"
#include "main.h"

char winStates[8][9] = {
    {'A', 'A', 'A', '4', '5', '6', '7', '8', '9'},
    {'1', '2', '3', 'A', 'A', 'A', '7', '8', '9'},
    {'1', '2', '3', '4', '5', '6', 'A', 'A', 'A'},
    {'A', '2', '3', 'A', '5', '6', 'A', '8', '9'},
    {'1', 'A', '3', '4', 'A', '6', '7', 'A', '9'},
    {'1', '2', 'A', '4', '5', 'A', '7', '8', 'A'},
    {'A', '2', '3', '4', 'A', '6', '7', '8', 'A'},
    {'1', '2', 'A', '4', 'A', '6', 'A', '8', '9'}};

void printPlayground(char playground[9])
{
    printf("                 |                 |                 \n        %c        |        %c        |        %c        \n                 |                 |                 \n", playground[0], playground[1], playground[2]);
    printf("-----------------+-----------------+-----------------\n");
    printf("                 |                 |                 \n        %c        |        %c        |        %c        \n                 |                 |                 \n", playground[3], playground[4], playground[5]);
    printf("-----------------+-----------------+-----------------\n");
    printf("                 |                 |                 \n        %c        |        %c        |        %c        \n                 |                 |                 \n", playground[6], playground[7], playground[8]);
}

int checkForWinner(char playground[9], char player)
{
    for (int i = 0; i < 8; i++)
    {
        int matchCounter = 0;
        for (int j = 0; j < 9; j++)
        {
            char gameField = playground[j];
            char winField = winStates[i][j];
            if ((winField == 'A') && (gameField == player))
            {
                matchCounter++;
            }
        }
        if (matchCounter == 3)
        {
            return 1;
        }
    }
    return 0;
}