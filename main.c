#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "communicator.h"
#include "logic.h"

void determineRole();

int run = 1;
char role = 'c';
char hostRole = 'h';
char clientRole = 'c';

/**
 * Program entry point
 * 
 * return int
 */
int main()
{
    char playground[9] = {'X', 'X', 'X', '4', '5', '6', '7', '8', '9'};

    printPlayground(playground);
    int winner = checkForWinner(playground, 'X');
    printf("Winner? %d", winner);

    // determine the user input and than which role to use
    determineRole();
    if (role == hostRole)
    {
        server();
    }
    else
    {
        client();
    }

    inputListener();

    return 0;
}

/**
 * Determine which connection peer to act as
 * 
 * return void
 */
void determineRole()
{
    printf("Info: Welcome to the game. Please choose your role (h)ost or (c)lient:\n");
    scanf("%c", &role);

    if ((role == hostRole) && (role == clientRole))
    {
        printf("Error: '%c' is not a valid role", role);
        exit(1);
    }
}