#include "ConnectFour.h"
#include <iostream>
#include <cstdlib>  //for exit function
#include <string>
#include <sstream>  //for ching invalid input -- std::istringstream
#include <fstream>

const int FOUR = 4;  //minumum row and col 
const int ZERO= 0;
const int ONE =1;

using namespace std;

ConnectFour::ConnectFour()
{
    /*Body intentionally empty  */
}

ConnectFour::ConnectFour(int myRow, int myCol)
{
    setRow(myRow);
    setColumn(myCol);
    
    reSize();
}

ConnectFour::ConnectFour(string paramFilename)
{
    setFilename(paramFilename);
    loadFunction();
}

ConnectFour::Cell::Cell()
{
    /*Body intentionally empty */
}

ConnectFour::Cell::Cell(int posX, int posY)
{
    position_x = posX;
    position_y = posY;
}

void ConnectFour::reSize()
{
    gameCells.resize(getRow());
    for (int i = 0; i <  getRow(); i++)
        gameCells[i].resize(getColumn());
}

void ConnectFour::Cell::SetPosition_y(int posY)
{
    position_y = posY;
}

int ConnectFour::Cell::GetPosition_y() const
{
    return position_y;
}

void ConnectFour::Cell::SetPosition_x(int posX)
{
    position_x = posX;
}

int ConnectFour::Cell::GetPosition_x() const
{
    return position_x;
}

void ConnectFour::Cell::SetContent(char cellContent)
{
    content = cellContent;
}

char ConnectFour::Cell::GetContent() const
{
    return content;
}

inline int ConnectFour::getRow() const
{
    return row;
}

inline void ConnectFour::setRow(int inputRow)
{
    row=inputRow;
}

inline int ConnectFour::getColumn() const
{
    return column;
}

void ConnectFour::setColumn(int inputColumn)
{
    column=inputColumn;
}

inline string ConnectFour::getFilename() const
{
    return filename;
}

inline void ConnectFour::setFilename(string file)
{
    filename=file;
}

inline string ConnectFour::getGameType() const
{
    return gameType;
}

char ConnectFour::getUserContent() const
{
    return userContent;
}

void ConnectFour::setUserContent(char content)
{
    userContent = content;
}


void ConnectFour::setGameType(string type)
{
    while(!((type[0]=='P' || type[0]=='C' ) && type.length()==1))
    {
        cerr<<"Invalid input! Please press P or C: ";
        cin>>type;
    }
    
    gameType =type;
}

void ConnectFour::checkBoardSizeInput() 
{
    int boardCol= getColumn();
    int boardRow=getRow();
    
    for(int i=0; i<boardRow; ++i)
    {
        vector<Cell> rowCells;  //create an empty row
        for(int j=0; j<boardCol ; ++j)
        {
            Cell emptyCell(i,j);
            emptyCell.SetContent('.');
            rowCells.push_back(emptyCell);
        }
        gameCells.push_back(rowCells);
    }
    
    printBoard();

}

void ConnectFour::printBoard() const
{
    char name='A';
    int count= ZERO;
    
    cout<<endl<<"   ";
    for( name ='A', count=0; name <= 'Z' , count< getColumn(); ++name, ++count)
    {
        cout<<" "<< name << " ";
    }
    cout<<endl;
    
    for(int i=0; i< getRow(); ++i)
    {
        if(i+1>=10)
            cout<< i+1 << " ";
        else
            cout<< i+1 << "  ";
        for(int j=0; j<getColumn(); ++j )
        {
            cout<<" "<< gameCells[i][j].GetContent()<<" ";

        }
        cout<<endl;
    }
}

bool ConnectFour::checkTiedGame() const
{
    int counter=ZERO;
    int col=getColumn();
    int row=getRow();
    
    for(auto i=0; i<row; ++i)
    {
        for(auto j=0; j<col ; ++j)
        {
            if(gameCells[i][j].GetContent()!= '.')
            {
                ++counter;
                if(counter == row*col)
                {
                    cout<<"\nTied game! Let's play again :)\n";
                    printBoard();
                    return true;
                }
            }
            else
            {
                counter=ZERO;
                break;
            }
        }
    }
    return false;
}

