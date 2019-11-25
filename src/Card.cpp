#include <cstdlib>
#include "Card.hpp"
#include "Consts.h"

char Card::getColor()
{
    if(suit == 's' || suit == 'c' || getPH() || !getRevealed())
    {
        return 'b';
    }
    else if(suit == 'd' || suit == 'h')
    {
        return 'r';
    }
    return ' ';
}

bool Card::equals(Card * card)
{
    if(card->getCVal() == getCVal() && card->getSuit() == getSuit())
    {
        return true;
    }
    return false;
}

char Card::getCVal() 
{ 
    return vals[val]; 
}

int Card::getIVal() 
{ 
    return val; 
}

bool Card::getPH() 
{ 
    return placeholder; 
}

bool Card::getRevealed() 
{ 
    return revealed;
}

char Card::getSuit() 
{ 
    return suit; 
}

void Card::reveal() // Flips card face up
{ 
    revealed = true; 
}

Card::Card() 
{
    val = 0;
    suit = ' ';
    revealed = true;
    placeholder = true;
}

Card::Card(int v, char s, bool r)
{
    val = v;
    suit = s;
    revealed = r;
    placeholder = false;
}