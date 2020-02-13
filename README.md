# SoliCurses
A version of Solitaire written in C++ using the ncurses library

To compile and run this program, you need:
    
    g++
    
    GNU make
    
    ncurses library
    
    Unix-like terminal environment

To compile the program:

    cd build
    
    make

To run the program:

    cd build
    
    make run

# How To Play

The game follows the standard rules of Klondike. 
Cards in tableau can only be stacked on one another if they're a different color and have decreasing values.
To win the game, fill the foundation with same-suit cards from Ace to King. 
The layout of the gameboard is in a 19x12 grid with the leftmost side being the root of every card pile. 
Each row is a different pile of cards like the DS (discard) pile, the F (foundation) piles, or the P (tableau pile) piles.


Arrow keys - Move higlighter over a card and then pile to move a card/set of cards

Space - Confirms selection of card/card set to move to a pile

D key - Draw a card

E key - Ask user if they want to exit the game
