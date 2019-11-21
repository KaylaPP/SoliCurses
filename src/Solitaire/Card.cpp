#include <cstdlib>
#include "Card.hpp"

bool Card::equals(Card * card)
{
    if(card->getCVal() == getCVal() && card->getSuit() == getSuit())
    {
        return true;
    }
    return false;
}

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

bool Card::getRevealed() 
{ 
    return revealed;
}

bool Card::getPH() 
{ 
    return placeholder; 
}

void Card::reveal() // Flips card face up
{ 
    revealed = true; 
}
    
int Card::getIVal() 
{ 
    return val; 
}
    
char Card::getSuit() 
{ 
    return suit; 
}
    
char Card::getCVal() 
{ 
    return vals[val]; 
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