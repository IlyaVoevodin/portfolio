#include "Code_generator.h"
#include "Print.h"

int main(int argc, char** argv) {
	ifstream fileIn;
	const int tableRow = 100, tableColumn = 100;

	char** Path = testPath(argv);

	for (int var = 0; Path[var]; var++) {
		if (Path[var] == NULL)
			return 0;
		fileIn.open(Path[var]);
		if (fileIn.is_open()) {
			cout << "File " << (var + 2) / 2 << "(input.sig) OK!\n\n";
		}
		else {
			cout << "File " << (var + 2) / 2 << "(input.sig) error!\n\n";
			return(0);
		}
		var++;
		
		Lexer LA(tableRow, tableColumn);
		
		char ch = '0';
		LA.SymSort();

		while (ch) {
			fileIn.get(ch);
			if (fileIn.eof()) {
				LA.divideToken(EOF, fileIn);
				break;
			}
			else {
				LA.divideToken(ch, fileIn);
			}
		}
		
		Parser PA(tableRow, tableColumn, LA.TokenPosition, LA.tableToken, LA.rowCount, LA.clmnCount);
		PA.Signal();

		//printCodingTable(LA.TokenPosition, LA.tableToken, LA.log, LA.indexLog, Path[var]);
		//printConst_IdnTable(LA.constTable, LA.identifierTable, Path[var]);
		
		//printParserTable(Path[var], PA.Sig, PA.Prog, PA.MainBlock, PA.AllDeclarations, PA.MathFunc, PA.FuncLists);

		CodeGenerator CG(tableColumn, tableRow, LA.log, PA.parserErrInfo.str());
		CG.genProg(Path[var], PA.Sig, PA.Prog, PA.MainBlock, PA.AllDeclarations, PA.MathFunc, PA.FuncLists);
		
		fileIn.close();
	}
	
	return(0);
}
