#include "ConnectFour.h"
#include <iostream>
#include <cstdlib>  //for exit function
#include <string>
#include <sstream>  //for ching invalid input -- std::istringstream
#include <fstream>

const int FOUR = 4;  //minumum row and col 
const int ZERO= 0;
const int ONE =1;
const int maxNumOfCol= 30;

using namespace std;

ConnectFour::ConnectFour():row(5), column(5)
{
    /*Body intentionally empty  */
}

ConnectFour::ConnectFour(int myRow, int myCol)
{
    setRow(myRow);
    setColumn(myCol);
}

ConnectFour::ConnectFour(string paramFilename)
{
    setFilename(paramFilename);
}

/*Destructor for ConnectFour class*/
ConnectFour::~ConnectFour()
{
    for(int i = 0; i < getRow(); ++i)  //delete gameBoard 
        delete [] gameBoard[i];

    delete [] gameBoard;
    
}
/*Copy constructor for ConnecFour Class */
ConnectFour::ConnectFour(const ConnectFour& other): 
                    row(other.getRow()), column(other.getColumn())
{
    this->gameType = other.gameType;  //gameType'ı kopyalama
    this->filename = other.filename;
    createDynamicArray(row, column); // create gameBoard 
    for (int i = 0; i < row; i++) 
    {
        for(int j=0; j<column; ++j)
        {   /*other gameBoard'u this->gameBoarda kopyalama*/
            gameBoard[i][j]= other.gameBoard[i][j];
        }
    }
}
/*Assignment operator for connectFour class..*/
ConnectFour& ConnectFour::operator =(const ConnectFour& other)
{
    /*This check for the case of having the same object on both 
     *                  sides of the assignment operator.*/
    if(this->row!= other.row || this->column != other.column 
       || this->filename != other.filename || this->gameType!=other.gameType)
    {
        for(int i = 0; i < getRow(); ++i)  //delete gameBoard 
            delete [] gameBoard[i];

        delete [] gameBoard;
        /*other'ın gameBoardunu olusturma*/
        createDynamicArray(other.row, other.column);
    }
    this->row = other.row;
    this->column=other.column;
    this->filename=other.filename;
    this->gameType=other.gameType;
    
    for (int i = 0; i < row; i++)
    {
        for(int j=0; j<column; ++j) 
        {
            gameBoard[i][j]= other.gameBoard[i][j]; //gameBoardu doldurma
        }
    }
    return *this;  // return reference
}

/*Resize gameBoard*/
void ConnectFour::createDynamicArray(int theRw, int theCl)
{
    gameBoard= new Cell *[theRw];
    for (int i = 0; i < theRw; i++) 
        gameBoard[i]= new Cell[theCl];
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
    row=inputRow;  //board row'u set etme
}

inline int ConnectFour::getColumn() const
{
    return column;
}

void ConnectFour::setColumn(int inputColumn)
{
    column=inputColumn;  //board columnu set etme
}

inline string ConnectFour::getFilename() const
{
    return filename;   //input olarak alinan file
}

inline void ConnectFour::setFilename(string file)
{
    ifstream f;
    f.open(file);
    while(f.fail())  //dosya yoksa tekrar input bekler
    {
        cout<<"The file doesn't exits, try again: ";
        cin>>file;
        if(file.length()==0) //dosya sonu EOF ise
        	exit(1);  //cstdlib
        f.open(file);
    }
    filename=file;
}

inline string ConnectFour::getGameType() const
{
    return gameType;   //P or C
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
        if(type.length()==0)  //dosya sonu EOF ise
        	exit(1);
    }
    gameType =type;
}

