all:
	bison -d src/java.ypp
	flex src/java.l
	g++ -std=c++11 lex.yy.c java.tab.cpp -o bin/3acgen
	
clean:
	rm lex.yy.c
	rm java.tab.cpp
	rm java.tab.hpp
	rm bin/3acgen
