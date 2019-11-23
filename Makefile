CC=clang++
CFLAGS=-pthread -c -g -std=gnu++11
LDFLAGS=-lncurses -std=gnu++11
EXECUTABLE=SoliCurses
SRCDIR = ../src/

all : $(EXECUTABLE)

$(EXECUTABLE) : main.o Card.o Consts.o Cursor.o GameBoard.o Key.o Vector.o
	$(CC) -o $@ main.o Card.o Cursor.o GameBoard.o $(LDFLAGS)

main.o : $(SRCDIR)main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)main.cpp $(SRCDIR)main.hpp

Card.o : $(SRCDIR)Card.cpp $(SRCDIR)Card.hpp
	$(CC) $(CFLAGS) $(SRCDIR)Card.cpp

Consts.o : $(SRCDIR)Consts.hpp
	$(CC) $(CFLAGS) $(SRCDIR)Consts.hpp

Cursor.o : $(SRCDIR)Cursor.cpp $(SRCDIR)Cursor.hpp
	$(CC) $(CFLAGS) $(SRCDIR)Cursor.cpp

GameBoard.o : $(SRCDIR)GameBoard.cpp
	$(CC) $(CFLAGS) $(SRCDIR)GameBoard.cpp

Key.o : $(SRCDIR)Key.hpp
	$(CC) $(CFLAGS) $(SRCDIR)Key.hpp

Vector.o : $(SRCDIR)Vector.hpp
	$(CC) $(CFLAGS) $(SRCDIR)Vector.hpp

clean : 
	rm -rf *.o SoliCurses