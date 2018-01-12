/* File:   ConnectFourAbstract.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE 241 - HW05
 * Created on November 22, 2017, 12:39 AM
 */

//This is the header file ConnectFourAbstract.h.
//This is the interface for the class ConnectFourAbstract .

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <iostream>
#include <string>
#include "Cell.h"

using namespace std;

namespace Game
{
    class ConnectFourAbstract
    {
    public:
        ConnectFourAbstract(); //no parameter constructor
        ConnectFourAbstract(int myRow, int myCol);
        ConnectFourAbstract(string filename);
        
        /****************    BIG TREE   ***********************/
        ConnectFourAbstract(const ConnectFourAbstract& other);  //copy constructor
        ConnectFourAbstract& operator = (const ConnectFourAbstract& obj); // assignment operator
        ~ConnectFourAbstract(); //Destructor

        /*******************************************************/
        
        void setFilename(string filename);
        string getFilename() const;
        
        //getter for row
        int getRow() const { return row; }
        void setRow(int inputRow) { row = inputRow ; } //setter 
       
        //getter for column
        inline int getColumn() const { return column; }
        inline void setColumn(int inputColumn) { column = inputColumn; }
                                         
        /*This function plays the game by asking the user to
         *  play and the computer plays*/
        int playGame();   
        
        /*it plays the computer. */
       int play();      
        
        /*This function takes a cell position and it plays the use*/
        virtual int play(string cellPosition)  ;  
        
        /* This function that returns if the game ended. */
        virtual bool gameEnded(char ch, char type) = 0 ;
        
         /*Loads the game board from filename*/
        virtual bool loadFunction() ;

        /*This function saves the current game status to filename */
        virtual void saveFunction(char ch);
        
         /*This function make a move after loaded game.*/
        bool afterGameLoaded(char typeGame, char ch);
        
        /*This function provides doing move for player. */
        bool makeMoveUser(char ch, char type) ;
        
        void setUserContent(char userContent);
        char getUserContent() const;
        
        void setGameType(string gameType);
        string getGameType() const;
        
        void setKindOfGame(char kindOfGame);  //setter for P or U or D
        char getKindOfGame() const;           //getter
        
         /*This function resize gameBoard array.*/
        void createDynamicArray(int theRw,int theCl);
      
        
    protected:
        Cell ** gameBoard;
        string filename;   // load ve save işlemi için kullanılan file
        int row; //satır sınırı yok
        int column; // max alfabe kadar olabilir
        string gameType;    //P or C
        char userContent;  //X or O
        char kindOfGame;   // Plus or Undo or Diag
        
        /*This function check input that user entered. */
        void checkBoardSizeInput() ;
        
        /*This function checks that the game is tied or not. */
        bool checkTiedGame() const ;
        
        /*This function provides to check move illegal or legal.*/
        virtual void moveCheck(string move, char ch ) ;  
        
        /*This function initialize board.*/
        virtual void initializeBoard() ; 
        
         //print board
         void printBoard() const; 
        
      
    };
    
}

#endif /* CONNECTFOURABSTRACT_H */

