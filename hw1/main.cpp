/* 
 * File:   main.cpp
 * Author: Gökçe Demir 
 * Student Id: 141044067
 * CSE 241 - HW01
 *
 * Created on September 20, 2017, 3:50 PM
 */


/*********************************************************************/
/* This program is connect four game. The game of Connect Four is    */ 
/* played by two players (computer-user or user1-user2) on a two     */
/* dimensional board (2D array) with rectangular cells.              */
/*********************************************************************/


#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>  //for checking invalid input -- std::istringstream

using namespace std;

#define ZERO 0
#define ONE 1
#define FOUR 4
#define DIMENSION 20

/******************      Function Prototype         ********************/

/*This function check input that user entered.
 Return Value: The return value is integer. Return board size.    */
int checkBoardSizeInput();

/*This function create board */
void createBoardArray(int size);

/*This function print board on the screen. */
void printBoard(char array[][DIMENSION],const int size); // print array

/*This function initialize board.*/
void initializeBoard(char array[][DIMENSION],const int size); 

/*This function provides doing move for player. */
void makeMoveUser(char array[][DIMENSION], const int size, const char ch, const char flag);

/*This function checks vertical four X or O.*/
int verticalCheck(char array[][DIMENSION],const int size,const char check, const char flag);

/*This function checks horizontal four X or O*/
int horizontalCheck(char array[][DIMENSION], const int size, const char check, const char flag);

/*This function checks the cross four X or O for user.*/
int crossCheck(char array[][DIMENSION],const int size, const char check, const char flag);

/*This function checks that the game is tied or not. */
int checkTiedGame(char array[][DIMENSION], const int size);

/*This function prints on the screen the connected cells with small case o and x*/
void printSmallCaseVertical(char array[][DIMENSION], const int size, char ch);
void printSmallCaseHorizontal(char array[][DIMENSION], const int size, char ch);

/************************************************************************/


int main(int argc, char** argv)
{
    int boardSize = ZERO;
    boardSize=checkBoardSizeInput();
    createBoardArray(boardSize);
    
    return 0;
}

int checkBoardSizeInput()
{
    int size;
    string input;
    
    cout<<"Welcome to Game of Connect Four\n";
    do{
        cout<<"Please enter the board size: ";
        cin >> input;
        std::istringstream (input) >> size;
        if(size ==ZERO || size%2!=ZERO || size>DIMENSION || size<FOUR)
            cout<<"Invalid input! "<<endl;
    }while(size == ZERO || size%2!=ZERO || size>DIMENSION || size<FOUR );
    cout<<"Board size entered as: " << size << endl;
    
    return size;
}

