target:
	flex java.l
	bison -d java.ypp
	g++ lex.yy.c java.tab.cpp -o myASTGenerator