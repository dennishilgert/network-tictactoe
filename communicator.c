#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "communicator.h"
#include "main.h"

/**
 * Variable for the ip address
 */ 
char ip[16];

/**
 * Constant for the port
 */ 
const int port = 5566;

/**
 * Variables for the server and client socket
 */ 
int server_sock, client_sock;

/**
 * Variables for the server and client address
 */ 
struct sockaddr_in server_addr, client_addr;

/**
 * Variable for the address size
 */ 
socklen_t addr_size;

/**
 * Variable for the buffer
 */ 
char buffer[1024];

int getSocket();
void socketListener();
void *serverListener();
void *clientListener();

/**
 * Enable the behaviour as a server peer
 * 
 * return void
 */
void server()
{
    printf("Info: Starting server behaviour\n");
    printf("Info: Please enter ip to host the game server on (default 127.0.0.1):\n");
    scanf("%s", ip);

    // create the server socket and check if the creation was successful
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        printf("Error: Cannot create server socket (%d)\n", server_sock);
        exit(1);
    }
    printf("Info: Server socket created\n");

    // define the server address to bind the socket to
    memset(&server_addr, '\n', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // bind the socket to the socket address and check if the binding was successful
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error: Cannot bind server socket to %s:%d\n", ip, port);
        exit(1);
    }
    printf("Info: Server socket bound to address\n");

    // listen for incoming connections
    listen(server_sock, 5);
    printf("Info: Server socket listening on %s:%d\n", ip, port);

    socketListener();
}

/**
 * Enable the behaviour as a client peer
 * 
 * return void
 */
void client()
{
    printf("Info: Starting client behaviour\n");
    printf("Info: Please enter the host ip of the game server:\n");
    scanf("%s", ip);

    // create the client socket and check if the creation was successful
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0)
    {
        printf("Error: Cannot create client socket (%d)\n", client_sock);
        exit(1);
    }
    printf("Info: Client socket created\n");

    // define the server address to connect to
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // connect to the server and check if the connection was established successfully
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error: Cannot connect to the server\n");
        exit(1);
    }
    printf("Info: Connected to the server\n");

    // send hello message
    sendData("hello");

    socketListener();
}

/**
 * Creates a new thread to listen for incoming data
 * 
 * return void
 */
void socketListener()
{
    pthread_t threadId;
    if (role == hostRole)
    {
        pthread_create(&threadId, NULL, serverListener, NULL);
    }
    else
    {
        pthread_create(&threadId, NULL, clientListener, NULL);
    }
}

/**
 * Lister of the server side to be executed in a new thread
 * 
 * args void *parameter
 * return void
 */
void *serverListener(void *parameter)
{
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("Info: Client connected\n");

    while (run == 1)
    {
        bzero(&buffer, 1024);
        int n = recv(client_sock, buffer, sizeof(buffer), 0);
        if (n == 0)
        {
            run = 0;
            printf("Info: Connection to the client closed - Shutting down");
            exit(0);
        }
        printf("Info: Message received '%s'\n", buffer);
    }
    return 0;
}

/**
 * Lister of the client side to be executed in a new thread
 * 
 * args void *parameter
 * return void
 */
void *clientListener(void *parameter)
{
    int socket = getSocket();

    while (run == 1)
    {
        bzero(&buffer, 1024);
        int n = recv(socket, buffer, sizeof(buffer), 0);
        if (n == 0)
        {
            run = 0;
            printf("Info: Connection to the server closed - Shutting down");
            exit(0);
        }
        printf("Info: Message received '%s'\n", buffer);
    }
    return 0;
}

/**
 * Listener for the user input to be sent to the other connection peer
 * 
 * return void
 */
void inputListener()
{
    char input[100];
    while (run == 1)
    {
        scanf("%s", input);
        sendData(input);
    }
}

/**
 * Getter for the active socket 
 * 
 * return int
 */
int getSocket()
{
    return client_sock;
}

/**
 * Send data to the other connection peer
 * 
 * args char data[]
 * return void
 */
void sendData(char data[])
{
    char buffer[1024];
    bzero(&buffer, 1024);
    strcpy(buffer, data);
    if (send(getSocket(), buffer, strlen(buffer), 0) < 0)
    {
        printf("Error: Cannot send data");
    }
}