all: hello

hello: main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o Cell.o
	g++ main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o Cell.o -o exe

main.o: main.cpp
	g++ -c main.cpp -std=c++11

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -c ConnectFourAbstract.cpp -std=c++11

ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -c ConnectFourPlus.cpp -std=c++11

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -c ConnectFourDiag.cpp -std=c++11

ConnectFourPlusUndo.o: ConnectFourPlusUndo.cpp
	g++ -c ConnectFourPlusUndo.cpp -std=c++11

Cell.o: Cell.cpp
	g++ -c Cell.cpp -std=c++11

clean:
	rm *.o exe
