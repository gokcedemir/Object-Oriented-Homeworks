/* 
 * File:   main.cpp
 * Author: Gökçe Demir
 *
 * Created on October 15, 2017, 12:41 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "ConnectFour.h"
#include <string>
#include <sstream>  //for ching invalid input -- std::istringstream

using namespace std;

int ConnectFour::livingCells= 0;
const int numOfObject = 5;

int main(int argc, char** argv)
{
    string gameType;
    cout<<"Please select type of game: ";
    cin>> gameType;
    string num;
    int myArr[5]={0, 0, 0, 0, 0};
    int count=0;
    int number;
    
    while(!(gameType[0] == 'S' || gameType[0] == 'M' ))
    {
        cerr<<"Invalid input! Please press S or M: ";
        cin>>gameType;
    }
    
    if(gameType[0] =='S')
    {
        ConnectFour myObject;
        myObject.setKindOfGame('S');
        myObject.playGame();
    }
    else if(gameType[0] == 'M')
    {
        ConnectFour objArray[numOfObject];
        string type="";
    
    
        
        for (int i = 0; i < numOfObject; i++)
        {
            objArray[i].setKindOfGame('M');
            cout<<"Object"<<i+1<<endl;
            objArray[i].checkBoardSizeInput();
            cout<< "Do you want to play 2 player(P) vs computer games(C):";
            cin >> type;
    
            objArray[i].setGameType(type);
            
        }
        while(1)
        {
            cout<<"Enter object: ";
            cin>>num;
            std::istringstream (num) >> number; 
           
            if((number-1) >=0 && (number-1)<5)
            {
            	if(myArr[number-1]== 1)
            	{
            		cout<<"Game is already ended!"<<endl;
            	}
            	else
               		myArr[number-1]=objArray[number-1].multipleGame();
            }
            
            for (int i = 0; i < 5; i++)
            {
                
                if(myArr[i]==1)
                {
                    ++count;
                    if(count == 5)
                    {
                        return 0;
                    }
                }
                else
                    count=0;
            }
        }
    }
            
    return 0;
}