int ConnectFour::readInputFile(string theFilename)
{
    int boardCol=ZERO, boardRow=ZERO, i;
    int *temp;
    char ch;
    ifstream fin;  
    string line;
    char **chr;    //read char to file
   
    temp=new int[maxNumOfCol];
    fin.open(theFilename);   //dosyadan input formatı okuma
    
    if(fin.fail())   //dosya acilamazsa
    {
        cerr<<"Input file opening failed!\n";
        exit(1);
    }
    //karekter karekter okuma
    while (fin.get(ch))  // find row
    {
        if (ch == '\n')
           ++boardRow;
    }
 
    setRow(boardRow+1);  //row'u set etme, sondaki \n saymadigi icin +1 ekledim
    
    fin.close();    //dosya kapama
    fin.open(theFilename);   //dosya acma

    for (i = 0; getline(fin, line); i++)  //find max column
        temp[i]= line.length();

    boardCol= temp[0];   //temp arrayin max elemanını bulma
    for (i = 1; i < getRow() ; i++)   //column sayisini bulma
    {
        if(boardCol< temp[i])
            boardCol=temp[i];   //en uzun satir uzunluguna sahip bize columnu verir
    }
    
    setColumn(boardCol);   //columnu set etme
    /*bulunan row ve columna gore gameBoardu olusturma*/
    createDynamicArray(getRow(), getColumn());

    fin.close();
    fin.open(theFilename);

    chr = new char *[getRow()];  //temp arrayi initialize etme
    for (int i = 0; i < getRow(); i++) 
        chr[i]= new char[boardCol];
   
    for (i = 0; getline(fin, line); i++) //satir satir okuma
    {
        for(int j=0; j< line.length(); ++j)
            chr[i][j]= line[j];
    }
       
    for(i =0; i< getRow(); ++i)
    {
        for(int j=0; j< getColumn(); ++j)
            gameBoard[i][j].SetContent(chr[i][j]);  //gameBoard'u doldurma
    }
    fin.close();     //input dosyasını kapatma
    delete [] temp;
    for(int i = 0; i < getRow(); ++i)   //chr char pointer pointer arrayini geri verme
        delete [] chr[i];

    delete [] chr;

}

void ConnectFour::initializeBoard() 
{
    for(int i=0; i< getRow(); ++i)
    {
        for(int j=0; j<getColumn(); ++j )
        {   /*array'de yildizlari nokta ile initialize etme*/
            if(gameBoard[i][j].GetContent() == '*')
            {
                gameBoard[i][j].SetContent('.');
            }
            if(gameBoard[i][j].GetContent() == ' ' ||
                        gameBoard[i][j].GetContent() == '\n')
            {
                gameBoard[i][j].SetContent(' ');
            }
        } 
    }
}

