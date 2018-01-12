//This is the implementation for the class ConnectFourAbstract.
//This is the file ConnectFourAbstract.cpp.
//The interface for the class ConnectFourAbstract is in the header file
//ConnectFourAbstract.h

#include "ConnectFourAbstract.h"
#include <iostream>
#include <cstdlib>  //for exit function
#include <string>
#include <sstream>  //for ching invalid input -- std::istringstream
#include <fstream>

const int FOUR = 4;  //minumum row and col 
const int ZERO= 0;
const int ONE =1;

using namespace std;

namespace Game
{
    /*No parameter constructor*/
    ConnectFourAbstract::ConnectFourAbstract():row(4), column(4)
    {
        /*Body intentionally empty  */
    }
    ConnectFourAbstract::ConnectFourAbstract(int myRow, int myCol)
    {
        setRow(myRow);
        setColumn(myCol);
    }

    ConnectFourAbstract::ConnectFourAbstract(string paramFilename)
    {
        setFilename(paramFilename);
    }
    
     /*Destructor for ConnectFourAbstract class*/
    ConnectFourAbstract::~ConnectFourAbstract()
    {
        for(int i = 0; i < getRow(); ++i)  //delete gameBoard 
            delete [] gameBoard[i];

        delete [] gameBoard;  //freestore
    }
   /*Assignment operator for connectFourAbstract class..*/
    ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& other)
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

    /*Copy constructor for ConnectFourAbstract Class */
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& other): 
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
    void ConnectFourAbstract::setUserContent(char userContent) {
        this->userContent = userContent;
    }

    char ConnectFourAbstract::getUserContent() const {
        return userContent;
    }

    void ConnectFourAbstract::setGameType(string gameType) {
        this->gameType = gameType;
    }

    string ConnectFourAbstract::getGameType() const {
        return gameType;
    }
    
     /*Setter for filename for load and save operation*/
    void ConnectFourAbstract::setFilename(string filename)
    {
        this->filename = filename;
    }
    /*Getter for filename*/
    string ConnectFourAbstract::getFilename() const
    {
        return filename;
    }

    void ConnectFourAbstract::moveCheck(string move, char ch)
    {
        int firstIndex=ZERO;

        cout<<"Please make your move  (A, B, C etc.)! ";
        getline(cin,move);  //kullanıcıdan move alma
        while((firstIndex=move[ZERO]-'A') >= getColumn() 
                || (firstIndex=move[ZERO]-'A')<ZERO 
                || gameBoard[ZERO][firstIndex].GetContent()=='X' 
                || gameBoard[ZERO][firstIndex].GetContent()== 'O') 
        {
            cerr<<"Invalid move, please try again!"<<endl;
            cout<<"Please make your move  (A, B, C etc.)! ";
            getline(cin,move);
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
    
    void ConnectFourAbstract::initializeBoard()
    {
        for(int i=0; i< getRow(); ++i)
        {
            for(int j=0; j<getColumn(); ++j )
            {   
                gameBoard[i][j].SetContent('.'); //board initialize edilir
            } 
        }     
    }
    void ConnectFourAbstract::printBoard() const
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
            if(i+1>=10)  //tek basamaklı sayilar disinda bosluk atma
                cout<< i+1 << " ";
            else
               cout<< i+1 << "  ";
            for(int j=0; j<getColumn(); ++j )
                cout<<" "<<gameBoard[i][j].GetContent()<< " ";
            cout<<endl;
       }
    }
    
    void ConnectFourAbstract::checkBoardSizeInput()
    {
       string r,c;
        int rw,cl, inputRow, inputCol;

        do{
            cout<<"Please enter the board row: ";
            cin >> r;
            if(r.length() == 0)
                exit(1);  //dosya sonu checki 
            std::istringstream (r) >> rw;
            setRow(rw);
            inputRow= getRow();

            if(inputRow ==ZERO || inputRow<FOUR)
                cerr<<"Invalid input! "<<endl;
                

        }while(inputRow ==ZERO || inputRow<FOUR );

        do{
            cout<<"Please enter the board column: ";
            cin>> c;
            if(c.length() == 0)
                exit(1); //dosya sonu checki 
            std::istringstream (c) >> cl;
            setColumn(cl);

            inputCol=getColumn();

            if( inputCol==ZERO || inputCol<FOUR || inputCol>26)
                cerr<<"Invalid input! "<<endl;

        }while(inputCol==ZERO || inputCol<FOUR || inputCol>26 );

        cout<<"Board size entered as: (Row:"<<getRow()<<",Col:"<<getColumn()<<")"<< endl;
    }
    
    void ConnectFourAbstract::createDynamicArray(int theRw, int theCl)
    {
        gameBoard= new Cell *[theRw];
        for (int i = 0; i < theRw; i++) 
            gameBoard[i]= new Cell[theCl];
    }

    void ConnectFourAbstract::setKindOfGame(char kindOfGame) {
        this->kindOfGame = kindOfGame;
    }

    char ConnectFourAbstract::getKindOfGame() const {
        return kindOfGame;
    }
    /*Berabere bitme durumunu check etme, eger tahta dolduysa berabere biter. */
    bool ConnectFourAbstract::checkTiedGame() const
    {
        int counter=ZERO;
        int col=getColumn();  //getter for col
        int row=getRow();     //getter for row

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
   /*This function plays the game by asking the user to
         *  play and the computer plays*/
    int ConnectFourAbstract::playGame()
    {
        int i=0;
        checkBoardSizeInput();  
        createDynamicArray(getRow(),getColumn());
        initializeBoard();   //tahtayi initialie etme
        string type="";
        string input="";
        bool rval= false;

        cout<< "Do you want to play 2 player(P) vs computer games(C):";
        cin >> type;
        setGameType(type);
        printBoard();       //tahtayi ekrana basma
        string typeOfGame= getGameType();  //gameTye P or C

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
                    if(rval == true)
                        break;
                    //for second player
                    cout<<"Please make your move second player (A, B, C etc.)";
                    setUserContent('O');
                    rval =makeMoveUser('O',typeOfGame[0]);
                    if(rval == true)
                        break;
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
                    if(rval == true)
                        break;

                    //for computer(user2)
                    cout<<"\nComputer made move: ";
                    play();
                    rval=gameEnded('O', typeOfGame[0]);
                    printBoard();  //tahtanın son halini print etme
                    if(rval == true)
                        break;
                }
            }
            else  //error durumu
            {
                cerr<<"Invalid input!\n";
                cout<<"Please press P or C: ";
                cin>>typeOfGame;
            }
        }
        return 0;
    }
    //its play the computer
    int ConnectFourAbstract::play()
    {
        int i=0, j=0;
        int col= getColumn();  //getter for column
        int row=getRow();
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
                                    i=j=-1; break;  //exit nested loop
                                }
                                else
                                {
                                    gameBoard[i][j-1].SetContent('O');
                                    cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                    i=j=-1; break;  //exit nested loop
                                }
                            }
                            else if(gameBoard[i][j+1].GetContent()=='.' && j+1<col)
                            {
                                if(i-1>=0 && gameBoard[i-1][j].GetContent()!='.')
                                {
                                    gameBoard[i][j+1].SetContent('O');
                                    cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                    i=j=-1; break; //exit nested loop
                                }
                            }
                        }
                        else
                        {
                            if(gameBoard[i][j-1].GetContent()=='.' && j-1>=0 )
                            {
                                if(i+1<row && gameBoard[i+1][j-1].GetContent()!='.')
                                {
                                    gameBoard[i][j-1].SetContent('O');
                                    cout<<static_cast<char>(j-1+'A')<<endl<<endl;
                                    i=j=-1; break; //exit nested loop
                                }
                            }
                            if(gameBoard[i][j+1].GetContent()=='.' && j+1<col )
                            {
                                if(i+1<row && gameBoard[i+1][j+1].GetContent()!='.' )
                                {
                                    gameBoard[i][j+1].SetContent('O');
                                    cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                    i=j=-1; break;  //exit nested loop
                                }
                                else if(i+1==row)
                                {
                                    gameBoard[i][j+1].SetContent('O');
                                    cout<<static_cast<char>(j+1+'A')<<endl<<endl;
                                    i=j=-1; break;  //exit nested loop
                                }
                            }
                            if(gameBoard[i-1][j].GetContent()=='.' && i-1>=0)
                            {
                                gameBoard[i-1][j].SetContent('O');
                                cout<<static_cast<char>(j+'A')<<endl<<endl;
                                i=j=-1; break; //exit nested loop
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
    
    int ConnectFourAbstract::play(string cellPosition)
    {
        int i=ZERO,firstIndex=ZERO,control=ZERO;
        const string saveCheck="SAVE";
        const string loadCheck="LOAD";
        char ch= getUserContent();
        string move="";
        bool stop=false;

        /*Checking move input */
        if(cellPosition== saveCheck && getFilename().length() != ZERO)
        {
            saveFunction(ch);    //save check
            moveCheck(move,ch);
            control=ONE;
        }
        else if(cellPosition == loadCheck && getFilename().length()!= ZERO)
        {
            stop=loadFunction();  //load check
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
    /*Loads the game board from filename*/
    bool ConnectFourAbstract::loadFunction()
    {
        ifstream fin;
        char ch,cont;
        string type,temp;
        int rw,cl;
        fin.open(getFilename());  //load yapılacak dosyayı acma
        bool stop = false;
        string line;
        char **chr;    //read char to file

        if(fin.fail())  //eger dosya acilamaz ise
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
        cout<<"The game loaded from file "<<getFilename()<<endl;
        printBoard();
        fin.close();
       
        stop=afterGameLoaded(type[0],ch);
        if(stop== true)
            return true;
      
        return false;
    }
    
    void ConnectFourAbstract::saveFunction(char ch)
    {
        ofstream fout;
        fout.open(getFilename());
        if(fout.fail())  //eger kaydetmek icin dosya olusturalamaz ise
        {
            cerr<<"Output file opening failed.\n";
            exit(1);  //in cstdlib library
        }
        cout<<"The game saved in "<<getFilename()<<endl;
        fout<< getRow()<< endl<<getColumn()<<endl;  //row ve colu yazma
        fout<<getGameType()<<endl;    //game tipini yazma P or C
        fout<<ch<<endl;   // X or O

        for(int i=0; i<getRow(); ++i)
        {
            for(int j=0; j<getColumn() ; ++j)
            {
                fout<<gameBoard[i][j].GetContent();
            }
            fout<<endl;
        }
    }
    
    bool ConnectFourAbstract::afterGameLoaded(char typeGame, char ch)
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
                        if(rval == true)
                            exit(0);

                        cout<<"Please make your move second player (A, B, C etc.)";
                        rval=makeMoveUser('O',typeGame);
                        if(rval == true)
                            exit(0);
                    }
                    //for second player
                    else if(ch=='O')
                    {   /*2.oyuncudan oynamaya devam edilir*/
                        cout<<"Please make your move second player (A, B, C etc.)";
                        rval=makeMoveUser('O',typeGame);
                        if(rval==true)  //oyun bittiyse true return eder
                            exit(0);
                        /*first player */
                        cout<<"Please make your move first player (A, B, C etc.)";
                        rval=makeMoveUser('X',typeGame);
                        if(rval == true) //oyun bittiyse return true
                            exit(0); 
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
                    //for computer(user2)
                    cout<<"\nComputer made move: ";
                    play();
                    rval=gameEnded('O', typeGame); //oyunun bitip bitmedigini check etme
                    if(rval==true)
                    {
                        printBoard();  //boardu print etme
                        exit(0);
                    }
                    printBoard();  //boardu print etme
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
    bool ConnectFourAbstract::makeMoveUser(char ch, char type)
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
            setFilename(filename);  //file set etme
            rval = play(firstWord);  //move'u gönderme
        }while(rval == ZERO);

        stopCondition= gameEnded(ch, type); //oyunun bitip bitmedigini check etme
        printBoard();

        return stopCondition;
    }
} //Game