/* File:   ConnectFourPlusUndo.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241 - Hw05
 * Created on November 22, 2017, 12:41 AM
 */

/*This class ConnectFourPlusUndo will derive from the ConnectFourPlus class. 
 * This class only accepts horizontally or vertically connected
 *  cells as the goal of the game.It can undo the
moves of the user or the computer until the beginning of the game.*/

#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include <iostream>
#include <string>
#include "ConnectFourPlus.h"
#include <vector>
#include <fstream>


namespace Game
{
    class ConnectFourPlusUndo: public ConnectFourPlus
    {
    public:
        ConnectFourPlusUndo(); //no parameter contructor
        ConnectFourPlusUndo(int theRow, int theCol);
        
        /*Undo islemi bu fonksiyon icinde gerceklesir*/
        int undo(); 
        
        /*override edilen play fonksiyonuna Undo checki eklendi*/
        virtual int play(string cellPosition) override;
        
        /*Hamle sonrası icinde copyBoard fonksiyonu cagrilir*/
        virtual void moveCheck(string move, char ch) override;
        
        /*GameBoard gameCell isimli boardları tutan vektore kopyalanır*/
        void copyBoard() ;
        
        /*Tahtanın ilk halini vektore kopyalama islemi icin overrde edildi*/
        virtual void initializeBoard() override;

        virtual void saveFunction(char ch) override;
        
        virtual bool loadFunction() override;


        
    private:
        /*Her hamleden sonra boardu Cell tipindeki vektorumde tutuyorum*/
        vector< vector< vector<Cell> > > eachMoveHolder; 
        
    };
} //Game

#endif /* CONNECTFOURPLUSUNDO_H */

