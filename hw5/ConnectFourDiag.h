/* File:   ConnectFourDiag.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HWO5
 * Created on November 22, 2017, 12:41 AM
 */

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include <iostream>
#include <string>

#include "ConnectFourAbstract.h"

using namespace std;

namespace Game
{
    class ConnectFourDiag: public ConnectFourAbstract
    {
    public:
        ConnectFourDiag(); //no parameter constructor
        ConnectFourDiag(int theRow, int theCol); 
        
         /* This function that returns if the game ended. */
        /* Return Value: bool if game ends return true */
        virtual bool gameEnded(char ch, char typeGame) override;
        
    private:
        /*This function checks the cross four X or O for user.*/
        bool crossCheck(char ch, const char& type);
    };
}

#endif /* CONNECTFOURDIAG_H */

