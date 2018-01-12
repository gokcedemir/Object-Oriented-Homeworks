/* 
 * File:   main.cpp
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241- HW05
 * Created on November 22, 2017, 12:38 AM
 */
#include <cstdlib>
#include <iostream>
#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"   //header file for abstract base class
#include "ConnectFourPlus.h"
#include <string>
#include <sstream>  //for checking invalid input -- std::istringstream

using namespace std;
using Game::ConnectFourAbstract;
using Game::ConnectFourDiag;
using Game::ConnectFourPlus;
using Game::ConnectFourPlusUndo;


int main(int argc, char** argv)
{
    string gameType;
    cout<<"Please select your game type (P or U or D): ";
    cin>> gameType;
    
    while(!(gameType[0] == 'P' || gameType[0] == 'U' || gameType[0]=='D' ))
    {
        cerr<<"Invalid input! Please press P or U or D: ";  //yanlis input checki
        cin>>gameType; 
    }
    
    if(gameType[0]=='P') //for class of  ConnectFourPlus 
    {
        ConnectFourPlus myObj;  //create connectFourPlus class of object
        myObj.setKindOfGame('P');
        myObj.playGame();  //calling playgame function
    }
    else if(gameType[0]=='D')  //for class of ConnectFourDiag
    {
        ConnectFourDiag Dobj;  //create ConnecFourDiag class of object
        Dobj.setKindOfGame('D');
        Dobj.playGame();  //calling playgame function
    }
    else if(gameType[0]=='U')   //for class of ConnectFourPlusUndo
    {   
        ConnectFourPlusUndo puObj;
        puObj.setKindOfGame('U');
        puObj.playGame();    //calling playgame function
    }
    return 0;
}

