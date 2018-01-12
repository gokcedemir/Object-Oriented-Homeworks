/* 
 * File:   main.cpp
 * Author: Gökçe Demir 
 * Student Id: 141044067
 * CSE 241 - HW02
 *
 * Created on October 1, 2017, 9:00 PM
 */


/*********************************************************************/
/* This program is connect four game. The game of Connect Four is    */ 
/* played by two players (computer-user or user1-user2) on a two     */
/* dimensional board (2D array) with rectangular cells.              */
/*********************************************************************/


#include <iostream>
#include <cstdlib>  //for exit function
#include <string>
#include <sstream>  //for checking invalid input -- std::istringstream
#include <fstream>

using namespace std;

#define ZERO 0
#define ONE 1
#define FOUR 4

const int SIZE_OF_ARRAY=20;  //max array size

/******************      Function Prototype         ********************/

/*This function check input that user entered.
 Return Value: The return value is integer. Return board size.    */
void checkBoardSizeInput(int& size);

/*This function create board */
void createBoardArray(int& size);

/*This function print board on the screen. */
void printBoard(char array[][SIZE_OF_ARRAY],int& size); // print array

/*This function initialize board.*/
/*Default parameter set as four*/
void initializeBoard(char array[][SIZE_OF_ARRAY], int size=4); 

/*This function provides doing move for player. */
void makeMoveUser(char array[][SIZE_OF_ARRAY], int& size, char ch,char& flag);

/*This function checks vertical four X or O.*/
void verticalCheck(char array[][SIZE_OF_ARRAY], int& size, char check, const char& flag);

/*This function checks horizontal four X or O*/
void horizontalCheck(char array[][SIZE_OF_ARRAY], int& size,char check, const char& flag);

/*This function checks the cross four X or O for user.*/
void crossCheck(char array[][SIZE_OF_ARRAY], int& size, char check, const char& flag);

/*This function checks that the game is tied or not. */
void checkTiedGame(char array[][SIZE_OF_ARRAY], int& size);

/*This function prints on the screen the connected cells with small case o and x*/
void printSmallCaseVertical(char array[][SIZE_OF_ARRAY], int size, char ch);
void printSmallCaseHorizontal(char array[][SIZE_OF_ARRAY], int size, char ch);

/*Loads the game board from given a parameter filename*/
void loadFunction(char array[][SIZE_OF_ARRAY],  int& size,
                            const string filename, char& flag);
/*This function saves the current game status to given a parameter filename */
void saveFunction(char array[][SIZE_OF_ARRAY],  int& size, 
                            const string filename, const char& flag, char ch);

/*This function provides to check move illegal or legal.*/
void moveCheck(char array[][SIZE_OF_ARRAY],string move, int& size, char ch);

/*This function make a move after loaded game.*/
void afterGameLoaded(char array[][SIZE_OF_ARRAY], int& size, char& flag, char ch);

/************************************************************************/


int main(int argc, char** argv)
{
    int size;
    checkBoardSizeInput(size);
    createBoardArray(size);
    
    return 0;
}

void loadFunction(char array[][SIZE_OF_ARRAY],int& size,
                            const string filename,char& flag)
{
    ifstream fin;
    char ch;
    fin.open(filename);
    
    if(fin.fail())
    {
        cerr<<"Input file opening failed!\n";
        exit(ONE);
    }
    
    fin>>size;
    fin>>flag;
    fin>>ch;
    
    for(int i=ZERO; i<size; ++i)
    {
        for(int j=ZERO; j<size; ++j)
        {
            fin>>array[i][j];
        }
        
    }
    cout<<"The game loaded from file "<<filename<<endl;
    printBoard(array, size);
    fin.close();
    afterGameLoaded(array,size,flag,ch);
}