int ConnectFour::multipleGame()
{
    int i=ZERO, j=ZERO;
    string type="";
    string input="";
    initializeBoard();
    reSize();
    bool rval=false;
    
    string typeOfGame= getGameType();
    
    if(typeOfGame[0] == 'P') // for 2 player game
    {
        for(i=ZERO; i<1; ++i)
                getline(cin, input);
       
            //for first player
            cout<<"Please make your move first player (A, B, C etc.)";
            setUserContent('X');
            rval=makeMoveUser('X',typeOfGame[0]);
            if(rval== true)
                return 1;
            getLivingCells();

            //for second player
            cout<<"Please make your move second player (A, B, C etc.)";
            setUserContent('O');
            rval=makeMoveUser('O',typeOfGame[0]);
            if(rval== true)
                return 1;
            getLivingCells();

            cout<<endl<<"LivingCell: "<<livingCells<<endl;
    }
    else if(typeOfGame[0] == 'C') // user1 vs computer
    {
        for(i=ZERO; i<1; ++i)
                getline(cin, input);
       
        //for user1
        cout<<"Please make your move first player (A, B, C etc.)! ";
        setUserContent('X');
        rval=makeMoveUser('X',typeOfGame[0]);
        if(rval==true)
            return 1;
        getLivingCells();

        //for computer(user2)
        cout<<"\nComputer made move: ";
        play();
        rval=verticalCheck('O',typeOfGame[0]);
        if(rval == true)
        {
            printBoard();
            return 1;
        }
        
        rval=horizontalCheck('O',typeOfGame[0]);
        if(rval== true)
        {
            printBoard();
            return 1;
        }
        
        rval=crossCheck('O',typeOfGame[0]);
        if(rval==true)
        {
            printBoard();
            return 1;
        }
        rval= checkTiedGame();
        if(rval== true)
        {
            printBoard();
            return 1;
        }
        
        printBoard();
       
        getLivingCells();

        cout<<endl<<"LivingCell: "<<livingCells<<endl;
    }
    else
    {
        cerr<<"Invalid input!\n";
        cout<<"Please press P or C: ";
        cin>>type;
    }
    
    
}


int ConnectFour::playGame()
{
    int i=0;
    checkBoardSizeInput();
    string type="";
    string input="";
    bool rval= false;
    
    cout<< "Do you want to play 2 player(P) vs computer games(C):";
    cin >> type;
    
    setGameType(type);
    string typeOfGame= getGameType();
    
    
    initializeBoard();
    reSize();
    
    while(rval == false)
    {
        if(typeOfGame[0] == 'P') // for 2 player game
        {
            for(i=ZERO; i<1; ++i)
                    getline(cin, input);
            while( rval == false)
            {
                //for first player
                cout<<"Please make your move first player (A, B, C etc.)";
                setUserContent('X');
                rval= makeMoveUser('X',typeOfGame[0]);
                getLivingCells();
                if(rval == true)
                    break;
                
                //for second player
                cout<<"Please make your move second player (A, B, C etc.)";
                setUserContent('O');
                rval =makeMoveUser('O',typeOfGame[0]);
                getLivingCells();
                if(rval == true)
                    break;
                
                cout<<endl<<"LivingCell: "<<livingCells<<endl;
            }   
        }
        else if(typeOfGame[0] == 'C') // user1 vs computer
        {
            for(i=ZERO; i<1; ++i)
                    getline(cin, input);
            while( rval == false)
            {
                //for user1
                cout<<"Please make your move first player (A, B, C etc.)! ";
                setUserContent('X');
                rval= makeMoveUser('X',typeOfGame[0]);
                getLivingCells();
                if(rval == true)
                    break;

                //for computer(user2)
                cout<<"\nComputer made move: ";
                play();
                rval=gameEnded('O', typeOfGame[0]);
               
                printBoard();
                if(rval == true)
                    break;
                getLivingCells();
                
                cout<<endl<<"LivingCell: "<<livingCells<<endl;
            }
        }
        else
        {
            cerr<<"Invalid input!\n";
            cout<<"Please press P or C: ";
            cin>>type;
        }
    }
    return 0;
}

bool ConnectFour::makeMoveUser(char ch, char type)
{
    int i=ZERO;
    string input="", firstWord, filename;
    int temp=ZERO;
    int rval=0;
    bool stopCondition;
    setUserContent(ch);
    
    do{
        
        if(temp!=ZERO)
        {
            cout<<"Please make your move again. ";
        }
        cout<<"To save the game.. (SAVE filename.txt):";
        ++temp;
        getline(cin,input);

        
        istringstream iss(input); 
        if(rval == 1)
            exit(1);

        i=ZERO;
        while (iss)  //stringi parcalama
        {
            i%2 == 0 ? (iss>> firstWord) : (iss>>filename);
            ++i;
        }

        setFilename(filename);
        
        rval = play(firstWord);
    }while(rval == ZERO);
    

        
    stopCondition= gameEnded(ch, type);
            
    printBoard();
    
    return stopCondition;
    
}

