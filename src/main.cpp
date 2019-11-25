#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include "GameBoard.hpp"
#include "Cursor.hpp"
#include "Key.h"
#include "DrawType.h"

int main() 
{
    // Initialize ncurses terminal mode
    initscr();
    if(has_colors() == FALSE)
    {    
        endwin();
        std::cout << "Your terminal does not support color\n";
        exit(1);
    }
    start_color();
    
    // Initializes the 4 different color modes
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Default white text on black background
    init_pair(2, COLOR_RED, COLOR_BLACK);   // Used for printing red cards
    init_pair(3, COLOR_BLACK, COLOR_WHITE); // Selected white card
    init_pair(4, COLOR_WHITE, COLOR_RED);   // Selected red card

    attron(COLOR_PAIR(1));
    raw();
    keypad(stdscr, true);
    noecho();
    halfdelay(1);
    
    // Create cursors and key input
    Cursor * cardcursor = new Cursor(12, 19);
    Cursor * pilecursor = new Cursor(12, 1);
    Key input;

    // Prompt for game type (draw 3 vs draw 1)
    do 
    {
        printw("Would you like to play draw 3 or draw 1? (1/3)");
        refresh();
        input = (Key) getch();
        clear();
    } while(input != Key::oneKey && input != Key::threeKey);

    DrawType drawtype;

    if(input == Key::oneKey)
    {
        drawtype = DrawType::one;
    }
    else
    {
        drawtype = DrawType::three;
    }

    GameBoard * board = new GameBoard(drawtype);

    input = Key::d;                     // First turn command is draw
    Key checkexit;                      // Check if you want to exit
    int starttime = time(NULL);         // Starting time, in seconds, of the game 
    char * gamemessage = (char *) "\n"; // Game message that details user or programmer error
    bool first_turn = true;             // Game starts on turn 1
    bool cardmode = true;               // Select cards in gameboard if true, piles if not
    bool endgame = false;               // false if game is still going, true if foundation is full
    bool win = false;                   // true if you won the game, false if the game ended prematurely
    while(!endgame)
    {
        board->printGB(cardcursor->getY(), cardcursor->getX(), !cardmode, pilecursor->getY());
        mvprintw(12, 20, "%s\n", gamemessage);
        mvprintw(13, 0, "\n");
        mvprintw(13, 0, "Elapsed Time: %d seconds", time(NULL) - starttime);
        refresh();
        if(board->isWon())
        {
            win = true;
            endgame = true;
            break;
        }
        input = (Key) getch();
        if(first_turn)
        {
            starttime = time(NULL);
        }

        switch(input)
        {
            case Key::y:
            case Key::Y:
            case Key::n:
            case Key::N:
            default:
                break;
            case Key::d:
                gamemessage = (char *) "";
                if(cardmode)
                {
                    board->draw();
                    first_turn = false;
                }
                break;
            case Key::e:
                gamemessage = (char *) "";
                clear();
                printw("Are you sure you want to exit? (y/n)");
                refresh();
                do
                {
                    checkexit = (Key) getch();
                    if(checkexit == Key::y || checkexit == Key::Y)
                    {
                        endgame = true;
                    }
                } while(checkexit != Key::y && checkexit != Key::Y && checkexit != Key::n && checkexit != Key::N);
                break;
            case Key::uarrow:
                gamemessage = (char *) "";
                if(cardmode)
                {
                    cardcursor->moveUp();
                }
                else
                {
                    pilecursor->moveUp();
                }
                break;
            case Key::darrow:
                gamemessage = (char *) "";
                if(cardmode)
                {
                    cardcursor->moveDown();
                }
                else
                {
                    pilecursor->moveDown();
                }
                break;
            case Key::larrow:
                gamemessage = (char *) "";
                if(cardmode)
                {
                    cardcursor->moveLeft();
                }
                break;
            case Key::rarrow:
                gamemessage = (char *) "";
                if(cardmode)
                {
                    cardcursor->moveRight();
                }
                break;
            case Key::spacebar:
                gamemessage = (char *) "";
                if(cardmode)
                {
                    cardmode = false;
                }
                else
                {
                    first_turn = false;
                    cardmode = true;
                    if(!board->moveCard(cardcursor->getY(), cardcursor->getX(), pilecursor->getY()))
                    {
                        gamemessage = (char *) "Invalid move";
                    }
                    else
                    {
                        gamemessage = (char *) "";
                        first_turn = false;
                    }
                }
                break;
        }
    }

    // Ending operations
    endwin();
    board->deallocate();
    delete board;
    delete cardcursor;
    delete pilecursor;

    if(win)
    {
        std::cout << "Hurray you won!";
    }

    return 0;
}