void afterGameLoaded(char array[][SIZE_OF_ARRAY], int& size, char& flag, char ch)
{
    int i=0, j=0, counter=0;
    int checkFlag=0;
    while(1)
    {
        if(flag == 'P') // for 2 player game
        {
            while(1)
            {
                //for first player
                if(ch=='X')
                {
                    cout<<"Please make your move first player (A, B, C etc.)";
                    makeMoveUser(array,size,'X',flag);
                    
                    cout<<"Please make your move second player (A, B, C etc.)";
                    makeMoveUser(array,size,'O',flag);
                }
                //for second player
                else if(ch=='O')
                {
                    cout<<"Please make your move second player (A, B, C etc.)";
                    makeMoveUser(array,size,'O',flag);
                    
                    cout<<"Please make your move first player (A, B, C etc.)";
                    makeMoveUser(array,size,'X',flag);
                }
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

void saveFunction(char array[][SIZE_OF_ARRAY],  int& size, 
                    const string filename, const char& flag,char ch)
{
    ofstream fout;
  
    fout.open(filename);
    if(fout.fail())
    {
        cerr<<"Output file opening failed.\n";
        exit(ONE);
    }
    cout<<"The game saved in "<<filename<<endl;
    fout<< size<< endl;
    
    fout<<flag<<endl;
    fout<<ch<<endl;
    
    for(int i=0; i<size; ++i)
    {
        for(int j=0; j<size ; ++j)
        {
            fout<<" "<<array[i][j]<<" ";
        }
        fout<<endl;
    }
}

void checkBoardSizeInput(int& size)
{
    string input;
    
    cout<<"Welcome to Game of Connect Four\n";
    do{
        cout<<"Please enter the board size: ";
        cin >> input;
        std::istringstream (input) >> size;
        if(size ==ZERO || size%2!=ZERO || size>SIZE_OF_ARRAY || size<FOUR)
            cerr<<"Invalid input! "<<endl;
    }while(size == ZERO || size%2!=ZERO || size>SIZE_OF_ARRAY || size<FOUR );
    cout<<"Board size entered as: " << size << endl;
    
}

void createBoardArray(int& size)
{
    char array[SIZE_OF_ARRAY][SIZE_OF_ARRAY];  //size*size board array
    int i=0;
    int j=0; 
    string flag;
    decltype (i) counter=ZERO;
    decltype (j) checkFlag=0;
    string input="";
    
    cout<< "Do you want to play 2 player(P) vs computer games(C):";
    cin >> flag;
    
    while(!((flag[0]=='P' || flag[0]=='C' ) && flag.length()==1))
    {
        cerr<<"Invalid input! Please press P or C: ";
        cin>>flag;
    }
    
    initializeBoard(array,size);
    while(1)
    {
        if(flag[0] == 'P') // for 2 player game
        {
            for(i=ZERO; i<1; ++i)
                    getline(cin, input);
            while(1)
            {
                //for first player
                cout<<"Please make your move first player (A, B, C etc.)";
                makeMoveUser(array,size,'X',flag[0]);
                
                //for second player
                cout<<"Please make your move second player (A, B, C etc.)";
                makeMoveUser(array,size,'O',flag[0]);
            }   
        }
        else if(flag[0] == 'C') // user1 vs computer
        {
            for(i=ZERO; i<1; ++i)
                    getline(cin, input);
            while(1)
            {
                //for user1
                cout<<"Please make your move first player (A, B, C etc.)! ";
                makeMoveUser(array,size,'X',flag[0]);

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
                verticalCheck(array,size,'O',flag[0]);
                horizontalCheck(array,size,'O',flag[0]);
                crossCheck(array,size,'O',flag[0]);
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
void makeMoveUser(char array[][SIZE_OF_ARRAY], int& size,char ch,char& flag )
{
    int i=ZERO,firstIndex=ZERO;
    const string saveCheck="SAVE";
    const string loadCheck="LOAD";
    string input="",move="", firstWord, filename;
    int control=ZERO;
    int temp=ZERO;
    
    do
    {
        if(temp!=ZERO)
        {
            cout<<"Please make your move again. ";
        }
        cout<<"To save the game.. (SAVE filename.txt):";
        ++temp;
        getline(cin,input);

        istringstream iss(input); 

        i=ZERO;
        while (iss)  //stringi parcalama
        {
            i%2 == 0 ? (iss>> firstWord) : (iss>>filename);
            ++i;
        }

        if(firstWord== saveCheck && filename.length() != ZERO)
        {
            saveFunction(array, size, filename, flag,ch);
            moveCheck(array,move,size,ch);
            control=ONE;

        }
        else if(firstWord == loadCheck && filename.length()!= ZERO)
        {
            loadFunction(array, size, filename, flag );
            moveCheck(array,move, size, ch);
            control=ONE;
        }
        else if(firstWord.length()==ONE && filename.length()==ZERO)
        {    
            move= firstWord;
            int count=ZERO;
            while((firstIndex=move[ZERO]-'A') >= size || (firstIndex=move[ZERO]-'A')<ZERO 
                    || array[ZERO][firstIndex]=='X' || array[ZERO][firstIndex]== 'O') 
            {
                cerr<<"Invalid move, please try again!"<<endl;
                cout<<"Please make your move  (A, B, C etc.)! ";
                getline(cin,move);
                firstIndex=move[ZERO]-'A';
            }

            for(i=size-1; i>= ZERO; i--)
            {
                if(array[i][firstIndex]=='.')
                {
                    array[i][firstIndex]= ch;
                    break;                    
                }
            }
            control=ONE;
        }
    }while(control==ZERO );
     
    horizontalCheck(array,size, ch,flag);
    verticalCheck(array,size,ch,flag);
    crossCheck(array,size, ch,flag);
    checkTiedGame(array,size);
    printBoard(array, size);
    
}
void moveCheck(char array[][SIZE_OF_ARRAY],string move, int& size, char ch)
{
    int firstIndex=ZERO;
    
    cout<<"Please make your move  (A, B, C etc.)! ";
    getline(cin,move);
    while((firstIndex=move[ZERO]-'A') >= size || (firstIndex=move[ZERO]-'A')<ZERO 
            || array[ZERO][firstIndex]=='X' || array[ZERO][firstIndex]== 'O') 
    {
        cerr<<"Invalid move, please try again!"<<endl;
        cout<<"Please make your move  (A, B, C etc.)! ";
        getline(cin,move);
        firstIndex=move[ZERO]-'A';
    }

    for(auto i=size-1; i>= ZERO; i--)
    {
        if(array[i][firstIndex]=='.')
        {
            array[i][firstIndex]= ch;
            break;                    
        }
    }
}
void printBoard(char array[SIZE_OF_ARRAY][SIZE_OF_ARRAY],int& size)
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
void initializeBoard(char array[][SIZE_OF_ARRAY],int size)
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
}
void verticalCheck(char array[][SIZE_OF_ARRAY],int& size,char check, const char& flag)
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
                    exit(0);
                }                       
            }
            else 
                temp=ZERO;
        }
        temp=ZERO;
    }
}
void horizontalCheck(char array[][SIZE_OF_ARRAY],int& size,char check , const char& flag)
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
                    exit(0);
                }                       
            }
            else 
                temp=ZERO;
        }
        temp=ZERO;
    }
}
void crossCheck(char array[][SIZE_OF_ARRAY], int& size,char check, const char& flag)
{
    int temp=ZERO;
    
    temp=ZERO;
    for (auto i = size-1; i>=0; --i)  //sağ capraz
    {
        for (auto j = 0; j< size; ++j)
        {
            if(array[i][j] == check)
            {
                for(auto k=0; k<size; ++k )
                {
                    if(i-k>=ZERO && array[i-k][j+k]==check)
                    {
                        ++temp;
                        if(temp==FOUR)
                        {
                            if(flag=='P' && check=='X')
                                    cout<< "\nFirst player won!\n\n";
                            else if(flag=='P' && check=='O')
                                cout<< "\nSecond player won!\n\n";
                            else if(flag=='C' && check=='X')
                                cout<< "\nYou won!\n\n";
                            else if(flag=='C' && check=='O')
                                cout<< "\nComputer won!\n\n";
                           
                            for(k=0; k<FOUR; ++k)
                                array[i-k][j+k]=tolower(check);
                            printBoard(array, size);
                            exit(ZERO);
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
    for (auto i = size-1; i>=0; --i)  //sol capraz
    {
        for (auto j =size-1 ; j>=0 ; --j)
        {
            if(array[i][j] == check)
            {
                for(auto k=0; k<size; ++k )
                {
                    if( i-k>=ZERO && array[i-k][j-k]==check )
                    {
                        ++temp;
                        if(temp==FOUR)
                        {
                            if(flag=='P' && check=='X')
                                cout<< "\nFirst player won!\n\n";
                            else if(flag=='P' && check=='O')
                                cout<< "\nSecond player won!\n\n";
                            else if(flag=='C' && check=='X')
                                cout<< "\nYou won!\n\n";
                            else if(flag=='C' && check=='O')
                                cout<< "\nComputer won!\n\n";
                            
                            for(k=0; k<FOUR; ++k)
                                array[i-k][j-k]=tolower(check);
                            
                            printBoard(array, size);
                            exit(ZERO);
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
void checkTiedGame(char array[][SIZE_OF_ARRAY], int& size)
{
    int counter=ZERO;
    
    for(auto i=0; i<size; ++i)
    {
        for(auto j=0; j<size ; ++j)
        {
            if(array[i][j]!= '.')
            {
                ++counter;
                if(counter == size*size)
                {
                    cout<<"\nTied game! Let's play again :)\n";
                    printBoard(array,size);
                    exit(0);
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

void printSmallCaseVertical(char array[][SIZE_OF_ARRAY], int size,char ch) //dikey
{
    int counter=ZERO;
    
    for(auto i=size-1; i>=ZERO; --i) // checking four 
    {
        for(auto j=size-1; j>=ZERO; --j)
        {
            if(array[j][i]==ch)
            {
                ++counter;
                if(counter==FOUR)
                {
                    for(auto k=0; k<4; ++k)
                    {
                        array[k+j][i]=tolower(ch);
                    }
                }
            }
        }
    }
}

void printSmallCaseHorizontal(char array[][SIZE_OF_ARRAY],int size, char ch) //yatay check
{
    
    int counter=ZERO;
    for(auto i=size-1; i>=ZERO; --i) // checking four 
    {
        for(auto j=size-1; j>=ZERO; --j)
        {
            if(array[i][j]==ch)
            {
                ++counter;
                if(counter==FOUR)
                {
                    for(auto k=0; k<FOUR; ++k)
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



