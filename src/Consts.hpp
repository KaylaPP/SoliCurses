#ifndef CONSTS_H
# define CONSTS_H

static const char vals[15] = " A23456789TJQK"; // All possible values of a card
static const char suits[5] = "cdhs";           // All possible suits of a card
static const char piles[12][3] =               // Pile names
{"DS", "F1", "F2", "F3", "F4", "P1", "P2", "P3", "P4", "P5", "P6", "P7"};
static int drawtype;             // An int representing the draw type of the game (1 or 3)
static const int pilelens[12] =  // The lengths of each pile in GB
{25, 14, 14, 14, 14, 20, 20, 20, 20, 20, 20, 20};

#endif