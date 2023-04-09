#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits>

#define NOT_PLUS false
#define PLUS true
#define NOT_CHOOSE false
#define CHOOSE true
#define INIT_STONES 4
#define P1_WELL 0
#define P2_WELL 1
#define SIDE_LENGTH 6
#define P1_START (P2_WELL + 1) 
#define P1_END (P1_START + SIDE_LENGTH - 1) 
#define P2_START (P1_END + 1) 
#define P2_END (P2_START + SIDE_LENGTH - 1) 

using namespace std;

void displayBoard(int*);
void populateBoard(int*);
void displayWinner(int*);

void vanilla(bool);
void chooseAny(bool);
void playMancala(bool, bool);

bool updateBoard(int*, int, bool); //bool only for + versions

#endif // UTILS_H