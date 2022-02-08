#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "communicator.h"
#include "logic.h"

void determineRole();

/**
 * Variable for the application status
 */
int run = 1;

/**
 * Variable for the role of the instance
 */
char role = 'c';

/**
 * Constant for the char definition of the host role
 */
const char hostRole = 'h';

/**
 * Constant for the sign definition of the host
 */
const char hostSign = 'X';

/**
 * Constant for the char definition of the client role
 */
const char clientRole = 'c';

/**
 * Constant for the sign definition of the client
 */
const char clientSign = 'O';

/**
 * Variable for the current playground
 */
char playground[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

/**
 * Program entry point
 * 
 * return int
 */
int main()
{
    
    // determine the user input and than which role to use
    determineRole();
    if (role == hostRole)
    {
        // start the server behaviour
        server();
    }
    else
    {
        // start the client behaviour
        client();
        printPlayground(playground);
        setSign(clientSign);
    }

    // block the main thread so the process won't finish too early
    while(run){};
    


    return 0;
}

/**
 * Determine which connection peer to act as
 * 
 * return void
 */
void determineRole()
{
    printf("Willkommen bie Tic Tac Toe. Bitte wähle eine Rolle: (h)ost oder (c)lient:\n");
    scanf("%c", &role);

    if ((role == hostRole) && (role == clientRole))
    {
        printf("Error: '%c' is not a valid role", role);
        exit(1);
    }
}