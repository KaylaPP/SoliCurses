#include <cstdlib>
#include "Consts.h"

#ifndef CARD_H
# define CARD_H

class Card
{
private:
    int val;
    char suit;
    bool revealed;
    bool placeholder;
public:
    Card(); // Placeholder constructor
    Card(int v, char s, bool r); // v is val, s is suit, r is revealed
    void reveal();
    int getIVal();
    char getSuit();
    char getCVal();
    char getColor();
    bool getRevealed();
    bool getPH();
    bool equals(Card * card);
};

#endif