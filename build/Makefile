#Makefile courtesy of u/downiedowndown on reddit

CC=clang++
CFLAGS=-pthread -c -g -std=gnu++11
LDFLAGS=-lncurses -std=gnu++11
EXECUTABLE=SoliCurses
SRCDIR = ../src/

#Finds all the cpp files in the source directory
SOURCES=$(wildcard ${SRCDIR}/*.cpp)

#Uses substitution to get the filename from the source file name and turns it into <filename>.o
OBJECTS=$(SOURCES:${SRCDIR}/%.cpp=%.o)

all : $(EXECUTABLE)

# $^ is all the things in OBJECTS
$(EXECUTABLE) : ${OBJECTS}
	$(CC) -o $@ $^ $(LDFLAGS)

# %.o is anything ending in .o in the current dir. This is reliant on finding something with the name name but with .cpp extension in the source directory
%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean : 
	rm -rf *.o ${EXECUTABLE}