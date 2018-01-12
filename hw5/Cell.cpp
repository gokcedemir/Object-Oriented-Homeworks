//This is the implementation for the class Cell.
//This is the file Cell.cpp.
//The interface for the class Cell is in the header file
//Cell.h

#include "Cell.h"
#include <iostream>

using namespace std;  //standart namespace

namespace Game
{
    
    Cell::Cell()
    {
        /*Body intentionally empty */
    }
    Cell::Cell(int posX, int posY)
    {
        position_x = posX;
        position_y = posY;
    }
    void Cell::SetPosition_y(int posY)
    {
        position_y = posY;  //setter for row
    }

    int Cell::GetPosition_y() const
    {  
        return position_y;    //getter for row
    }

    void Cell::SetPosition_x(int posX)
    {
        position_x = posX;       //setter for col
    }

    int Cell::GetPosition_x() const
    {
        return position_x;
    }

    void Cell::SetContent(char cellContent)  
    {
        content = cellContent;  // X or O
    }

    char Cell::GetContent() const
    {
        return content;
    }
}//Game