int ConnectFour::play(string cellPosition)
{
    int i=ZERO,firstIndex=ZERO;
    const string saveCheck="SAVE";
    const string loadCheck="LOAD";
    int control=ZERO;
    char ch= getUserContent();
    string move="";
    bool stop=false;

    
  
    if(cellPosition== saveCheck && getFilename().length() != ZERO)
    {
        saveFunction(ch);
        moveCheck(move,ch);
        control=ONE;

    }
    else if(cellPosition == loadCheck && getFilename().length()!= ZERO)
    {
        stop=loadFunction();
        if(stop == true)
            return 1;
        moveCheck(move,ch);
        control=ONE;
    }
    else if(cellPosition.length()==ONE && getFilename().length()==ZERO)
    {    
        move= cellPosition;
        while((firstIndex=move[ZERO]-'A') >= getColumn()
                || (firstIndex=move[ZERO]-'A')<ZERO 
                || gameCells[ZERO][firstIndex].GetContent()=='X' 
                || gameCells[ZERO][firstIndex].GetContent()== 'O') 
        {
            cerr<<"Invalid move, please try again!"<<endl;
            cout<<"Please make your move  (A, B, C etc.)! ";
            getline(cin,move);
            firstIndex=move[ZERO]-'A';
        }

        for(i=getRow()-1; i>= ZERO; i--)
        {
            if(gameCells[i][firstIndex].GetContent() =='.')
            {
                gameCells[i][firstIndex].SetContent(ch);
                break;                    
            }
        }
        control=ONE;
    }

    return control;
  
}

int ConnectFour::play()
{
    int i=0, j=0;
    int col= getColumn();
    int row=getRow();
    decltype (i) counter=ZERO;
    decltype (j) checkFlag=0;
       
    checkFlag=0;
    for(i=col-1; i>=ZERO; --i)  //dikey ch
    {
        for(j=row-1; j>=ZERO; --j)
        {
            if(gameCells[j][i].GetContent()=='X')
            {
                ++counter;
                if(counter==FOUR-1)
                {
                    if(gameCells[j-1][i].GetContent()=='.' && j-1>=ZERO)
                    {
                        gameCells[j-1][i].SetContent('O');
                        checkFlag=1;
                        cout<<static_cast<char>(i+'A')<<endl<<endl;
                        i=j=-1; break; //exit nested loop
                    }
                }
            }
            else if(gameCells[j][i].GetContent()=='O')
            {
                ++counter;
                if(counter==FOUR-1)
                {
                    if(gameCells[j-1][i].GetContent()=='.' && j-1>=ZERO)
                    {
                        gameCells[j-1][i].SetContent('O');
                        checkFlag=ONE;
                        cout<<static_cast<char>(i+'A')<<endl<<endl;
                        i=j=-1; break; //exit nested loop
                    }
                }
            }
        }
        counter=ZERO;
    }
    if(checkFlag==ZERO) //yatay ch
    {
        for(i=row-1; i>=ZERO; --i) //yatay ch
        {
            for(j=col-1; j>=ZERO; --j)
            {
                if(gameCells[i][j].GetContent()=='X')
                {
                    ++counter;
                    if(counter==FOUR-1)
                    {
                        if(gameCells[i][j-1].GetContent()=='.' && j-1>=0 )
                        {
                            if(i-1>=0 && gameCells[i-1][j].GetContent()!='.')
                            {
                                gameCells[i][j-1].SetContent('O');
                                cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                i=j=-1; break;
                            }
                            else
                            {
                                gameCells[i][j-1].SetContent('O');
                                cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                i=j=-1; break; 
                            }
                        }
                        else if(gameCells[i][j+1].GetContent()=='.' && j+1<col)
                        {
                            if(i-1>=0 && gameCells[i-1][j].GetContent()!='.')
                            {
                                gameCells[i][j+1].SetContent('O');
                                cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                i=j=-1; break;
                            }
                        }
                    }
                    else
                    {
                        if(gameCells[i][j-1].GetContent()=='.' && j-1>=0 )
                        {
                            if(i+1<row && gameCells[i+1][j-1].GetContent()!='.')
                            {
                                gameCells[i][j-1].SetContent('O');
                                cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                i=j=-1; break;
                            }
                        }
                        if(gameCells[i][j+1].GetContent()=='.' && j+1<col )
                        {
                            if(i+1<row && gameCells[i+1][j+1].GetContent()!='.' )
                            {
                                gameCells[i][j+1].SetContent('O');
                                cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                i=j=-1; break;
                            }
                            else if(i+1==row)
                            {
                                gameCells[i][j+1].SetContent('O');
                                cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                i=j=-1; break;
                            }
                        }
                        if(gameCells[i-1][j].GetContent()=='.' && i-1>=0)
                        {
                            gameCells[i-1][j].SetContent('O');
                            cout<<static_cast<char>(j+'A')<<endl<<endl;
                            i=j=-1; break;
                        }
                    }

                }
                else
                    counter=0;
            }
            counter=ZERO;
        }
    }
    return 0;
}


