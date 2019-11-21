#include <cstdlib>
#include "Card.hpp"
#include "Vector.hpp"
#include "Consts.hpp"

#ifndef GAMEBOARD_H
# define GAMEBOARD_H

class GameBoard
{
private:
    //int points;             // Current score
    int maxdraw;            // An inclusive number for the max index of drawn cards
    bool drawncards[25];    // true for drawn cards, false for not
    Card * PH = new Card(); // Placeholder card to prevent segfaults
    Card ** allcards;       // Original 52 cards
    Card *** GB;            // 12 rows of varying length card piles
    Card * last(int y);
    Vector locationOf(Card * card);
    Vector locationOf(Card * card, int y);
    void boardRefresh();
    void decreaseDrawMax();
    void undraw();
public:
    GameBoard();
    bool isWon();
    bool moveCard(int boardy, int boardx, int pileindex);
    void deallocate();
    void draw();
    void printGB(int boardy, int boardx, bool pilesel, int pileindex);
};

#endif