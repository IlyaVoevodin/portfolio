#ifndef _CODE_GENERATOR_H
#define  _CODE_GENERATOR_H
#include "Parser.h"

class CodeGenerator {
public:
	int asmRow, asmClmn;
	char** Asm;

	int* IdnCheck;
	int checkIdx;

	string* CodeErrorLog;
	int errIdx;

	string* LexerErrLog;
	string ParserErrLog;

	CodeGenerator(int rows, int clmns, string* LexerErrors,string ParserError);

	void genProg(char* testPath, treeSignal PrSig, treeProg MainProg, treeBlock PrBlock, treeDeclarations PrDeclar, treeMathFunc PrMathFunc, treeFuncList* PrFuncList);
};


#endif // !_CODE_GENERATOR_H