void ConnectFour::moveCheck(string move, char ch)
{
    int firstIndex=ZERO;
    
    cout<<"Please make your move  (A, B, C etc.)! ";
    getline(cin,move);
    while((firstIndex=move[ZERO]-'A') >= getColumn() 
            || (firstIndex=move[ZERO]-'A')<ZERO 
            || gameCells[ZERO][firstIndex].GetContent()=='X' 
            || gameCells[ZERO][firstIndex].GetContent()== 'O') 
    {
        cerr<<"Invalid move, please try again!"<<endl;
        cout<<"Please make your move  (A, B, C etc.)! ";
        getline(cin,move);
        firstIndex=move[ZERO]-'A';
    }

    for(auto i=getRow()-1; i>= ZERO; i--)
    {
        if(gameCells[i][firstIndex].GetContent()=='.')
        {
            gameCells[i][firstIndex].SetContent(ch);
            break;                    
        }
    }
}


bool ConnectFour::horizontalCheck(char ch, const char& type)
{
    int i=ZERO, j=ZERO, temp=ZERO;
    
    for(i=0; i<getRow(); ++i) // checking four
    {
        for(j=0; j<getColumn(); ++j)
        {
            if(gameCells[i][j].GetContent()== ch) //yatay ch
            {
                ++temp;
                if(temp == FOUR)
                {
                    if(type=='P' && ch=='X')
                    {
                        cout<< "\nFirst player won!\n\n";
                    }
                    else if(type=='P' && ch=='O')
                    {
                    	cout<< "\nSecond player won!\n\n";
                    }
                    else if(type=='C' && ch=='X')
                    {
                    	cout<< "\nYou won!\n\n";
                    }
                    else if(type=='C' && ch=='O')
                    {
                    	cout<< "\nComputer won!\n\n";
                    }
                    printSmallCaseHorizontal(ch);
                    //printBoard();
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

bool ConnectFour::verticalCheck(char ch, const char& type) //dikey
{
    int temp= ZERO;
    int i=ZERO;
    int j=ZERO;
    int k=ZERO;
    
    for(i=0; i<getColumn(); ++i) // ching four 
    {
        for(j=0; j<getRow(); ++j)
        {
            if(gameCells[j][i].GetContent()== ch) //dikey ch
            {
                ++temp;
                if(temp == FOUR)
                {
                    if(type=='P' && ch=='X')
                    {
                        cout<< "\nFirst player won!\n\n";
                    }
                    else if(type=='P' && ch=='O')
                    {
                    	cout<< "\nSecond player won!\n\n";
                    }
                    else if(type=='C' && ch=='X')
                    {
                    	cout<< "\nYou won!\n\n";
                    }
                    else if(type=='C' && ch=='O')
                    {
                    	cout<< "\nComputer won!\n\n";
                    }
                    printSmallCaseVertical(ch);
                    //printBoard();
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

bool ConnectFour::crossCheck(char ch, const char& type)
{
    int temp=ZERO;
    
    temp=ZERO;
    for (auto i = getRow()-1; i>=0; --i)  //sağ capraz
    {
        for (auto j = 0; j< getColumn(); ++j)
        {
            if(gameCells[i][j].GetContent() == ch)
            {
                for(auto k=0; k<getColumn(); ++k ) //sag capraz
                {
                    if(i-k>=ZERO && j+k<getColumn() && gameCells[i-k][j+k].GetContent()==ch)
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
                                gameCells[i-k][j+k].SetContent(tolower(ch));
                            //printBoard();
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
            if(gameCells[i][j].GetContent() == ch)
            {
                for(auto k=0; k<getColumn(); ++k )
                {
                    if( i-k>=ZERO && gameCells[i-k][j-k].GetContent()==ch )
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
                                gameCells[i-k][j-k].SetContent(tolower(ch));
                            
                            //printBoard();
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

void ConnectFour::printSmallCaseHorizontal(char ch)
{
    int counter=ZERO;
    for(auto i=getRow()-1; i>=ZERO; --i) // checking four 
    {
        for(auto j=getColumn()-1; j>=ZERO; --j)
        {
            if(gameCells[i][j].GetContent() ==ch)
            {
                ++counter;
                if(counter==FOUR)
                {
                    for(auto k=0; k<FOUR; ++k)
                    {
                        gameCells[i][j+k].SetContent(tolower(ch));
                    }
                }
            }
            else
            	counter=ZERO;
        }
        counter=ZERO;
    }
}

void ConnectFour::printSmallCaseVertical(char ch)  //dikey
{
    int counter=ZERO;
    
    for(auto i=getColumn()-1; i>=ZERO; --i) // checking four 
    {
        for(auto j=getRow()-1; j>=ZERO; --j)
        {
            if(gameCells[j][i].GetContent() == ch)
            {
                ++counter;
                if(counter==FOUR)
                {
                    for(auto k=0; k<4; ++k)
                    {
                        gameCells[k+j][i].SetContent(tolower(ch));
                    }
                }
            }
            else
                counter=ZERO;
        }
        counter=ZERO;
    }
}

void ConnectFour::checkBoardSizeInput()
{
    string r,c;
    int rw,cl, inputRow, inputCol;
        
    do{
        cout<<"Please enter the board row: ";
        cin >> r;
        std::istringstream (r) >> rw;
        setRow(rw);
        inputRow= getRow();

        if(inputRow ==ZERO || inputRow<FOUR)
            cerr<<"Invalid input! "<<endl;

    }while(inputRow ==ZERO || inputRow<FOUR );

    do{
        cout<<"Please enter the board column: ";
        cin>> c;
        std::istringstream (c) >> cl;
        setColumn(cl);

        inputCol=getColumn();

        if( inputCol==ZERO || inputCol<FOUR || inputCol>26)
            cerr<<"Invalid input! "<<endl;

    }while(inputCol==ZERO || inputCol<FOUR || inputCol>26 );

    cout<<"Board size entered as: (Row:"<<getRow()<<",Col:"<<getColumn()<<")"<< endl;

}

bool ConnectFour::loadFunction()
{
    ifstream fin;
    char ch, cont;
    string type;
    int rw,cl;
    fin.open(getFilename());
    bool stop = false;
    
    if(fin.fail())
    {
        cerr<<"Input file opening failed!\n";
        exit(1);
    }
    
    fin>>rw;
    (setRow(rw));
    fin>>cl;
    setColumn(cl);
    fin>>type;
    setGameType(type);
    fin>>ch;
    setUserContent(ch);
    fin>>livingCells;
    
    reSize();
    
    for(int i=ZERO; i<getRow(); ++i)
    {
        for(int j=ZERO; j<getColumn(); ++j)
        {
            fin>>cont;
            gameCells[i][j].SetContent(cont);
        }
        
    }
    cout<<"The game loaded from file "<<filename<<endl;
    printBoard();
    fin.close();
    if(getKindOfGame() == 'S')
    {
        stop=afterGameLoaded(type[0],ch);
        if(stop== true)
            return true;
    }
    else if(getKindOfGame() == 'M')
    {
        stop=loadForMultipleGame(type[0],ch);
        if(stop == true)
            return true;
    }
    
    
    return false;
}

void ConnectFour::saveFunction(char ch)
{
    ofstream fout;
    
    fout.open(getFilename());
    if(fout.fail())
    {
        cerr<<"Output file opening failed.\n";
        exit(1);
    }
    cout<<"The game saved in "<<getFilename()<<endl;
    fout<< getRow()<< endl<<getColumn()<<endl;
    
    fout<<getGameType()<<endl;
    fout<<ch<<endl;
    fout<<livingCells<<endl;
    
    for(int i=0; i<getRow(); ++i)
    {
        for(int j=0; j<getColumn() ; ++j)
        {
            fout<<" "<<gameCells[i][j].GetContent()<<" ";
        }
        fout<<endl;
    }
}

bool ConnectFour::loadForMultipleGame(char typeGame, char ch)
{
    int i=0, j=0, counter=0;
    int checkFlag=0;
    bool rval=false;
    
    if(typeGame == 'P') // for 2 player game
    {
        //for first player
        if(ch=='X')
        {
            cout<<"Please make your move first player (A, B, C etc.)";
            rval=makeMoveUser('X',typeGame);
            getLivingCells();
            if(rval == true)
                exit(0);
            
            cout<<"Please make your move second player (A, B, C etc.)";
            rval=makeMoveUser('O',typeGame);
            if(rval == true)
                exit(0);
            getLivingCells();
            cout<<endl<<"LivingCell: "<<livingCells<<endl;
            
        }
        //for second player
        else if(ch=='O')
        {
            cout<<"Please make your move second player (A, B, C etc.)";
            rval=makeMoveUser('O',typeGame);
            if(rval==true)
                exit(0);
            getLivingCells();
            
            cout<<"Please make your move first player (A, B, C etc.)";
            rval=makeMoveUser('X',typeGame);
            if(rval == true)
                exit(0);
            getLivingCells();
            cout<<endl<<"LivingCell: "<<livingCells<<endl;
        }
    }   

    else if(typeGame == 'C') // user1 vs computer
    {
        
        //for user1
        cout<<"Please make your move first player (A, B, C etc.)! ";
        rval=makeMoveUser('X',typeGame);
        if(rval==true)
            exit(0);
        getLivingCells();

        //for computer(user2)
        cout<<"\nComputer made move: ";
        
        play();
        rval=gameEnded('O', typeGame);
        if(rval==true)
        {
            printBoard();
            exit(0);
        }

        printBoard();
        getLivingCells();
        cout<<endl<<"LivingCell: "<<livingCells<<endl;
        
    }
    else
    {
        cerr<<"Invalid input!\n";
        cout<<"Please press P or C: ";
        cin>>typeGame;
    }
    
    return false;
}

bool ConnectFour::afterGameLoaded(char typeGame, char ch)
{
    int i=0, j=0, counter=0;
    int checkFlag=0;
    bool rval=false;
    while(rval == false)
    {
        if(typeGame == 'P') // for 2 player game
        {
            while(rval== false)
            {
                //for first player
                if(ch=='X')
                {
                    cout<<"Please make your move first player (A, B, C etc.)";
                    rval=makeMoveUser('X',typeGame);
                    getLivingCells();
                    if(rval == true)
                        exit(0);
                    
                    cout<<"Please make your move second player (A, B, C etc.)";
                    rval=makeMoveUser('O',typeGame);
                    if(rval == true)
                        exit(0);
                    getLivingCells();
                    cout<<endl<<"LivingCell: "<<livingCells<<endl;
                    
                }
                //for second player
                else if(ch=='O')
                {
                    cout<<"Please make your move second player (A, B, C etc.)";
                    rval=makeMoveUser('O',typeGame);
                    if(rval==true)
                        exit(0);
                    getLivingCells();
                    
                    cout<<"Please make your move first player (A, B, C etc.)";
                    rval=makeMoveUser('X',typeGame);
                    if(rval == true)
                        exit(0);
                    getLivingCells();
                    cout<<endl<<"LivingCell: "<<livingCells<<endl;
                }
            }   
        }
        else if(typeGame == 'C') // user1 vs computer
        {
            while(rval == false)
            {
                //for user1
                cout<<"Please make your move first player (A, B, C etc.)! ";
                rval=makeMoveUser('X',typeGame);
                if(rval==true)
                    exit(0);
                getLivingCells();

                //for computer(user2)
                cout<<"\nComputer made move: ";
                
                play();
                rval=gameEnded('O', typeGame);
                if(rval==true)
                {
                    printBoard();
                    exit(0);
                }

                printBoard();
                getLivingCells();
                cout<<endl<<"LivingCell: "<<livingCells<<endl;
            }
        }
        else
        {
            cerr<<"Invalid input!\n";
            cout<<"Please press P or C: ";
            cin>>typeGame;
        }
    }
    return false;
}


bool ConnectFour::gameEnded(char ch, char typeGame)
{
    bool stop=false;
  
    stop=horizontalCheck(ch,typeGame);
    if(stop == true)
        return true;
    
    stop=verticalCheck(ch,typeGame);
    if(stop == true)
        return true;
    
    stop=crossCheck(ch,typeGame);
    if(stop == true)
        return true;
    
    stop=checkTiedGame();
    if(stop == true)
        return true;
    
    return false;
    
}

int ConnectFour::getLivingCells()
{
    livingCells++;
    return livingCells;
}

void ConnectFour::setKindOfGame(char kindOfGame)
{
    kindOfGame = kindOfGame;
}

char ConnectFour::getKindOfGame() const
{
    return kindOfGame;
}