void ConnectFour::printBoard() const
{
    char name='A';
    int count= ZERO;
    
    //sutun sayisi kadar harf basma
    cout<<endl<<"   ";
    for( name ='A', count=0; name <= 'Z' , count< getColumn(); ++name, ++count)
    {
        cout<<" "<< name << " ";
    }
    cout<<endl;
    
    for(int i=0; i< getRow(); ++i)
    {   //satir sayisi kadar numara basma
        if(i+1>=10)
            cout<< i+1 << " ";
        else
           cout<< i+1 << "  ";
        for(int j=0; j<getColumn(); ++j )
            cout<<" "<<gameBoard[i][j].GetContent()<< " ";
        cout<<endl;
   }
}
/*Berabere bitme durumunu check etme, eger tahta dolduysa berabere biter. */
bool ConnectFour::checkTiedGame() const
{
    int counter=ZERO;
    int col=getColumn();
    int row=getRow();
    
    for(auto i=0; i<row; ++i)
    {
        for(auto j=0; j<col ; ++j)
        {
            if(gameBoard[i][j].GetContent()!= '.')
            {
                ++counter;
                if(counter == row*col)  //tahta dolu ise
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
    printBoard();
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
        getLivingCells();   //hamle sonrasi livingCelli artirma

        //for second player
        cout<<"Please make your move second player (A, B, C etc.)";
        setUserContent('O');
        rval=makeMoveUser('O',typeOfGame[0]);
        if(rval== true)
            return 1;
        getLivingCells(); //hamle sonrasi livingCelli artirma

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
        getLivingCells();  //hamle sonrasi livingCelli artirma

        //for computer(user2)
        cout<<"\nComputer made move: ";
        play();
        rval=verticalCheck('O',typeOfGame[0]);   //dikey check
        if(rval == true)
        {
            printBoard();
            return 1;
        }
        rval=horizontalCheck('O',typeOfGame[0]);  //yatay check
        if(rval== true)
        {
            printBoard();
            return 1;
        }
        rval=crossCheck('O',typeOfGame[0]);  //carpraz check
        if(rval==true)
        {
            printBoard();
            return 1;
        }
        rval= checkTiedGame();  //berabere durumu check etme
        if(rval== true)
        {
            printBoard();
            return 1;
        }
        printBoard();
        getLivingCells();  //hamle sonrasi livingCelli artirma

        cout<<endl<<"LivingCell: "<<livingCells<<endl;
    }
    else  //error durumu
    {
        cerr<<"Invalid input!\n";
        cout<<"Please press P or C: ";
        cin>>type;
    }
}
/*This function plays the computer. */
int ConnectFour::playGame() 
{
    int i=0;
    checkBoardSizeInput();  
    initializeBoard();   //tahtayi initialie etme
    string type="";
    string input="";
    bool rval= false;
    
    cout<< "Do you want to play 2 player(P) vs computer games(C):";
    cin >> type;
    setGameType(type);
    printBoard();       //tahtayi ekrana basma
    string typeOfGame= getGameType();  //gameTye P or C
    
    initializeBoard();
    
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
                getLivingCells();  //hamle sonrasi livingCelli artirma
                if(rval == true)
                    break;
                
                //for second player
                cout<<"Please make your move second player (A, B, C etc.)";
                setUserContent('O');
                rval =makeMoveUser('O',typeOfGame[0]);
                getLivingCells();  //hamle sonrasi livingCelli artirma
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
                getLivingCells();  //hamle sonrasi livingCelli artirma
                if(rval == true)
                    break;

                //for computer(user2)
                cout<<"\nComputer made move: ";
                play();
                rval=gameEnded('O', typeOfGame[0]);
               
                printBoard();
                if(rval == true)
                    break;
                getLivingCells();    //hamle sonrasi livingCelli artirma
                //yaşayan obje sayisini ekrana basma
                cout<<endl<<"LivingCell: "<<livingCells<<endl;
            }
        }
        else  //error durumu
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
            cout<<"Please make your move again. ";
        cout<<"To save the game.. (SAVE filename.txt):";
        ++temp;
        getline(cin,input);
        if(input.length()==0)  //dosya sonu EOF checki
        	exit(1);
        istringstream iss(input); 
        if(rval == 1)
            exit(1);

        i=ZERO;
        while (iss)  //stringi parcalama
        {
            i%2 == 0 ? (iss>> firstWord) : (iss>>filename);
            ++i;
        }
        setLoadOrSaveFile(filename);  //file set etme
        
        rval = play(firstWord);  //move'u gönderme
    }while(rval == ZERO);

    stopCondition= gameEnded(ch, type); //oyunun bitip bitmedigini check etme
    printBoard();
    
    return stopCondition;
}

