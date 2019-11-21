#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "GameBoard.hpp"
#include "Vector.hpp"
#include "Card.hpp"
#include "Consts.hpp"

// Returns the last card in a given pile
Card * GameBoard::last(int y)
{
    if(y != 0)
    {
        for(int x = pilelens[y] - 1; x >= 0; x--)
        {
            if(!GB[y][x]->getPH())
            {
                return GB[y][x];
            }
        }
        return GB[y][0];
    }
    else
    {
        for(int x = 24; x >=0; x--)
        {
            if(drawncards[x])
            {
                return GB[0][x];
            }
        }
        return GB[0][0];
    }
}

Vector GameBoard::locationOf(Card * card)
{
    Vector location;
    location.y = -1;
    location.x = -1;
    for(int y = 0; y < 12; y++)
    {
        for(int x = 0; x < pilelens[y]; x++)
        {
            if(GB[y][x]->equals(card))
            {
                location.y = y;
                location.x = x;
                return location;
            }
        }
    }
    return location;
}

Vector GameBoard::locationOf(Card * card, int y)
{
    Vector location;
    location.y = y;
    location.x = -1;
    for(int x = 0; x < pilelens[y]; x++)
    {
        if(GB[y][x]->equals(card))
        {
            location.x = x;
            return location;
        }
    }
    return location;
}

// Checks and fixes the gameboard
void GameBoard::boardRefresh()
{
    // Checks for null pointers and replaces with placeholder
    for(int y = 0; y < 12; y++)
    {
        for(int x = 0; x < pilelens[y]; x++)
        {
            if(GB[y][x] == nullptr)
            {
                GB[y][x] = PH;
            }
        }
    }

    // Checks for reveals last cards in tableau
    for(int y = 5; y < 12; y++)
    {
        last(y)->reveal();
    }

    // Shifts all cards in discard to the left if a card is missing/moved
    int startpoint = -1;
    for(int x = 0; x <= maxdraw; x++)
    {
        if(GB[0][x]->getPH() && !GB[0][x + 1]->getPH())
        {
            startpoint = x;
            break;
        }
    }
    if(startpoint != -1)
    {
        for(int x = startpoint; x <= maxdraw; x++)
        {
            GB[0][x] = GB[0][(x + 1)];
            GB[0][(x + 1)] = PH;
        }
    }
}

// Makes last in drawncards false and decrease maximum cards by 1
void GameBoard::decreaseDrawMax()
{
    if(--maxdraw < -1)
    {
        maxdraw = -1;
    }
    if(maxdraw != -1)
    {
        for(int i = 24; i >= 0; i--)
        {
            if(drawncards[i])
            {
                drawncards[i] = false;
                break;
            }
        }
    }
}

// Make all items in drawncards false
void GameBoard::undraw()
{
    for(int i = 0; i < 25; i++)
    {
        drawncards[i] = false;
    }
}

// Returns a bool representing whether a game is won or not
bool GameBoard::isWon()
{
    for(int y = 1; y < 5; y++)
    {
        for(int x = 0; x < 13; x++)
        {
            if(GB[y][x]->getPH())
            {
                return false;
            }
        }
    }
    return true;
}

