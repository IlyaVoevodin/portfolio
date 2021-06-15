#ifndef _LEXER_H
#define _LEXER_H

#include <iostream> 
#include <sstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include <fstream>

using namespace std;

class Lexer {
public:
	int AllTableRowSize;
	int AllTableClmnSize;

	char** tableToken;
	int indexTableToken;

	int** TokenPosition;
	int positionIndex;

	char** constTable;
	int* constCodeTable;
	int indexConstTable;

	char** identifierTable;
	int* idnCodeTable;
	int indexIdentTable;

	string* log;
	int indexLog;

	int* SymbolCategories;
	char reservWord[5][20] = { "0 PROGRAM","1 BEGIN","2 END","3 DEFFUNC", NULL };
	int idnResWord[5] = { 401, 402, 403, 404, NULL };

	int Constant;
	int Idn;

	int clmn;
	int clmnCount;
	int rowCount;
	int CommRowPos;
	int CommClmnPos;

	char* resw;
	char* tok;

	Lexer(int row, int column);
	~Lexer();

	void SymSort();
	void divideToken(char sym, ifstream& file);
};

#endif // _LEXER_H