int ConnectFour::play(string cellPosition)  
{
    int i=ZERO,firstIndex=ZERO,control=ZERO;
    const string saveCheck="SAVE";
    const string loadCheck="LOAD";
    char ch= getUserContent();
    string move="";
    bool stop=false;
  
    if(cellPosition== saveCheck && getLoadOrSaveFile().length() != ZERO)
    {
        saveFunction(ch);
        moveCheck(move,ch);
        control=ONE;
    }
    else if(cellPosition == loadCheck && getLoadOrSaveFile().length()!= ZERO)
    {
        stop=loadFunction();
        if(stop == true)
            return 1;
        moveCheck(move,ch);
        control=ONE;
    }
    else if(cellPosition.length()==ONE && getLoadOrSaveFile().length()==ZERO)
    {    
        move= cellPosition;
        while((firstIndex=move[ZERO]-'A') >= getColumn()
                || (firstIndex=move[ZERO]-'A')<ZERO 
                || gameBoard[ZERO][firstIndex].GetContent()=='X' 
                || gameBoard[ZERO][firstIndex].GetContent()== 'O') 
        {
            cerr<<"Invalid move, please try again!"<<endl;
            cout<<"Please make your move  (A, B, C etc.)! ";
            getline(cin,move);
            if(move.length()==0)  //dosya sonu EOF checki
            	exit(1);
            firstIndex=move[ZERO]-'A';
        }

        for(i=getRow()-1; i>= ZERO; i--)
        {
            if(gameBoard[i][firstIndex].GetContent() =='.')
            {
                gameBoard[i][firstIndex].SetContent(ch);
                break;                    
            }
            else if(gameBoard[i][firstIndex].GetContent() ==' ')
            {
                cerr<<"Invalid input!";
                return 0;   //false return eder
            }
        }
        control=ONE;
    }
    return control;
}

