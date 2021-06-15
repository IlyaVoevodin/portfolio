#include "Code_generator.h"

CodeGenerator::CodeGenerator(int rows, int clmns, string* LexerErrors, string ParserError)
{
	Asm = new char* [rows];
	asmRow = 0;
	asmClmn = 0;

	IdnCheck = new int [rows];
	checkIdx = 0;

	CodeErrorLog = new string[rows];
	errIdx = 0;

	LexerErrLog = LexerErrors;
	ParserErrLog = ParserError;

	for (int i = 0; i < rows; i++)
	{
		Asm[i] = new char[clmns];
		IdnCheck[i] = NULL;
		for (int j = 0; j < clmns; j++)
		{
			Asm[i][j] = NULL;
		}
	}
}

void CodeGenerator::genProg(char* testPath,treeSignal PrSig, treeProg MainProg, treeBlock PrBlock, treeDeclarations PrDeclar, treeMathFunc PrMathFunc, treeFuncList* PrFuncList)
{
	ofstream lst;
	stringstream fullErr;
	bool flag;
	lst.open(testPath);
	
	
	if (MainProg.ErrorLog == "")
	{
		cout << "DATA_" << MainProg.ProgIDN.value << "\t SEGMENT byte\n";
		lst << "DATA_" << MainProg.ProgIDN.value << "\t SEGMENT byte\n";

		if ((PrMathFunc.Empty == "")&&(PrMathFunc.ErrorLog == ""))
		{
			treeFuncList* p = PrFuncList;
			while (p)
			{
				if ((p->Empty == "")&&(p->AnotherFunc.ErrorLog == "")&&(p->AnotherFunc.FuncCharacteristic.ErrorLog == "")) 
				{
					flag = false;
					for (int i = 0; IdnCheck[i]; i++)
					{
						if (p->AnotherFunc.FuncIDN.code == IdnCheck[i])
						{
							fullErr << "Code Generator: Error( Name of math function '" << p->AnotherFunc.FuncIDN.value << "' at [R:" << p->AnotherFunc.FuncIDN.row 
								<< "][C:" << p->AnotherFunc.FuncIDN.clmn << "] must be unique!)\n";
							CodeErrorLog[errIdx] = fullErr.str();
							fullErr.str("");
							errIdx++;
							p->AnotherFunc.FuncIDN.code = -1;
							flag = true;
							break;
						}
					}

					if (atoi(p->AnotherFunc.FuncCharacteristic.SecondConst.value) < 1)
					{
						fullErr << "Code Generator: Error( Value of second index '" << p->AnotherFunc.FuncCharacteristic.SecondConst.value << "' at [R:" << p->AnotherFunc.FuncCharacteristic.SecondConst.row
							<< "][C:" << p->AnotherFunc.FuncCharacteristic.SecondConst.clmn << "] can't be less then 1!)\n";
						CodeErrorLog[errIdx] = fullErr.str();
						fullErr.str("");
						errIdx++;
						p->AnotherFunc.FuncIDN.code = -1;
						flag = true;
					}

					if (flag == false)
					{
						cout << "  " << p->AnotherFunc.FuncIDN.value << "\t\t " << atoi(p->AnotherFunc.FuncCharacteristic.SecondConst.value) + 1 << " DUP (?)\n";
						lst << "  " << p->AnotherFunc.FuncIDN.value << "\t\t " << atoi(p->AnotherFunc.FuncCharacteristic.SecondConst.value) + 1 << " DUP (?)\n";
					}
					IdnCheck[checkIdx] = p->AnotherFunc.FuncIDN.code;
					checkIdx++;
				}
				p = p->AnotherList;
			}
		}

		cout << "DATA_"<< MainProg.ProgIDN.value <<"\t ENDS\n\nCODE_"<< MainProg.ProgIDN.value <<"\t SEGMENT\n";
		lst << "DATA_" << MainProg.ProgIDN.value << "\t ENDS\n\nCODE_" << MainProg.ProgIDN.value <<"\t SEGMENT\n";

		if ((PrMathFunc.Empty == "")&&(PrMathFunc.ErrorLog == ""))
		{
			treeFuncList* f = PrFuncList;
			int label = 1;
			while (f)
			{
				if ((f->Empty == "")&&(f->AnotherFunc.ErrorLog == "")&&(f->AnotherFunc.FuncCharacteristic.ErrorLog == "")&&(f->AnotherFunc.FuncIDN.code != -1))
				{
					if (atoi(f->AnotherFunc.FuncCharacteristic.FirstConst.value) > atoi(f->AnotherFunc.FuncCharacteristic.SecondConst.value))
					{
						fullErr << "Code Generator: Error( First index '" << f->AnotherFunc.FuncCharacteristic.FirstConst.value << "' at [R:" << f->AnotherFunc.FuncCharacteristic.FirstConst.row 
							<<"][C:" << f->AnotherFunc.FuncCharacteristic.FirstConst.clmn << "] cant't be greater then second index)\n";
						CodeErrorLog[errIdx] = fullErr.str();
						fullErr.str("");
						errIdx++;
						break;
					}
					else
					{
						cout << "\t MOV\t ECX," << f->AnotherFunc.FuncCharacteristic.FirstConst.value << endl;
						lst << "\t MOV\t ECX," << f->AnotherFunc.FuncCharacteristic.FirstConst.value << endl;

						cout << "\t MOV\t EAX," << f->AnotherFunc.FuncCharacteristic.SecondConst.value << endl;
						lst << "\t MOV\t EAX," << f->AnotherFunc.FuncCharacteristic.SecondConst.value << endl;
					}

					cout << "L" << label << "?:\n";
					lst << "L" << label << "?:\n";

					cout << "\t MOV\t " << f->AnotherFunc.FuncIDN.value << "[ECX * 2]," << f->AnotherFunc.Constant.value << endl;
					lst << "\t MOV\t " << f->AnotherFunc.FuncIDN.value << "[ECX * 2]," << f->AnotherFunc.Constant.value << endl;

					cout << "\t ADD\t ECX,1\n\t CMP\t ECX," << f->AnotherFunc.FuncCharacteristic.SecondConst.value << endl;
					lst << "\t ADD\t ECX,1\n\t CMP\t ECX, " << f->AnotherFunc.FuncCharacteristic.SecondConst.value << endl;

					cout << "\t JLE\t L"<< label << "?\n";
					lst << "\t JLE\t L"<<label<<"?\n";
					label++;
				}
				f = f->AnotherList;
			}
		}

		if (PrBlock.Begin.code != NULL)
		{
			cout << PrBlock.Begin.value << ":\n";
			lst << PrBlock.Begin.value << ":\n";
		}

		cout << "CODE_" << MainProg.ProgIDN.value << "\t ENDS\n";
		lst << "CODE_" << MainProg.ProgIDN.value << "\t ENDS\n";

		if ((PrBlock.Begin.value != NULL)&&(PrBlock.End.value != NULL))
		{
			cout << "\t\t " << PrBlock.End.value << "\t " << PrBlock.Begin.value << "\n";
			lst << "\t\t " << PrBlock.End.value << "\t " << PrBlock.Begin.value << "\n";
		}
	}

	for (int i = 0; LexerErrLog[i] != ""; i++)
	{
		cout << LexerErrLog[i] << endl;
		lst << LexerErrLog[i] << endl;
	}

	if (ParserErrLog != "")
	{
		cout << ParserErrLog << endl;
		lst << ParserErrLog << endl;
	}

	for (int i = 0; CodeErrorLog[i] != ""; i++)
	{
		cout << CodeErrorLog[i];
		lst << CodeErrorLog[i];
	}
	lst.close();
}