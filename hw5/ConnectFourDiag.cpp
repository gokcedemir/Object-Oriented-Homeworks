//This is the implementation for the class ConnectFourDiag.
//This is the file ConnectFourDiag.cpp.
//The interface for the class Cell is in the header file
//ConnectFourDiag.h

#include <iostream>
#include <string>
#include "ConnectFourDiag.h"

using namespace std;

const int FOUR = 4;  //minumum row and col 
const int ZERO= 0;
const int ONE =1;


namespace Game
{

    ConnectFourDiag::ConnectFourDiag(): ConnectFourAbstract()
    {
       /*Body intentionally empty*/
    }

    ConnectFourDiag::ConnectFourDiag(int theRow, int theCol): ConnectFourAbstract(theRow,theCol)
    {
        /*Body intentionally empty*/
    }

    /* This function that returns if the game ended. 
     * Return Value: bool if game ends return true */
    bool ConnectFourDiag::gameEnded(char ch, char typeGame)
    {
        bool stop=false;
  
        stop=crossCheck(ch,typeGame);  //carpraz check
        if(stop == true)
            return true;

        stop=checkTiedGame();   //oyunun berabere bitisini check etme

        if(stop == true)
            return true;

        return false;  //eger oyun bitmezse false return eder
    }
     /*This function checks cross four X or O*/
    bool ConnectFourDiag::crossCheck(char ch, const char& type)
    {
        int temp=ZERO;
    
        temp=ZERO;
        for (auto i = getRow()-1; i>=0; --i)  //sağ capraz
        {
            for (auto j = 0; j< getColumn(); ++j)
            {
                if(gameBoard[i][j].GetContent() == ch)
                {
                    for(auto k=0; k<getColumn(); ++k ) //sag capraz
                    {
                        if(i-k>=ZERO && j+k<getColumn() && gameBoard[i-k][j+k].GetContent()==ch)
                        {
                            ++temp;
                            if(temp==FOUR)
                            {
                                if(type=='P' && ch=='X')
                                    cout<< "\nFirst player won!\n\n";
                                else if(type=='P' && ch=='O')
                                    cout<< "\nSecond player won!\n\n";
                                else if(type=='C' && ch=='X')
                                    cout<< "\nYou won!\n\n";
                                else if(type=='C' && ch=='O')
                                    cout<< "\nComputer won!\n\n";

                                for(k=0; k<FOUR; ++k)
                                    gameBoard[i-k][j+k].SetContent(tolower(ch));
                                return true;
                            }
                        }
                        else
                            temp=ZERO;
                    }
                    temp=ZERO;
                }
                else
                    temp=ZERO;
            }
        }
        temp=ZERO;
        for (auto i = getRow()-1; i>=0; --i)  //sol capraz
        {
            for (auto j=getColumn()-1 ; j>=0 ; --j)
            {
                if(gameBoard[i][j].GetContent() == ch)
                {
                    for(auto k=0; k<getColumn(); ++k )
                    {
                        if( i-k>=ZERO && gameBoard[i-k][j-k].GetContent()==ch )
                        {
                            ++temp;
                            if(temp==FOUR)
                            {   //kazanani print etme
                                if(type=='P' && ch=='X')
                                    cout<< "\nFirst player won!\n\n";
                                else if(type=='P' && ch=='O')
                                    cout<< "\nSecond player won!\n\n";
                                else if(type=='C' && ch=='X')
                                    cout<< "\nYou won!\n\n";
                                else if(type=='C' && ch=='O')
                                    cout<< "\nComputer won!\n\n";

                                for(k=0; k<FOUR; ++k)
                                    gameBoard[i-k][j-k].SetContent(tolower(ch));
                                return true;
                            }
                        }
                        else
                            temp=ZERO;
                    }
                    temp=ZERO;
                }
                else
                    temp=ZERO;
            }
        }
        return false;
    }
        
}