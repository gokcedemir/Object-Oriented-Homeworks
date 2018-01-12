//This is the implementation for the class ConnectFourPlus.
//This is the file ConnectFourPlus.cpp.
//The interface for the class ConnectFourPlus is in the header file
//ConnectFourPlus.h

#include "ConnectFourPlus.h"
#include <iostream>
#include <string>

using namespace std;

const int FOUR = 4;  //minumum row and col 
const int ZERO= 0;
const int ONE =1;

namespace Game
{
    //no parameter contructor, 
    ConnectFourPlus::ConnectFourPlus(): ConnectFourAbstract()
    {
        /*Body intentionally empty*/
    }
    ConnectFourPlus::ConnectFourPlus(int theRow, int theCol): ConnectFourAbstract(theRow,theCol)
    {
        setColumn(theCol);
        setRow(theRow);
    }
//    ConnectFourPlus::~ConnectFourPlus()
//    {
////        for(int i = 0; i < getRow(); ++i)  //delete gameBoard 
////            delete [] gameBoard[i];
////
////        delete [] gameBoard;  //freestore
//    }
    /*Assignment operator for connectFour class..*/
//    ConnectFourPlus& ConnectFourPlus::operator=(const ConnectFourPlus& other)
//    {
//        /*This check for the case of having the same object on both 
//     *                  sides of the assignment operator.*/
//        if(this->row!= other.row || this->column != other.column 
//           || this->filename != other.filename || this->gameType!=other.gameType)
//        {
//            for(int i = 0; i < getRow(); ++i)  //delete gameBoard 
//                delete [] gameBoard[i];
//
//            delete [] gameBoard;
//            /*other'ın gameBoardunu olusturma*/
//            createDynamicArray(other.row, other.column);
//        }
//        this->row = other.row;
//        this->column=other.column;
//        this->filename=other.filename;
//        this->gameType=other.gameType;
//
//        for (int i = 0; i < row; i++)
//        {
//            for(int j=0; j<column; ++j) 
//            {
//                gameBoard[i][j]= other.gameBoard[i][j]; //gameBoardu doldurma
//            }
//        }
//        return *this;  // return reference
//    }
//    /*Copy constructor for ConnecFour Class */
//    ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& other)
//    {   
//        setRow(other.getRow());
//        setColumn(other.getColumn());
//        this->gameType = other.gameType;  //gameType'ı kopyalama
//        this->filename = other.filename;
//        createDynamicArray(row, column); // create gameBoard 
//        for (int i = 0; i < row; i++) 
//        {
//            for(int j=0; j<column; ++j)
//            {   /*other gameBoard'u this->gameBoarda kopyalama*/
//                gameBoard[i][j]= other.gameBoard[i][j];
//            }
//        }
//    }
    /* This function that returns if the game ended. 
    * Return Value: bool if game ends return true */
    bool ConnectFourPlus::gameEnded(char ch, char typeGame)
    {
        bool stop=false;
        stop=horizontalCheck(ch,typeGame);  //yatayi check etme
        if(stop == true)
            return true;

        stop=verticalCheck(ch,typeGame);  //dikeyi check etme
        if(stop == true)
            return true;
        
        stop=checkTiedGame();   //oyunun berabere bitisini check etme
        if(stop == true)
            return true;

        return false;  //eger oyun bitmezse false return eder
    }
    /*This function prints on the screen the connected cells with small case o and x*/
    void ConnectFourPlus::printSmallCaseHorizontal(char ch)
    {
        int counter=ZERO;
        for(auto i=getRow()-1; i>=ZERO; --i) // checking four 
        {
            for(auto j=getColumn()-1; j>=ZERO; --j)
            {
                if(gameBoard[i][j].GetContent() ==ch)
                {
                    ++counter;
                    if(counter==FOUR)
                    {
                        for(auto k=0; k<FOUR; ++k)
                        {   //kucultme
                            gameBoard[i][j+k].SetContent(tolower(ch));
                        }
                    }
                }
                else
                    counter=ZERO;
            }
            counter=ZERO;
        }
    }
    /*This function prints on the screen the connected cells with small case o and x*/
    void ConnectFourPlus::printSmallCaseVertical(char ch)
    {
        int counter=ZERO;
        for(auto i=getColumn()-1; i>=ZERO; --i) // checking four 
        {
            for(auto j=getRow()-1; j>=ZERO; --j)
            {
                if(gameBoard[j][i].GetContent() == ch)
                {
                    ++counter;
                    if(counter==FOUR)
                    {
                        for(auto k=0; k<4; ++k)
                        {   //contenti kucultme
                            gameBoard[k+j][i].SetContent(tolower(ch));
                        }
                    }
                }
                else
                    counter=ZERO;
            }
            counter=ZERO;
        }
    }
     /*This function checks vertical four X or O*/
    bool ConnectFourPlus::verticalCheck(char ch, const char& type) //dikey
    {
        int temp= ZERO, i=0,j=0,k=0;
        for(i=0; i<getColumn(); ++i) // ching four 
        {
            for(j=0; j<getRow(); ++j)
            {
                if(gameBoard[j][i].GetContent()== ch) //dikey ch
                {
                    ++temp;
                    if(temp == FOUR)
                    {
                        if(type=='P' && ch=='X')
                            cout<< "\nFirst player won!\n\n";
                        else if(type=='P' && ch=='O')
                            cout<< "\nSecond player won!\n\n";
                        else if(type=='C' && ch=='X')
                            cout<< "\nYou won!\n\n";
                        else if(type=='C' && ch=='O')
                            cout<< "\nComputer won!\n\n";
                        printSmallCaseVertical(ch);
                        return true;
                    }                       
                }
                else 
                    temp=ZERO;
            }
            temp=ZERO;
        }
        return false;
    }
     /*This function checks horizontal four X or O  */
    bool ConnectFourPlus::horizontalCheck(char ch, const char& type) //yatay
    {
        int i=ZERO, j=ZERO, temp=ZERO;
        for(i=0; i<getRow(); ++i) // checking horizontal four
        {
            for(j=0; j<getColumn(); ++j)
            {
                if(gameBoard[i][j].GetContent()== ch) //yatay ch
                {
                    ++temp;
                    if(temp == FOUR)
                    {
                        if(type=='P' && ch=='X')
                            cout<< "\nFirst player won!\n\n";
                        else if(type=='P' && ch=='O')
                            cout<< "\nSecond player won!\n\n";
                        else if(type=='C' && ch=='X')
                            cout<< "\nYou won!\n\n";
                        else if(type=='C' && ch=='O')
                            cout<< "\nComputer won!\n\n";
                        printSmallCaseHorizontal(ch);
                        return true;
                    }                       
                }
                else 
                    temp=ZERO;
            }
            temp=ZERO;
        }
        return false;
    }



}