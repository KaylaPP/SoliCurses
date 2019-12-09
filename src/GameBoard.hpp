#include <cstdlib>
#include "Card.hpp"
#include "Consts.h"
#include "DrawType.h"
#include "Vector.h"

#ifndef GAMEBOARD_H
# define GAMEBOARD_H

class GameBoard
{
private:
    int points = 0;         // Current score
    int maxdraw;            // An inclusive number for the max index of drawn cards
    DrawType drawtype;      // The drawtype of a game of Solitaire (1 or 3)
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
    GameBoard(DrawType draw);
    ~GameBoard();
    bool isWon();
    bool moveCard(int boardy, int boardx, int pileindex);
    int getPoints();
    void draw();
    void printGB(int boardy, int boardx, bool pilesel, int pileindex);
};

#endif