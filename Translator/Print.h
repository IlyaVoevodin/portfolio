#ifndef _PRINT_H
#define _PRINT_H
#include <iostream>
#include <fstream>

using namespace std;

#pragma warning(disable : 4996)

int printCodingTable(int** tokenPosition, char** Token, string* ErrorLog, int indexErr, char* testPath);
int printConst_IdnTable(char** ConstTable, char** IdnTable, char* testPath);
int printParserTable(char* testPath, struct treeSignal PrSig, struct treeProg MainProg, struct treeBlock PrBlock, struct treeDeclarations PrDeclar, struct treeMathFunc PrMathFunc, struct treeFuncList* PrFuncList);
char** testPath(char** argv);

#endif // !_PRINT_H