// Moves selected card to selected pile if possible and returns true if successful, false if not
bool GameBoard::moveCard(int boardy, int boardx, int pileindex)
{
    // Immediate movement disqualifiers
    if
    (
        pileindex == 0 ||
        boardy == pileindex ||
        GB[boardy][boardx]->getPH() ||
        !GB[boardy][boardx]->getRevealed() ||
        (boardy >= 1 && boardy <= 4 && boardx != 0) ||
        (boardy == 0 && !drawncards[boardx])
    )
    {
        return false;
    }
    // Checks for movement based on valid locations
    if(boardy == 0) // Movement from discard
    {
        int lastcard = -1;
        for(int i = 24; i >= 0; i--)
        {
            if(GB[0][i]->equals(last(0)))
            {
                lastcard = i;
            }
        }
        if((lastcard > 2 && boardx == 2) || lastcard == boardx) // Valid movement from discard
        {
            if(pileindex >= 1 && pileindex <= 4) // Move to foundation
            {
                if(last(pileindex)->getPH() && last(0)->getIVal() == 1) // Valid move
                {
                    GB[pileindex][0] = last(0);
                    GB[locationOf(last(0)).y][locationOf(last(0)).x] = PH;
                    decreaseDrawMax();
                    return true;
                }
                else if(last(pileindex)->getSuit() == last(0)->getSuit() && last(pileindex)->getIVal() == last(0)->getIVal() - 1)
                {
                    GB[pileindex][locationOf(last(pileindex)).x + 1] = last(0);
                    GB[locationOf(last(0)).y][locationOf(last(0)).x] = PH;
                    decreaseDrawMax();
                    return true;
                }
            }
            else if(pileindex > 4) // Movement to tableau
            {
                if(last(pileindex)->getPH() && last(boardy)->getIVal() == 13)
                {
                    GB[pileindex][0] = last(boardy);
                    GB[locationOf(last(boardy)).y][locationOf(last(boardy)).x] = PH;
                    decreaseDrawMax();
                    return true;
                }
                for(int x = 0; x < pilelens[pileindex]; x++)
                {
                    if
                    (
                        GB[pileindex][x]->getPH() && 
                        last(boardy)->getColor() != last(pileindex)->getColor() && 
                        last(boardy)->getIVal() == last(pileindex)->getIVal() - 1
                    ) // Valid movement
                    {
                        GB[pileindex][x] = last(boardy);
                        GB[locationOf(last(boardy)).y][locationOf(last(boardy)).x] = PH;
                        decreaseDrawMax();
                        return true;
                    }
                }
            }
        }
    }
    else if(boardy >= 1 && boardy <= 4) // Movement from foundation
    {
        if(pileindex > 4) // Movement to tableau
        {
            for(int x = 0; x < pilelens[pileindex]; x++)
            {
                if
                (
                    GB[pileindex][x]->getPH() && 
                    last(boardy)->getColor() != last(pileindex)->getColor() && 
                    last(boardy)->getIVal() == last(pileindex)->getIVal() - 1
                ) // Valid movement
                {
                    GB[pileindex][x] = last(boardy);
                    GB[locationOf(last(boardy)).y][locationOf(last(boardy)).x] = PH;
                    return true;
                }
            }
        }
    }
    else if(boardy > 4) // Movement from tableau
    {
        if(pileindex >= 1 && pileindex <= 4) // Movement to foundation
        {
            if(last(pileindex)->getPH() && last(boardy)->getIVal() == 1) // Valid move
                {
                    GB[pileindex][0] = last(boardy);
                    GB[boardy][boardx] = PH;
                    return true;
                }
                else if(last(pileindex)->getSuit() == last(boardy)->getSuit() && last(pileindex)->getIVal() == last(boardy)->getIVal() - 1)
                {
                    GB[pileindex][locationOf(last(pileindex)).x + 1] = last(boardy);
                    GB[boardy][boardx] = PH;
                    return true;
                }
        }
        else if(pileindex > 4) // Movement to tableau
        {
            bool singlecard = false;
            if(GB[boardy][boardx + 1]->getPH())
            {
                singlecard = true;
            }
            if(last(pileindex)->getPH() && GB[boardy][boardx]->getIVal() == 13) // Valid movement with King to empty spot
            {
                for(int x = boardx; x < pilelens[boardy]; x++)
                {
                    if(!GB[boardy][x]->getPH())
                    {
                        GB[pileindex][x - boardx] = GB[boardy][x];
                        GB[boardy][x] = PH;
                    }
                    else
                    {
                        break;
                    }
                }
                return true;
            }
            else if
            (
                GB[boardy][boardx]->getColor() != last(pileindex)->getColor() &&
                GB[boardy][boardx]->getIVal() == last(pileindex)->getIVal() - 1
            ) // Valid movement of non-king card
            {
                if(singlecard)
                {
                    GB[locationOf(last(pileindex)).y][locationOf(last(pileindex)).x + 1] = GB[boardy][boardx];
                    GB[boardy][boardx] = PH;
                    return true;
                }
                else // if moving multiple cards
                {
                    for(int x = boardx; x < pilelens[boardy]; x++)
                    {
                        if(!GB[boardy][x]->getPH())
                        {
                            GB[pileindex][(locationOf(PH, pileindex).x)] = GB[boardy][x];
                            GB[boardy][x] = PH;
                        }
                        else
                        {
                            break;
                        }
                    }
                    return true;
                }
            }
        }
    }

    return false;
}

// Deallocates all pointers
void GameBoard::deallocate()
{
    delete PH;

    for(int i = 0; i < 52; i++)
    {
        delete allcards[i];
    }
    delete[] allcards;

    for(int i = 0; i < 12; i++)
    {
        delete[] GB[i];
    }
    delete[] GB;
}

// Draws 1 or 3 cards
void GameBoard::draw()
{
    int startpoint = -1;
    for(int i = 0; i <= maxdraw; i++) // Find where the undrawn card is
    {
        if(!drawncards[i])
        {
            startpoint = i;
            break;
        }
    }
    if(startpoint != -1) // Draw 1 or 3 cards
    {
        for(int i = startpoint; i < startpoint + drawtype; i++)
        {
            if(i <= maxdraw)
            {
                drawncards[i] = true;
            }
            else
            {
                break;
            }
        }
    }
    else // Put all cards back in the deck
    {
        undraw();
    }
}

