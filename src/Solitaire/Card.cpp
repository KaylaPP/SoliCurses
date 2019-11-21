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