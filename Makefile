all: proj3.exe

proj3.o: proj3.cpp checkMenuChoice.h ColorImageClass.h
	g++ -std=c++98 -pedantic -Wall -c proj3.cpp -o proj3.o

checkMenuChoice.o: checkMenuChoice.cpp checkMenuChoice.h
	g++ -std=c++98 -pedantic -Wall -c checkMenuChoice.cpp -o checkMenuChoice.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h
	g++ -std=c++98 -pedantic -Wall -c RowColumnClass.cpp -o RowColumnClass.o

ColorClass.o: ColorClass.cpp ColorClass.h checkMenuChoice.h
	g++ -std=c++98 -pedantic -Wall -c ColorClass.cpp -o ColorClass.o

RectangleClass.o: RectangleClass.cpp RectangleClass.h ColorClass.h RowColumnClass.h checkMenuChoice.h
	g++ -std=c++98 -pedantic -Wall -c RectangleClass.cpp -o RectangleClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h ColorClass.h RowColumnClass.h RectangleClass.h PatternClass.h constants.h
	g++ -std=c++98 -pedantic -Wall -c ColorImageClass.cpp -o ColorImageClass.o

PatternClass.o: PatternClass.cpp PatternClass.h checkMenuChoice.h ColorClass.h RowColumnClass.h RectangleClass.h
	g++ -std=c++98 -pedantic -Wall -c PatternClass.cpp -o PatternClass.o

proj3.exe: RowColumnClass.o ColorClass.o ColorImageClass.o checkMenuChoice.o RectangleClass.o PatternClass.o proj3.o
	g++ -std=c++98 RowColumnClass.o ColorClass.o ColorImageClass.o proj3.o checkMenuChoice.o RectangleClass.o PatternClass.o -o proj3.exe

clean:
	rm -f *.o *.exe