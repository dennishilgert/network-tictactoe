#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic.h"
#include "main.h"
#include "communicator.h"

/**
 * Constant for the winning states
 */
const char winStates[8][9] = {
    {'A', 'A', 'A', '4', '5', '6', '7', '8', '9'},
    {'1', '2', '3', 'A', 'A', 'A', '7', '8', '9'},
    {'1', '2', '3', '4', '5', '6', 'A', 'A', 'A'},
    {'A', '2', '3', 'A', '5', '6', 'A', '8', '9'},
    {'1', 'A', '3', '4', 'A', '6', '7', 'A', '9'},
    {'1', '2', 'A', '4', '5', 'A', '7', '8', 'A'},
    {'A', '2', '3', '4', 'A', '6', '7', '8', 'A'},
    {'1', '2', 'A', '4', 'A', '6', 'A', '8', '9'}};

/**
 * Print row with signs in specific colors
 *
 * return void
 */
void colorSign(char sign) {
    printf("        "); 
    if (sign == hostSign) {
        printf(TEXT_BOLD SIGN_COLOR_HOST "%c" ANSI_COLOR_RESET TEXT_RESET, sign);
    } else if (sign == clientSign) {
        printf(TEXT_BOLD SIGN_COLOR_CLIENT "%c" ANSI_COLOR_RESET TEXT_RESET, sign);
    } else {
        printf("%c", sign);
    }
    printf("        ");
}

/**
 * Print a given playground to the console
 *
 * args char playground[9]
 * return void
 */
void printPlayground(char playground[9])
{
    system("clear");

    for (int i = 0; i < 7; i = i + 3) {
        printf("                 |                 |                 \n");
        colorSign(playground[i]);
        printf("|");
        colorSign(playground[i + 1]);
        printf("|");
        colorSign(playground[i + 2]);
        printf("\n");
        printf("                 |                 |                 \n");
        if (i < 6) {
            printf("-----------------+-----------------+-----------------\n");
        }
    }
}

/**
 * Check if the current playground matches a draw
 *
 * args char playground[9]
 * return int
 */
int checkForDraw(char playground[9]) {
    int draw = 1;
    for (int i = 0; i < 9; i++) {
        if ((playground[i] != hostSign) && (playground[i] != clientSign)) {
            draw = 0;
        }
    }
    if (draw == 1) {
        printf("\nUnentschieden!\n");
    }
    return draw;
}

/**
 * Check if there is a winner
 *
 * args char playground[9], char player
 * return int
 */
int checkForWinner(char playground[9], char sign)
{
    for (int i = 0; i < 8; i++)
    {
        int matchCounter = 0;
        for (int j = 0; j < 9; j++)
        {
            char gameField = playground[j];
            char winField = winStates[i][j];
            if ((winField == 'A') && (gameField == sign))
            {
                matchCounter++;
            }
        }
        if (matchCounter == 3)
        {
            
            if ((sign == hostSign) && (role == hostRole)) {
                printf(TEXT_BOLD ANSI_COLOR_GREEN "Du hast gewonnen!\n" ANSI_COLOR_RESET TEXT_RESET);
            } else {
                if (role == hostRole) {
                    printf("\n" ANSI_COLOR_RED "Spieler " TEXT_BOLD SIGN_COLOR_CLIENT "%c" ANSI_COLOR_RESET TEXT_RESET ANSI_COLOR_RED " hat gewonnen.\n", sign);
                } else {
                    printf("\n" ANSI_COLOR_RED "Spieler " TEXT_BOLD SIGN_COLOR_HOST "%c" ANSI_COLOR_RESET TEXT_RESET ANSI_COLOR_RED " hat gewonnen.\n", sign);
                }
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Update the playground with the received one
 *
 * args char newPlayground[9]
 * return void
 */
void updatePlayground(char newPlayground[9])
{
    for (int i = 0; i < 9; i++) {
        playground[i] = newPlayground[i];
    }
    printPlayground(playground);
}

/**
 * Handle the move an a player
 *
 * args char sign
 * return void
 */
void setSign(char sign)
{
    int fieldNumber = 1;
    int askForNumber = 1;

    printf("Bitte gib die Ziffer des Feldes ein: ");
    do
    {
        scanf("%i", &fieldNumber);
        if ((playground[fieldNumber - 1] == hostSign) || (playground[fieldNumber - 1] == clientSign)) {
            printf("Bitte freies Feld angeben: ");
        } else {
            askForNumber = 0;
        }
    } while (askForNumber == 1);
    
    playground[fieldNumber-1] = sign;
    printPlayground(playground);

    printf("Eingabe erfolgreich!\n");

    sendData(playground);

    if (analysePlayground() == 1) {
        run = 0;
        return;
    }

    printf("Bitte warte auf den anderen Spieler ...\n");
}

/**
 * Check if the opponent made a game finishing move
 *
 * args char buffer[1024], char sign
 * return void
 */
void updateGamestate(char buffer[1024], char sign) {
    updatePlayground(buffer);
    if (analysePlayground() == 1) {
        run = 0;
        return;
    }
    setSign(sign);
}

/**
 * Determine if the playground contains a finishing state
 *
 * return int
 */
int analysePlayground() {
    int result = 0;
    if (checkForDraw(playground) == 1) {
        result = 1;
    } else {
        if (checkForWinner(playground, hostSign) == 1) {
            result = 1;
        } else if (checkForWinner(playground, clientSign) == 1) {
            result = 1;
        }
    }
    return result;
}