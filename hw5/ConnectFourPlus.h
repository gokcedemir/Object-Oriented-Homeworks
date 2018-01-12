 /* File:   ConnectFourPlus.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241- HW05
 * Created on November 22, 2017, 12:41 AM
 */

/*This class ConnectFourPlus will derive from the abstract class. 
 * This class only accepts horizontally or vertically connected
 *  cells as the goal of the game.*/

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include <iostream>
#include <string>
#include "ConnectFourAbstract.h"

using namespace std;

namespace Game
{
    class ConnectFourPlus : public ConnectFourAbstract
    {
    public:
        ConnectFourPlus();  //no parameter constructor
       
        /*This function plays the game by asking the user to
         *  play and the computer plays.*/
        ConnectFourPlus(int theRow, int theCol);
        
        /* This function that returns if the game ended. */
        /* Return Value: bool if game ends return true */
        virtual bool gameEnded(char ch, char typeGame) override  ;
        
    protected:
        /*This function prints on the screen the connected cells with small case o and x*/
        void printSmallCaseVertical(char ch);
        void printSmallCaseHorizontal(char ch);
      
        /*This function checks vertical four X or O.*/
        bool verticalCheck(char ch, const char& type);

        /*This function checks horizontal four X or O*/
        bool horizontalCheck(char ch, const char& type);

    };
}



#endif /* CONNECTFOURPLUS_H */