// Prints all items in the gameboard
void GameBoard::printGB(int boardy, int boardx, bool pilesel, int pileindex)
{
    boardRefresh();

    // Print discard
    int colorpair = 1;
    if(pilesel && pileindex == 0)
    {
        colorpair = 3;
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(colorpair));
    mvprintw(0, 0, "%s", piles[0]);
    attroff(COLOR_PAIR(colorpair));
    attron(COLOR_PAIR(1));

    printw(" [  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ]");

    for(int i = maxdraw, count = 2; i >= 0; i--)
    {
        if(i < 3 || drawncards[i])
        {
            mvprintw(4 + 4 * count--, 0, "AA");
            if(count < 0)
            {
                break;
            }
        }
    }

    for(int i = 3; i < 19; i++)
    {
        if(boardx == i && boardy == 0)
        {
            colorpair = 3;
        }
        else
        {
            colorpair = 1;
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(colorpair));
        mvprintw(0, 4 + 4 * i, "  ");
        attroff(COLOR_PAIR(colorpair));
        attron(COLOR_PAIR(1));
    }

    // Print foundation
    for(int i = 1; i < 5; i++)
    {
        colorpair = 1;
        if(pilesel && pileindex == i)
        {
            colorpair = 3;
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(colorpair));
        mvprintw(i, 0, "%s", piles[i]);
        attroff(COLOR_PAIR(colorpair));
        attron(COLOR_PAIR(1));

        printw(" [  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ]");
        for(int n = 0; n < 19; n++)
        {
            Card * printcard;
            if(n > 0)
            {
                printcard = PH;
            }
            else
            {
                printcard = last(i);
            }
            if(n == boardx && i == boardy)
            {
                if(printcard->getColor() == 'b')
                {
                    colorpair = 3;
                }
                else
                {
                    colorpair = 4;
                }
            }
            else
            {
                if(printcard->getColor() == 'b' || !printcard->getRevealed())
                {
                    colorpair = 1;
                }
                else
                {
                    colorpair = 2;
                }
            }
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(colorpair));
            if(printcard->getRevealed())
            {
                mvprintw(i, 4 + 4 * n, "%c%c", printcard->getCVal(), printcard->getSuit());
            }
            attroff(COLOR_PAIR(colorpair));
            attron(COLOR_PAIR(1));
        }
    }

    // Print tableau
    for(int i = 5; i < 12; i++)
    {
        colorpair = 1;
        if(pilesel && pileindex == i)
        {
            colorpair = 3;
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(colorpair));
        mvprintw(i, 0, "%s", piles[i]);
        attroff(COLOR_PAIR(colorpair));
        attron(COLOR_PAIR(1));

        printw(" [  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ]");
        for(int n = 0; n < 19; n++)
        {
            Card * printcard;
            if(n > pilelens[i] - 1)
            {
                printcard = PH;
            }
            else
            {
                printcard = GB[i][n];
            }
            if(n == boardx && i == boardy)
            {
                if(printcard->getColor() == 'b')
                {
                    colorpair = 3;
                }
                else
                {
                    colorpair = 4;
                }
            }
            else
            {
                if(printcard->getColor() == 'b' || !printcard->getRevealed())
                {
                    colorpair = 1;
                }
                else
                {
                    colorpair = 2;
                }
            }
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(colorpair));
            if(printcard->getRevealed())
            {
                mvprintw(i, 4 + 4 * n, "%c%c", printcard->getCVal(), printcard->getSuit());
            }
            else
            {
                mvprintw(i, 4 + 4 * n, "--");
            }
            attroff(COLOR_PAIR(colorpair));
            attron(COLOR_PAIR(1));
        }
    }
}

GameBoard::GameBoard()
{
    // Set private values
    maxdraw = 23;               // An inclusive number for the max index of drawn cards
    PH = new Card();            // Placeholder card to prevent segfaults
    allcards = new Card * [52]; // Original 52 cards
    GB = new Card ** [12];      // 12 rows of varying length card piles

    // Random seed based on time
    srand(time(NULL));

    // Generate random indices
    bool repeating = true;
    int randnums[52];
    int i;
    for(i = 0; i < 52; i++)
    {
        randnums[i] = rand() % 52;
    }
    while(repeating)
    {
        repeating = false;
        for(i = 0; i < 52; i++)
        {
            for(int j = 0; j < 52; j++)
            {
                if(j != i && randnums[j] == randnums[i])
                {
                    randnums[j] = rand() % 52;
                    repeating = true;
                }
            }
        }
    }

    // Create 52 cards
    i = 0;
    for(int v = 0; v < 13; v++)
    {
        for(int s = 0; s < 4; s++)
        {
            allcards[randnums[i++]] = new Card(v + 1, suits[s], false);
        }
    }

    // Add piles to GB's rows
    for(i = 0; i < 12; i++)
    {
        GB[i] = new Card * [pilelens[i]];
    }

    // Add PH to GB
    for(int y = 0; y < 12; y++)
    {
        for(int x = 0; x < pilelens[y]; x++)
        {
            GB[y][x] = PH;
        }
    }

    // Add cards to tableau
    i = 1;
    int count = 0;
    for(int y = 5; y < 12; y++, i++)
    {
        for(int x = 0; x < i; x++)
        {
            GB[y][x] = allcards[count++];
        }
    }

    // Add cards to discard
    for(i = 28; i < 52; i++)
    {
        allcards[i]->reveal();
        GB[0][i - 28] = allcards[i];
    }

    // Make all cards not drawn
    for(i = 0; i < 25; i++)
    {
        drawncards[i] = false;
    }
}
