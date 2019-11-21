#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include "GameBoard.hpp"
#include "Cursor.hpp"
#include "Key.hpp"
#include "main.hpp"

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
    
    // Create gameboard, cursors, and key input
    GameBoard * board = new GameBoard();
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
    } while(input != Key::one && input != Key::three);

    if(input == Key::one)
    {
        drawtype = 1;
    }
    else
    {
        drawtype = 3;
    }

    input = Key::d;                     // First turn command is draw
    Key checkexit;                      // Check if you want to exit
    char * gamemessage = (char *) "\n"; // Game message that details user or programmer error
    bool first_turn = true;             // Game starts on turn 1
    bool cardmode = true;               // Select cards in gameboard if true, piles if not
    bool endgame = false;               // false if game is still going, true if foundation is full
    bool win = false;                   // true if you won the game, false if the game ended prematurely
    while(!endgame)
    {
        board->printGB(cardcursor->getY(), cardcursor->getX(), !cardmode, pilecursor->getY());
        mvprintw(12, 0, "%s\n", gamemessage);
        gamemessage = (char *) "";
        refresh();
        if(board->isWon())
        {
            win = true;
            endgame = true;
            break;
        }
        if(!first_turn)
        {
            input = (Key) getch();
        }
        else
        {
            first_turn = false;
        }

        switch(input)
        {
            case Key::y:
            case Key::Y:
            default:
                break;
            case Key::d:
                if(cardmode)
                {
                    board->draw();
                }
                break;
            case Key::e:
                clear();
                printw("Are you sure you want to exit? (y/N)");
                refresh();
                checkexit = (Key) getch();
                if(checkexit == Key::y || checkexit == Key::Y)
                {
                    endgame = true;
                }
                break;
            case Key::uarrow:
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
                if(cardmode)
                {
                    cardcursor->moveLeft();
                }
                break;
            case Key::rarrow:
                if(cardmode)
                {
                    cardcursor->moveRight();
                }
                break;
            case Key::spacebar:
                if(cardmode)
                {
                    cardmode = false;
                }
                else if(!first_turn)
                {
                    cardmode = true;
                    if(!board->moveCard(cardcursor->getY(), cardcursor->getX(), pilecursor->getY()))
                    {
                        gamemessage = (char *) "Invalid move";
                    }
                    else
                    {
                        gamemessage = (char *) "";
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
