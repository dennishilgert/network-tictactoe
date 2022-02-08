#ifndef MAIN_H
#define MAIN_H

/**
 * Variable for the while-loops
 */ 
extern int run;

/**
 * Variable for the current role
 */ 
extern char role;

/**
 * Constant for the host role
 */ 
extern const char hostRole;

/**
 * Constant for the host sign
 */ 
extern const char hostSign;

/**
 * Constant for the client role
 */ 
extern const char clientRole;

/**
 * Constant for the client sign
 */ 
extern const char clientSign;

/**
 * Variable for the current playground
 */
extern char playground[9];

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define TEXT_BOLD          "\033[1m"
#define TEXT_RESET         "\033[0m"

#define SIGN_COLOR_HOST ANSI_COLOR_BLUE
#define SIGN_COLOR_CLIENT ANSI_COLOR_YELLOW

#endif