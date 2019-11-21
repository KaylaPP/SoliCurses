#include <cstdlib>
#include "Consts.hpp"

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
    void reveal() { revealed = true; } // Flips card face up
    int getIVal() { return val; }
    char getSuit() { return suit; }
    char getCVal() { return vals[val]; }
    char getColor();
    bool getRevealed() { return revealed; }
    bool getPH() { return placeholder; }
    bool equals(Card * card);
};

#endif