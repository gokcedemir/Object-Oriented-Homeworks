/* 
 * File:   ConnectFour.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 *  CSE241 HW03
 *
 * Created on October 15, 2017, 1:29 PM
 */

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <vector>
#include <string>

using namespace std;

class ConnectFour
{
    public:
        ConnectFour(); //no parameter constructor
        ConnectFour(int myRow, int myCol);
        ConnectFour(string filename);
        
        void reSize();
      
        void printBoard() const;
        
        string getFilename() const;
       
        void setFilename(string file);
        
        int getRow() const;  //getter for row
        void setRow(int inputRow);
       
        int getColumn() const;  //getter for column
        void setColumn(int inputColumn);
        
        string getGameType() const;
        void setGameType(string type);
        
        char getUserContent() const;
        void setUserContent(char content);
        
        /*This function initialize board.*/
        void initializeBoard() ; 
        
        /*This function checks that the game is tied or not. */
        bool checkTiedGame() const ;
        
        /*This function checks vertical four X or O.*/
        bool verticalCheck(char ch, const char& type);

        /*This function checks horizontal four X or O*/
        bool horizontalCheck(char ch, const char& type);

        /*This function checks the cross four X or O for user.*/
        bool crossCheck(char ch, const char& type);
        
        /*This function prints on the screen the connected cells with small case o and x*/
        void printSmallCaseVertical(char ch);
        void printSmallCaseHorizontal(char ch);
        
        /*This function plays the game by asking the user the board size first
         *      then asks the user to play and the computer plays*/
        int playGame();
        
        /*it plays the computer. */
        int play(); 
        
        /*This function takes a cell position and it plays the use*/
        int play(string cellPosition);
        
        /*This function check input that user entered. */
        void checkBoardSizeInput() ;
        
        /*Loads the game board from filename*/
        bool loadFunction();

        /*This function saves the current game status to filename */
        void saveFunction(char ch);
        
        /*This function make a move after loaded game.*/
        bool afterGameLoaded(char typeGame, char ch);
        
        /*This function provides doing move for player. */
        bool makeMoveUser(char ch, char type);
        
        /*This function provides to check move illegal or legal.*/
        void moveCheck(string move, char ch );
        
        /* This function that returns if the game ended. */
        bool gameEnded(char ch, char type);
        
        static int getLivingCells();
        
        void setKindOfGame(char kindOfGame);
        char getKindOfGame() const;
        
        int multipleGame();

        bool loadForMultipleGame(char typeGame, char ch);
    
    private:
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
        
        vector< vector<Cell> > gameCells;
        string filename;
        int row; //satır sınırı yok
        int column; // max alfabe kadar olabilir
        string gameType;    //P or C
        char userContent;  //X or O
        static int livingCells;
        char kindOfGame;
        
};


#endif /* CONNECTFOUR_H */

