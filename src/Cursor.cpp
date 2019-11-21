#include "Cursor.hpp"

Cursor::Cursor(int ybound, int xbound) // xbound and ybound are non-inclusive maximums of the x and y values
{
    xmax = --xbound;
    ymax = --ybound;
}
void Cursor::moveDown()
{
    ypos++;
    if(ypos > ymax)
    {
        ypos = 0;
    }
}
void Cursor::moveUp() 
{
    ypos--;
    if(ypos < 0)
    {
        ypos = ymax;
    }
}
void Cursor::moveRight()
{
    xpos++;
    if(xpos > xmax) 
    {
        xpos = 0;
    }
}
void Cursor::moveLeft() 
{
    xpos--;
    if(xpos < 0)
    {
        xpos = xmax;
    }
}
int Cursor::getX()
{
    return xpos;
}
int Cursor::getY()
{
    return ypos;
}
