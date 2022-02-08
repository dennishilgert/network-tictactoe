#ifndef LOGIC_H
#define LOGIC_H

void printPlayground(char playground[9]);
int checkForDraw(char playground[9]);
int checkForWinner(char playground[9], char player);
void setSign(char sign);
void updateGamestate(char buffer[1024], char sign);
int analysePlayground();

#endif