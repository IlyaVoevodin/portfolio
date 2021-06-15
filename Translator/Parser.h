#ifndef _PARSER_H
#define _PARSER_H

#include "ParserTree.h"

class Parser {
public:
	int tokenCodePosition = 0;
	int** TableCodePosition;
	char** TokenTable;
	int LastRow;
	int LastClmn;
	stringstream parserErrInfo;

	treeSignal Sig;
	treeProg Prog;
	treeBlock MainBlock;
	treeDeclarations AllDeclarations;
	treeMathFunc MathFunc;
	treeFuncList* FuncLists;
	treeFunc FuncTMP;
	treeFuncChar FuncCharTMP;

	treeFuncList* LastList;
	treeFunc NullFunc;
	treeFuncChar NullFuncChar;

	treeFuncList* createHead(treeFuncList** List, bool EmptyFlag);
	treeFuncList* addNode(treeFuncList** List, bool EmptyFlag);
	bool funcExist;

	Parser(int row, int clmn, int** tokPosition, char** TokenCodTable, int lastRow, int lastClmn);

	void Signal();
	bool ProgStart();
	bool Block();
	bool Declarations();
	bool MathFunction();
	bool FuncList();
	bool Func();
	bool FuncCharcteristic();
	bool Const();
	bool Identifier();
	bool Empty();
	bool EmptyMathFunc();
};

#endif // _PARSER_H
