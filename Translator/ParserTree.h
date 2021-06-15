#ifndef _PARSERTREE_H
#define _PARSERTREE_H
#include "Lexer.h"
#define cnst 100

struct TokenInfo
{
	int row = 0;
	int clmn = 0;
	int code = 0;
	char value[cnst] = {};
};

struct treeFuncChar
{
	int treeLVL;
	string FuncCharName;

	TokenInfo BackSlash;
	TokenInfo FirstConst;
	TokenInfo Coma;
	TokenInfo SecondConst;

	string ErrorLog;
};

struct treeFunc
{
	int treeLVL;
	string FuncName;
	string FuncIDN_Name;
	string IDN_Name;
	
	TokenInfo FuncIDN;
	TokenInfo Equ;
	TokenInfo Constant;
	TokenInfo Semicolon;
	treeFuncChar FuncCharacteristic;

	string ErrorLog;
};

struct treeFuncList
{
	int treeLVL;
	string FuncListName;
	string Empty;
	treeFunc AnotherFunc;
	treeFuncList* AnotherList;
};

struct treeMathFunc
{
	int treeLVL;
	string MathFuncName;
	string Empty;

	TokenInfo Deffunc;
	treeFuncList* FunctionList;

	string ErrorLog;
};

struct treeDeclarations
{
	int treeLVL;
	string DeclarationsName;
	treeMathFunc* MathFunctions;
};

struct treeBlock
{
	int treeLVL;
	string BlockName;
	string StatementsList;
	string Empty;

	TokenInfo Begin;
	TokenInfo End;
	treeDeclarations* Declaration;

	string ErrorLog;
};

struct treeProg
{
	int treeLVL;

	string ProgName;
	string ProgIDN_Name;
	string IDN_Name;

	TokenInfo Program;
	TokenInfo ProgIDN;
	TokenInfo Semicolon;
	TokenInfo Point;
	treeBlock* ProgBlock;

	string ErrorLog;
};

struct treeSignal
{
	string SigName;
	treeProg* StartProg;
};

#endif