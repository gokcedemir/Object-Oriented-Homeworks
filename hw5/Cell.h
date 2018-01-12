/* 
 * File:   Cell.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 *
 * Created on November 22, 2017, 12:48 AM
 */

//This is the header file Cell.h.
//This is the interface for the class Cell .

#ifndef CELL_H
#define CELL_H

#include <iostream>

namespace Game
{
    class Cell
        {
            public:
                Cell(); // no parameter constructor
                Cell(int posX, int posY);
                void SetPosition_y(int position_y);
                int GetPosition_y() const;
                void SetPosition_x(int position_x);
                int GetPosition_x() const;
                void SetContent(char content);
                char GetContent() const;

            private:
                char content;
                int position_x;
                int position_y;
        };
} //Game


#endif /* CELL_H */

