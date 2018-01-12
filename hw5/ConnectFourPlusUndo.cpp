//This is the implementation for the class ConnectFourPlusUndo.
//This is the file ConnectFourPlusUndo.cpp.
//The interface for the class ConnectFourPlusUndo is in the header file
//ConnectFourPlusUndo.h

#include "ConnectFourPlusUndo.h"


const int FOUR = 4;  //minumum row and col 
const int ZERO= 0;
const int ONE =1;

using namespace std;

namespace Game
{
    ConnectFourPlusUndo::ConnectFourPlusUndo(): ConnectFourPlus()
    {
        /*Body intentionally empty*/
    }

    ConnectFourPlusUndo::ConnectFourPlusUndo(int theRow, int theCol):ConnectFourPlus(theRow,theCol)
    {
        /*Body intentionally empty*/
    }
    int ConnectFourPlusUndo::play(string cellPosition)
    {
        int i=ZERO,firstIndex=ZERO,control=ZERO;
        const string saveCheck="SAVE";
        const string loadCheck="LOAD";
        const string undoCheck="UNDO";
        char ch= getUserContent();
        string move="";
        bool stop=false;
        

        /*Check move input for save, load or undo*/
        if(cellPosition== saveCheck && getFilename().length() != ZERO)
        {
            saveFunction(ch); //for save
            moveCheck(move,ch);
            control=ONE;
        }
        else if(cellPosition == loadCheck && getFilename().length()!= ZERO)
        {
            stop=loadFunction();  //for load
            if(stop == true)
                return 1;
            moveCheck(move,ch);
            control=ONE;
        }
        else if(cellPosition== undoCheck && getFilename().length()==ZERO)
        {
            stop=undo();   //for undo
            if(stop== 0)
                return 0;
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
            copyBoard();
            control=ONE;
        }
        return control;
    }
    int ConnectFourPlusUndo::undo()
    {
        int rw= getRow();
        int cl= getColumn();
        eachMoveHolder.pop_back(); // son hamlenin oldugu board vektorden cikarilir 
        int lastElem = eachMoveHolder.size();
        
        if(lastElem == ZERO)
        {
            cerr<<"UNDO cannot be do!\n"; //undo yapılamaz ise return 0 
            return 0;
        }
        else
        {
            for (int i = 0; i < rw; i++)
            {
                for(int j=0 ; j< cl; ++j)
                {
                    gameBoard[i][j]= eachMoveHolder[lastElem-1][i][j];
                }
            }
            return ONE;
        }
    }
    
    void ConnectFourPlusUndo::copyBoard()
    {
        int rw=getRow();  //rowu atama
        int cl=getColumn();   //gameBoard'un columnu atama
       
        vector< vector <Cell> > gameCells; 
        /*initialiaze vector*/
        for (int i = 0; i < rw; i++)
        {
            vector<Cell> rowCells; 
            for(int j=0; j< cl; ++j)
            {
                rowCells.push_back(gameBoard[i][j]);
            }
            gameCells.push_back(rowCells);
        }
        eachMoveHolder.push_back(gameCells); //her hamle vektore eklenir
    }
    void ConnectFourPlusUndo::moveCheck(string move, char ch)
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
             if(move.length()==0)  //dosya sonu EOF checki
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
        copyBoard(); /*hamle sonrasi tahta vektore kopyalanir*/
    }
    
    void ConnectFourPlusUndo::initializeBoard()
    {
        for(int i=0; i< getRow(); ++i)
        {
            for(int j=0; j<getColumn(); ++j )
            {   
                gameBoard[i][j].SetContent('.'); //board initialize edilir
            } 
        }     
        copyBoard();  /*gameBoard'un ilk hali vektore kopyalanir*/
    }
    
    void ConnectFourPlusUndo::saveFunction(char ch)
    {
        ofstream myOut;
        myOut.open(getFilename());
        if(myOut.fail())  //eger kaydetmek icin dosya olusturalamaz ise
        {
            cerr<<"Output file opening failed.\n";
            exit(1);  //in cstdlib library
        }
        cout<<"The game saved in "<<getFilename()<<endl;
        myOut<< getRow()<< endl<<getColumn()<<endl;  //row ve colu yazma
        myOut<<getGameType()<<endl;    //game tipini yazma P or C
        myOut<<ch<<endl;   // X or O

        int size= eachMoveHolder.size();
        myOut<<size<<endl;
        
        for(int a=0; a<size; ++a)
        {
            for(int i=0; i<getRow(); ++i)
            {
                for(int j=0; j<getColumn() ; ++j)
                {
                    myOut<< eachMoveHolder[a][i][j].GetContent();
                }
                myOut<<endl;
            }
        }
    }
    
    bool ConnectFourPlusUndo::loadFunction()
    {
        ifstream fin;
        char ch;
        string type,temp;
        int rw,cl, size;
        fin.open(getFilename());  //load yapılacak dosyayı acma
        bool stop = false;
        string line;
        char **chr;    //read char to file
        char cont;
        
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
        
        fin>>size;
        eachMoveHolder.clear();  //vektoru sifirlama
        
        getline(fin,temp);
        int a=0;
        while( a < size )
        {
            chr = new char *[getRow()];
            for (int i = 0; i < getRow(); i++) 
                chr[i]= new char[getColumn()];
            
            for (int i = 0; i<getRow(); i++)
            {
                getline(fin,line);
                for(int j=0; j< getColumn(); ++j)
                    chr[i][j]= line[j];
            }

            vector< vector <Cell> > gameCells; //gecici vektor olusturma
            for(int i=ZERO; i<getRow(); ++i)
            {
                vector<Cell> rowCells; 
                for(int j=ZERO; j<getColumn(); ++j)
                {
                    Cell tmp;
                    char t= chr[i][j];
                    tmp.SetContent(t);
                    rowCells.push_back(tmp);
                }
                gameCells.push_back(rowCells);
            }
            eachMoveHolder.push_back(gameCells); //her hamle vektore eklenir
            
            ++a;
        }
        
        size = eachMoveHolder.size();
        for(int i=0; i< getRow(); ++i)
        {
            for (int j = 0; j < getColumn(); j++)
            {
                gameBoard[i][j]=eachMoveHolder[size-1][i][j];  //gameBoardu doldurma
            }
        }
        
        cout<<"The game loaded from file "<<getFilename()<<endl;
        printBoard();   //Boardun son halini print etme
        fin.close();    //dosyayi kapatma
       
        stop=afterGameLoaded(type[0],ch);  //END check
        if(stop== true)
            return true;
        
        for(int i = 0; i < getRow(); ++i)  //delete chr 
            delete [] chr[i];

        delete [] chr;  //freestore
      
        return false;
    }
}