void createBoardArray(const int size)
{
    char array[DIMENSION][DIMENSION];  //size*size board array
    int i=0;
    int j=0; 
    char flag;
    int counter=ZERO;
    int checkFlag=0;
    
    cout<< "Do you want to play 2 player(P) vs computer games(C):";
    cin >> flag;
    
    while(!(flag=='P' || flag=='C'))
    {
        cout<<"Invalid input! Please press P or C: ";
        cin>>flag;
    }
    
    
    initializeBoard(array,size);
    while(1)
    {
        if(flag == 'P') // for 2 player game
        {
            while(1)
            {
                //for first player
                cout<<endl<<"Please make your move first player (A, B, C etc.)! ";
                makeMoveUser(array,size,'X',flag);
                
                //for second player
                cout<<endl<<"Please make your move second player (A, B, C etc.)!";
                makeMoveUser(array,size,'O',flag);
            }   
        }
        else if(flag == 'C') // user1 vs computer
        {
            while(1)
            {
                //for user1
                cout<<"Please make your move first player (A, B, C etc.)! ";
                makeMoveUser(array,size,'X',flag);

                //for computer(user2)
                cout<<"\nComputer made move: ";
                
                checkFlag=0;
                for(i=size-1; i>=ZERO; --i)  //dikey check
                {
                    for(j=size-1; j>=ZERO; --j)
                    {
                        if(array[j][i]=='X')
                        {
                            ++counter;
                            if(counter==FOUR-1)
                            {
                                if(array[j-1][i]=='.' && j-1>=ZERO)
                                {
                                    array[j-1][i]='O';
                                    checkFlag=ONE;
                                    cout<<static_cast<char>(i+'A')<<endl<<endl;
                                    i=j=-1; break; //exit nested loop
                                }
                            }
                        }
                        else if(array[j][i]=='O')
                        {
                            ++counter;
                            if(counter==FOUR-1)
                            {
                                if(array[j-1][i]=='.' && j-1>=ZERO)
                                {
                                    array[j-1][i]='O';
                                    checkFlag=ONE;
                                    cout<<static_cast<char>(i+'A')<<endl<<endl;
                                    i=j=-1; break; //exit nested loop
                                }
                            }
                        }
                    }
                    counter=ZERO;
                }
                if(checkFlag==ZERO) //yatay check
                {
                    for(i=size-1; i>=ZERO; --i) //yatay check
                    {
                        for(j=size-1; j>=ZERO; --j)
                        {
                            if(array[i][j]=='X')
                            {
                                ++counter;
                                if(counter==FOUR-1)
                                {
                                    if(array[i][j-1]=='.' && j-1>=0 )
                                    {
                                        if(i-1>0 && array[i-1][j]!='.')
                                        {
                                            array[i][j-1]='O';
                                            cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                            i=j=-1; break;
                                        }
                                    }
                                    else if(array[i][j+1]=='.' && j+1<size)
                                    {
                                        if(i-1>0 && array[i-1][j]!='.')
                                        {
                                            array[i][j+1]='O';
                                            cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                            i=j=-1; break;
                                        }
                                    }
                                }
                                else
                                {
                                    if(array[i][j-1]=='.' && j-1>=0 )
                                    {
                                        array[i][j-1]='O';
                                        cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                        i=j=-1; break;
                                    }
                                    if(array[i][j+1]=='.' && j+1<size )
                                    {
                                        if(i+1<size && array[i+1][j+1]!='.' )
                                        {
                                            array[i][j+1]='O';
                                            cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                            i=j=-1; break;
                                        }
                                        else if(i+1==size)
                                        {
                                            array[i][j+1]='O';
                                            cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                            i=j=-1; break;
                                        }
                                    }
                                    if(array[i-1][j]=='.' && i-1>=0)
                                    {
                                        array[i-1][j]='O';
                                        cout<<static_cast<char>(j+'A')<<endl<<endl;
                                        i=j=-1; break;
                                    }
                                }

                            }
                        }
                        counter=ZERO;
                    }
                }
                verticalCheck(array,size,'O',flag);
                horizontalCheck(array,size,'O',flag);
                crossCheck(array,size,'O',flag);
                printBoard(array,size);
                checkTiedGame(array,size);
            }
        }
        else
        {
            cerr<<"Invalid input!\n";
            cout<<"Please press P or C: ";
            cin>>flag;
        }
    }
}
void makeMoveUser(char array[][DIMENSION],const int size,const char ch, const char flag )
{
    int i=ZERO;
    int firstIndex=ZERO;
    char move;
    int count=ZERO;
    
    cin>>move;
    
    count=ZERO;
    while((firstIndex=move-'A') >= size || (firstIndex=move-'A')<ZERO 
            || array[ZERO][firstIndex]=='X' || array[ZERO][firstIndex]== 'O') 
    {
        cerr<<"Invalid move, please try again!"<<endl;
        cout<<"Please make your move  (A, B, C etc.)! ";
        cin>>move;
        firstIndex=move-'A';
       
    }
    
    for(i=size-1; i>= ZERO; i--)
    {
        if(array[i][firstIndex]=='.')
        {
            array[i][firstIndex]= ch;
            break;                    
        }
    }
    horizontalCheck(array,size, ch,flag);
    verticalCheck(array,size,ch,flag);
    crossCheck(array,size, ch,flag);
    checkTiedGame(array,size);
    printBoard(array, size);
   
}
void printBoard(char array[DIMENSION][DIMENSION],const int size)
{
    char name='A';
    int count= ZERO;
    int i=0, j=0;
    
    for( name ='A', count=0; name <= 'Z' , count<size ; ++name, ++count)
    {
        cout<< " "<<name << " ";
    }
    cout<<endl;
   
    for(i=0; i<size; ++i)
    {
        for(j=0; j<size ; ++j)
        {
            cout<<" "<<array[i][j]<<" ";
        }
        cout<<endl;
    }
}
void initializeBoard(char array[][DIMENSION],const int size)
{
    char name='A';
    int count= ZERO;
    int i=ZERO, j=ZERO;
    
    cout<<endl;

    for( name ='A', count=0; name <= 'Z' , count<size ; ++name, ++count)
    {
        cout<< " "<< name << " ";
    }
    cout<<endl;
    
    for(i=0; i<size; ++i)
    {
        for(j=0; j<size ; ++j)
        {
            array[i][j]='.';
            cout<<" "<<array[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

}
int verticalCheck(char array[][DIMENSION],const int size,const char check, const char flag)
{
    int temp= ZERO;
    int i=ZERO;
    int j=ZERO;
    int k=ZERO;
    
    for(i=0; i<size; ++i) // checking four 
    {
        for(j=0; j<size; ++j)
        {
            if(array[j][i]== check) //dikey check
            {
                ++temp;
                if(temp == FOUR)
                {
                	if(flag=='P' && check=='X')
                	{
            			cout<< "\nFirst player won!\n\n";
                	}
                    else if(flag=='P' && check=='O')
                    {
                    	cout<< "\nSecond player won!\n\n";
                    }
                    else if(flag=='C' && check=='X')
                    {
                    	cout<< "\nYou won!\n\n";
                    }
                    else if(flag=='C' && check=='O')
                    {
                    	cout<< "\nComputer won!\n\n";
                    }
                    printSmallCaseVertical(array,size,check);
                    printBoard(array, size);
                    return 0;
                }                       
            }
            else 
                temp=ZERO;
        }
        temp=ZERO;
    }
}
int horizontalCheck(char array[][DIMENSION],const int size,const char check , const char flag)
{
    int i=ZERO, j=ZERO, temp=ZERO;
    
    for(i=0; i<size; ++i) // checking four
    {
        for(j=0; j<size; ++j)
        {
            if(array[i][j]== check) //yatay check
            {
                ++temp;
                if(temp == FOUR)
                {
                    if(flag=='P' && check=='X')
                	{
            			cout<< "\nFirst player won!\n\n";
                	}
                    else if(flag=='P' && check=='O')
                    {
                    	cout<< "\nSecond player won!\n\n";
                    }
                    else if(flag=='C' && check=='X')
                    {
                    	cout<< "\nYou won!\n\n";
                    }
                    else if(flag=='C' && check=='O')
                    {
                    	cout<< "\nComputer won!\n\n";
                    }
                    printSmallCaseHorizontal(array,size,check);
                    printBoard(array, size);
                    return 0;
                }                       
            }
            else 
                temp=ZERO;
        }
        temp=ZERO;
    }
}
int crossCheck(char array[][DIMENSION],const int size,const char check, const char flag)
{
    int temp=ZERO;
    int k=0, i=0, j=0;
    
    temp=ZERO;
    for (i = size-1; i>=0; --i)  //sağ capraz
    {
        for (j = 0; j< size; ++j)
        {
            if(array[i][j] == check)
            {
                for(k=0; k<size; ++k )
                {
                    if(array[i-k][j+k]==check)
                    {
                        ++temp;
                        if(temp==FOUR)
                        {
                            if(flag=='P' && check=='X')
		                	{
		            			cout<< "\nFirst player won!\n\n";
		                	}
		                    else if(flag=='P' && check=='O')
		                    {
		                    	cout<< "\nSecond player won!\n\n";
		                    }
		                    else if(flag=='C' && check=='X')
		                    {
		                    	cout<< "\nYou won!\n\n";
		                    }
		                    else if(flag=='C' && check=='O')
		                    {
		                    	cout<< "\nComputer won!\n\n";
		                    }
                            for(k=0; k<FOUR; ++k)
                            {
                                array[i-k][j+k]=tolower(check);
                            }
                            printBoard(array, size);
                            return 0;
                        }
                    }
                    else
                        temp=ZERO;
                }
            }
            else
                temp=ZERO;
        }
    }
    
    temp=ZERO;
    for (i = size-1; i>=0; --i)  //sol capraz
    {
        for (j =size-1 ; j>=0 ; --j)
        {
            if(array[i][j] == check)
            {
                for(k=0; k<size; ++k )
                {
                    if(array[i-k][j-k]==check)
                    {
                        ++temp;
                        if(temp==FOUR)
                        {
                            if(flag=='P' && check=='X')
		                	{
		            			cout<< "\nFirst player won!\n\n";
		                	}
		                    else if(flag=='P' && check=='O')
		                    {
		                    	cout<< "\nSecond player won!\n\n";
		                    }
		                    else if(flag=='C' && check=='X')
		                    {
		                    	cout<< "\nYou won!\n\n";
		                    }
		                    else if(flag=='C' && check=='O')
		                    {
		                    	cout<< "\nComputer won!\n\n";
		                    }
                            for(k=0; k<FOUR; ++k)
                            {
                                array[i-k][j-k]=tolower(check);
                            }
                            printBoard(array, size);
                            return 0;
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
}
void checkTiedGame(char array[][DIMENSION],const int size)
{
    int i=ZERO, j=ZERO;
    int counter=ZERO;
    
    for(i=0; i<size; ++i)
    {
        for(j=0; j<size ; ++j)
        {
            if(array[i][j]!= '.')
            {
                ++counter;
                if(counter == size*size)
                {
                    cout<<"\nTied game! Let's play again :)\n";
                    printBoard(array,size);
                    return 0;
                }
            }
            else
            {
                counter=ZERO;
                break;
            }
        }
    }
}

void printSmallCaseVertical(char array[][DIMENSION], const int size, char ch) //dikey
{
    int i=ZERO;
    int j=ZERO;
    int k=0;
    int counter=ZERO;
    
    for(i=size-1; i>=ZERO; --i) // checking four 
    {
        for(j=size-1; j>=ZERO; --j)
        {
            if(array[j][i]==ch)
            {
                ++counter;
                if(counter==FOUR)
                {
                    for(k=0; k<4; ++k)
                    {
                        array[k+j][i]=tolower(ch);
                    }
                }
            }
        }
    }
}

void printSmallCaseHorizontal(char array[][DIMENSION], const int size, char ch) //yatay check
{
    int i=ZERO;
    int j=ZERO;
    int k=0;
    int counter=ZERO;
    
    for(i=size-1; i>=ZERO; --i) // checking four 
    {
        for(j=size-1; j>=ZERO; --j)
        {
            if(array[i][j]==ch)
            {
                ++counter;
                if(counter==FOUR)
                {
                    for(k=0; k<FOUR; ++k)
                    {
                        array[i][j+k]=tolower(ch);
                    }
                }
            }
            else
            	counter=ZERO;
        }
        counter=ZERO;
    }
}


