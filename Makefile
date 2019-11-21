CC=clang++
CFLAGS=-pthread -c -g -std=gnu++11
LDFLAGS=-lncurses -std=gnu++11
EXECUTABLE=SoliCurses
BUILD = build/
SRCDIR = src/
SOLDIR = src/Solitaire/

all : $(EXECUTABLE)

$(EXECUTABLE) : main.o Card.o Consts.o Cursor.o GameBoard.o Key.o Vector.o
	$(CC) -o $@ main.o Card.o Cursor.o GameBoard.o $(LDFLAGS)
	mv *.o $(BUILD)

main.o : $(SRCDIR)main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)main.cpp

Card.o : $(SOLDIR)Card.cpp $(SOLDIR)Card.hpp
	$(CC) $(CFLAGS) $(SOLDIR)Card.cpp $(SOLDIR)Card.hpp

Consts.o : $(SOLDIR)Consts.hpp
	$(CC) $(CFLAGS) $(SOLDIR)Consts.hpp

Cursor.o : $(SOLDIR)Cursor.cpp $(SOLDIR)Cursor.hpp
	$(CC) $(CFLAGS) $(SOLDIR)Cursor.cpp $(SOLDIR)Cursor.hpp

GameBoard.o : $(SOLDIR)GameBoard.cpp $(SOLDIR)GameBoard.hpp
	$(CC) $(CFLAGS) $(SOLDIR)GameBoard.cpp $(SOLDIR)GameBoard.hpp

Key.o : $(SOLDIR)Key.hpp
	$(CC) $(CFLAGS) $(SOLDIR)Key.hpp

Vector.o : $(SOLDIR)Vector.hpp
	$(CC) $(CFLAGS) $(SOLDIR)Vector.hpp

clean : 
	rm -rf *.o SoliCurses