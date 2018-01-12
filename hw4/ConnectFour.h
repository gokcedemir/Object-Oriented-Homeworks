/* 
 * File:   ConnectFour.h
 * Author: Gokce Demir
 * Student ID: 141044067
 *  CSE241 HW04
 *
 * Created on October 31, 2017, 1:29 PM
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
        
        /****************    BIG TREE   ***********************/
        ConnectFour(const ConnectFour& other);  //copy constructor
        ConnectFour& operator = (const ConnectFour& obj); // assignment operator
        ~ConnectFour(); //Destructor
        
        /*******************************************************/
        
        /*This function resize gameBoard array.*/
        void createDynamicArray(int theRw,int theCl);
        
         //print board
        void printBoard() const;  
        
        /*Accessor for filename*/
        string getFilename() const;
        /*Mutator for filename*/
        void setFilename(string file);
        
        string getLoadOrSaveFile() const { return file; }
        void setLoadOrSaveFile(string theFile) { file= theFile; }
        
        int getRow() const;  //getter for row
        void setRow(int inputRow);
       
        int getColumn() const;  //getter for column
        void setColumn(int inputColumn);
        
        string getGameType() const;   //P or C
        void setGameType(string type);
        
        char getUserContent() const;   //X or O
        void setUserContent(char content);
        
        /*This function initialize board.*/
        void initializeBoard() ; 
              
        /*This function plays the game by asking the user to
         *  play and the computer plays*/
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
        
        /*This function increment static member living cells.*/
        static int getLivingCells();
        
        void setKindOfGame(char kindOfGame);
        char getKindOfGame() const;
        
        int multipleGame();
        /*This function return bool value. This functi */
        bool loadForMultipleGame(char typeGame, char ch);
    
        friend bool operator == (const ConnectFour& obj1, const ConnectFour& obj2);
        friend bool operator != (const ConnectFour& obj1, const ConnectFour& obj2);
        
        //input olarak alinan dosyayi okuma;
        int readInputFile(string theFilename); 
 
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
                
                static int getState() ;
                
                /*compare two cells*/
                bool operator == (const Cell& other) const;
                
                /*stream insertion operator */
                friend ostream& operator << (ostream& out, const Cell& obj);
                
                /*stream extraction operator*/
                friend istream& operator >> (istream& in, const Cell& obj);
                
                enum cellState {empty, user1, user2, computer};
                cellState operator ++(int ignoreMe);  //postfix
                cellState operator ++();   //prefix version
                
            private:
                char content;
                int position_x;
                int position_y;
                cellState myState;
                static int state;
        };
        
        Cell ** gameBoard;
        string filename;   // input olarak alınan text file
        string file;   // load ve save işlemi için kullanılan file
        int row; //satır sınırı yok
        int column; // max alfabe kadar olabilir
        string gameType;    //P or C
        char userContent;  //X or O
        static int livingCells;
        char kindOfGame;
        
        /*Stream insertion and extraction operators for cell.*/
        friend ostream& operator <<(ostream& out, const ConnectFour::Cell& obj);
        friend istream& operator >>(istream& in, ConnectFour::Cell& obj);
        
        /*This function prints on the screen the connected cells with small case o and x*/
        void printSmallCaseVertical(char ch);
        void printSmallCaseHorizontal(char ch);
      
        /*This function checks that the game is tied or not. */
        bool checkTiedGame() const ;
        
        /*This function checks vertical four X or O.*/
        bool verticalCheck(char ch, const char& type);

        /*This function checks horizontal four X or O*/
        bool horizontalCheck(char ch, const char& type);

        /*This function checks the cross four X or O for user.*/
        bool crossCheck(char ch, const char& type);
};


#endif /* CONNECTFOUR_H */