int ConnectFour::play()  //its play the computer
{
    int i=0, j=0,col= getColumn(),row=getRow();
    decltype (i) counter=ZERO;
    decltype (j) checkFlag=0;
       
    checkFlag=0;
    for(i=col-1; i>=ZERO; --i)  //dikey ch
    {
        for(j=row-1; j>=ZERO; --j)
        {
            if(gameBoard[j][i].GetContent()=='X')
            {
                ++counter;
                if(counter==FOUR-1)
                {
                    if(gameBoard[j-1][i].GetContent()=='.' && j-1>=ZERO)
                    {
                        gameBoard[j-1][i].SetContent('O');
                        checkFlag=1;
                        cout<<static_cast<char>(i+'A')<<endl<<endl;
                        i=j=-1; break; //exit nested loop
                    }
                }
            }
            else if(gameBoard[j][i].GetContent()=='O')
            {
                ++counter;
                if(counter==FOUR-1)
                {
                    if(gameBoard[j-1][i].GetContent()=='.' && j-1>=ZERO)
                    {
                        gameBoard[j-1][i].SetContent('O');
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
                if(gameBoard[i][j].GetContent()=='X')
                {
                    ++counter;
                    if(counter==FOUR-1)
                    {
                        if(gameBoard[i][j-1].GetContent()=='.' && j-1>=0 )
                        {
                            if(i-1>=0 && gameBoard[i-1][j].GetContent()!='.')
                            {
                                gameBoard[i][j-1].SetContent('O');
                                cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                i=j=-1; break;   //exit nested loop
                            }
                            else
                            {
                                gameBoard[i][j-1].SetContent('O');
                                cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                i=j=-1; break;   //exit nested loop
                            }
                        }
                        else if(gameBoard[i][j+1].GetContent()=='.' && j+1<col)
                        {
                            if(i-1>=0 && gameBoard[i-1][j].GetContent()!='.')
                            {
                                gameBoard[i][j+1].SetContent('O');
                                cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                i=j=-1; break;    //exit nested loop
                            }
                        }
                    }
                    else
                    {
                        if(gameBoard[i][j-1].GetContent()=='.' && j-1>=0 )
                        {
                            if((i+1<row && gameBoard[i+1][j-1].GetContent()!='.') 
                            || i+1==row )
                            {
                                gameBoard[i][j-1].SetContent('O');
                                cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                i=j=-1; break;   //exit nested loop
                            }
                        }
                        if(gameBoard[i][j+1].GetContent()=='.' && j+1<col )
                        {
                            if(i+1<row && gameBoard[i+1][j+1].GetContent()!='.' )
                            {
                                gameBoard[i][j+1].SetContent('O');
                                cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                i=j=-1; break;   //exit nested loop
                            }
                            else if(i+1==row)
                            {
                                gameBoard[i][j+1].SetContent('O');
                                cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                i=j=-1; break;   //exit nested loop
                            }
                        }
                        if(gameBoard[i-1][j].GetContent()=='.' && i-1>=0)
                        {
                            gameBoard[i-1][j].SetContent('O');
                            cout<<static_cast<char>(j+'A')<<endl<<endl;
                            i=j=-1; break;  //exit nested loop
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
    if(move.length()==0)
    	exit(1);
    while((firstIndex=move[ZERO]-'A') >= getColumn() 
            || (firstIndex=move[ZERO]-'A')<ZERO 
            || gameBoard[ZERO][firstIndex].GetContent()=='X' 
            || gameBoard[ZERO][firstIndex].GetContent()== 'O') 
    {
        cerr<<"Invalid move, please try again!"<<endl;
        cout<<"Please make your move  (A, B, C etc.)! ";
        getline(cin,move);
        if(move.length()==0) //dosya sonu EOF checki
        	exit(1);
        firstIndex=move[ZERO]-'A';
    }

    for(auto i=getRow()-1; i>= ZERO; i--)
    {
        if(gameBoard[i][firstIndex].GetContent()=='.')
        {
            gameBoard[i][firstIndex].SetContent(ch);
            break;                    
        }
    }
}

 /*This function checks horizontal four X or O*/
bool ConnectFour::horizontalCheck(char ch, const char& type)
{
    int i=ZERO, j=ZERO, temp=ZERO;
    
    for(i=0; i<getRow(); ++i) // checking four
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
 /*This function checks vertical four X or O*/
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
 /*This function checks cross four X or O*/
bool ConnectFour::crossCheck(char ch, const char& type)
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
/*This function prints on the screen the connected cells with small case o and x*/
void ConnectFour::printSmallCaseHorizontal(char ch)
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
                    {
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
void ConnectFour::printSmallCaseVertical(char ch)  //dikey
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
                    {
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

void ConnectFour::checkBoardSizeInput()
{
    string file;
    cout<<"Please enter your file name: ";
    cin>>file;    //kullanicidan input olarak filename alma
    if(file.length()==0)  //check EOF 
    	exit(1);
    setFilename(file);   //file set etme
    readInputFile(getFilename());  //dosyayı okuyup col ve rowu bulma
}
bool ConnectFour::loadFunction()
{
    ifstream fin;
    char ch,cont;
    string type,temp;
    int rw,cl;
    fin.open(getLoadOrSaveFile());  //load yapılacak dosyayı acma
    bool stop = false;
    string line;
    char **chr;    //read char to file
    
    if(fin.fail())
    {
        cerr<<"Input file opening failed!\n";
        exit(1);
    }
    
    for(int i = 0; i < getRow(); ++i)  //gameBoard'u resize yapma
        delete [] gameBoard[i];

    delete [] gameBoard;
    
    fin>>rw;
    (setRow(rw));
    fin>>cl;
    setColumn(cl);
    fin>>type;
    setGameType(type);
    fin>>ch;
    setUserContent(ch);
    fin>>livingCells;
    
    //resize gameBoard
    createDynamicArray(getRow(), getColumn());
    
    chr = new char *[getRow()];
    for (int i = 0; i < getRow(); i++) 
        chr[i]= new char[getColumn()];
        getline(fin,temp);
    for (int i = 0; getline(fin, line); i++)
    {
        for(int j=0; j< line.length(); ++j)
            chr[i][j]= line[j];
    }
       
    for(int i =0; i< getRow(); ++i)
    {
        for(int j=0; j< getColumn(); ++j)
            gameBoard[i][j].SetContent(chr[i][j]);  //gameBoard'u doldurma
    }

    cout<<"The game loaded from file "<<getLoadOrSaveFile()<<endl;
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
    
    fout.open(getLoadOrSaveFile());
    if(fout.fail())
    {
        cerr<<"Output file opening failed.\n";
        exit(1);
    }
    cout<<"The game saved in "<<getLoadOrSaveFile()<<endl;
    fout<< getRow()<< endl<<getColumn()<<endl;  //row ve colu yazma
    fout<<getGameType()<<endl;    //game tipini yazma P or C
    fout<<ch<<endl;   // X or O
    fout<<livingCells<<endl;   //cell sayisi
    
    for(int i=0; i<getRow(); ++i)
    {
        for(int j=0; j<getColumn() ; ++j)
        {
            fout<<gameBoard[i][j].GetContent();
        }
        fout<<endl;
    }
}

bool ConnectFour::loadForMultipleGame(char typeGame, char ch)
{
    bool rval=false;
    
    if(typeGame == 'P') // for 2 player game
    {
        //for first player
        if(ch=='X')
        {
            cout<<"Please make your move first player (A, B, C etc.)";
            rval=makeMoveUser('X',typeGame);
            getLivingCells();  //hamle sonrasi livingCell artirma
            if(rval == true)
                exit(0);
            
            cout<<"Please make your move second player (A, B, C etc.)";
            rval=makeMoveUser('O',typeGame);
            if(rval == true)
                exit(0);
            getLivingCells();   //hamle sonrasi livingCell artirma
            cout<<endl<<"LivingCell: "<<livingCells<<endl;
            
        }
        //for second player
        else if(ch=='O')
        {
            cout<<"Please make your move second player (A, B, C etc.)";
            rval=makeMoveUser('O',typeGame);
            if(rval==true)  //return true ise oyun biter
                exit(0);
            getLivingCells();  //hamle sonrasi livingCell artirma
            
            cout<<"Please make your move first player (A, B, C etc.)";
            rval=makeMoveUser('X',typeGame);
            if(rval == true)  //return true ise oyundan cikar
                exit(0);
            getLivingCells();  //hamle sonrasi livingCell artirma
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
        getLivingCells();   //hamle sonrasi livingCell artirma

        //for computer(user2)
        cout<<"\nComputer made move: ";
        
        play();
        rval=gameEnded('O', typeGame);
        if(rval==true)
        {
            printBoard();
            exit(0);
        }
        printBoard();   //boardu print etme
        getLivingCells();   //cell sayisini arttırma
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
                    getLivingCells();   //hamle sonrasi livingCell artirma
                    if(rval == true)
                        exit(0);
                    
                    cout<<"Please make your move second player (A, B, C etc.)";
                    rval=makeMoveUser('O',typeGame);
                    if(rval == true)
                        exit(0);
                    getLivingCells();   //hamle sonrasi livingCell artirma
                    cout<<endl<<"LivingCell: "<<livingCells<<endl;
                    
                }
                //for second player
                else if(ch=='O')
                {   /*2.oyuncudan oynamaya devam edilir*/
                    cout<<"Please make your move second player (A, B, C etc.)";
                    rval=makeMoveUser('O',typeGame);
                    if(rval==true)  //oyun bittiyse true return eder
                        exit(0);
                    getLivingCells();   //hamle sonrasi livingCell artirma
                    /*first player */
                    cout<<"Please make your move first player (A, B, C etc.)";
                    rval=makeMoveUser('X',typeGame);
                    if(rval == true) //oyun bittiyse return true
                        exit(0); 
                    getLivingCells();   //hamle sonrasi livingCell artirma
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
                getLivingCells();  //hamle sonrasi livingCell artirma

                //for computer(user2)
                cout<<"\nComputer made move: ";
                
                play();
                rval=gameEnded('O', typeGame); //oyunun bitip bitmedigini check etme
                if(rval==true)
                {
                    printBoard();
                    exit(0);
                }

                printBoard();  //boardu print etme
                getLivingCells();   //hamle sonrasi livingCell artirma
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

/* This function that returns if the game ended. 
 * Return Value: bool if game ends return true */
bool ConnectFour::gameEnded(char ch, char typeGame)
{
    bool stop=false;
  
    stop=horizontalCheck(ch,typeGame);  //yatayi check etme
    if(stop == true)
        return true;
    
    stop=verticalCheck(ch,typeGame);  //dikeyi check etme
    if(stop == true)
        return true;
    
    stop=crossCheck(ch,typeGame);  //carpraz check
    if(stop == true)
        return true;
    
    stop=checkTiedGame();   //oyunun berabere bitisini check etme
    
    if(stop == true)
        return true;
    
    return false;  //eger oyun bitmezse false return eder
    
}

int ConnectFour::getLivingCells()
{
    livingCells++;  //number of cell
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

/*Compare two Cell objects*/
bool ConnectFour::Cell::operator ==(const Cell& other) const
{
    return (this->GetContent()== other.GetContent());
}
/*Stream insertion operatoru, Cell'in contentini ve koordinatlarini ekrana basar.*/
ostream& operator <<(ostream& out, const ConnectFour::Cell& obj)
{
    out<<endl<<"Content: "<< obj.GetContent()<< " pos_x: "<< obj.GetPosition_x()<<
            " pos_y: "<< obj.GetPosition_y()<<endl;
    
    return out;  //returns a reference
}
/*Stream extraction operatoru, Cell'in contentini ve koordinatlarini kullanıcıdan alir*/
istream& operator >>(istream& in,ConnectFour::Cell& obj)
{
    char ch;
    int x,y;
    cout<<"Enter Cell Content: ";
    in>>ch;    //enter from user game content
    obj.SetContent(ch);
    cout<<"Enter cell positions: ";
    in>>x;    //enter from user x position
    obj.SetPosition_x(x);
    cout<<" ";
    in>>y;     //enter from user y position
    obj.SetPosition_y(y);
    
    return in;  //returns a reference
}
/*Compare two objects, ConnectFour friend func.*/
bool operator == (const ConnectFour& obj1, const ConnectFour& obj2)
{
    bool rval1=false, rval2=false;
    /*Two objects compare the filename, row, column and game type*/
    if( (obj1.getFilename() ==obj2.getFilename()) && 
           (obj1.getColumn()== obj2.getColumn()) && 
          (obj1.getRow()== obj2.getRow()) &&
          (obj1.getGameType()== obj2.getGameType()) )
    {
        rval1=true;  //if they same thing return true
    }
    if(rval1 ==true)
    {   
        /*eger row ve colu esitse iki objeninde gameBoard'a bakilir*/
        for (int i = 0; i < obj1.getRow(); i++)
        {
            for(int j=0; j<obj1.getColumn(); ++j)
            {
                /*GameBoard icerikleri esit mi diye bakilir*/
                if(obj1.gameBoard[i][j] == obj2.gameBoard[i][j])
                    rval2= true;
                else
                {
                    rval2=false; /*esit olmadigi an false döndürüp dönguden cıkar*/
                     break;
                }
            }
        }
    }
    if(rval1==true && rval2==true) //her seyleri esit ise true return eder
        return true;
    else 
        return false;       //degilse false return eder
    
}
/*Compare two objects, ConnectFour friend func.*/
bool operator !=(const ConnectFour& obj1, const ConnectFour& obj2)
{
    return !(obj1==obj2);  //return bool value
}

ConnectFour::Cell::cellState ConnectFour::Cell::operator ++(int ignoreMe) //postfix version
{
    int rval=getState();  //integer artirmasi
    if(rval> 4) //comuter'dan sonra empty gecme
    {
        state=0;
        rval=0; 
    }
    cellState temp;
    temp= myState;  //gecici enum olusturup onu return edicem
    myState = static_cast<cellState>(rval);  // cell state artirilir
    
    return temp;  //kopyasi return edilir
    
}

ConnectFour::Cell::cellState ConnectFour::Cell::operator ++() //prefix version
{
    int rval=getState(); 
    if(rval ==4) // computer to empty
    {
        rval=0;
        state=0;
    }
    myState = static_cast<cellState>(rval);
    
    return myState;   //enum return etme
}

int ConnectFour::Cell::getState()
{
    ++state;
    return state;
}

