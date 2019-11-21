#ifndef CURSOR_H
# define CURSOR_H

class Cursor 
{
private:
    int xpos = 0;
    int ypos = 0;
    int xmax;
    int ymax;
public:
    Cursor(int ybound, int xbound);
    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();
    int getX();
    int getY();
};

#endif