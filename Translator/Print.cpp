#include "Print.h"
#include "ParserTree.h"

int printCodingTable(int** tokenPosition, char** Token, string* ErrorLog, int indexErr, char* testPath)
{
	ofstream outFile;

	outFile.open(testPath);
	if (outFile.is_open()) {
		cout << "File (generated.txt) OK!\n\n";
	}
	else {
		cout << "File (generated.txt) error!\n\n";
		return(0);
	}

	cout << "|  Row   | Column|TokCode| Token  |" << endl;
	outFile << "| Row |Column |TokCode |Token |\n";
	for (int i = 0; Token[i][0]; i++)
	{
		cout << "  " << tokenPosition[i][0] << "\t | " << tokenPosition[i][1] << "\t | " << tokenPosition[i][2] << "\t | ";
		outFile << "   " << tokenPosition[i][0] << " \t " << tokenPosition[i][1] << " \t " << tokenPosition[i][2] << " \t";
		for (int j = 0; Token[i][j]; j++)
		{
			cout << Token[i][j];
			outFile << Token[i][j];
		}
		cout << endl;
		outFile << endl;
	}
	outFile << endl;

	for (int i = 0; i < indexErr; i++)
	{
		cout << ErrorLog[i] << endl;
		outFile << ErrorLog[i].c_str() << endl;
	}
	outFile << endl;

	outFile.close();
}

int printConst_IdnTable(char** ConstTable, char** IdnTable, char* testPath)
{
	ofstream outFile;

	outFile.open(testPath, ios_base::app);
	if (outFile.is_open()) {
		cout << "File (generated.txt) OK!\n\n";
	}
	else {
		cout << "File (generated.txt) error!\n\n";
		return(0);
	}

	outFile << "Constant table \n\n";
	cout << "Constant table" << endl;

	for (int i = 0; ConstTable[i][0]; i++)
	{
		outFile << "\t";
		for (int j = 0; ConstTable[i][j]; j++)
		{
			cout << ConstTable[i][j];
			outFile << ConstTable[i][j];
		}
		cout << endl;
		outFile << endl;
	}
	outFile << "\n\n";

	outFile << "Identifier table \n\n";
	cout << "Identifier table" << endl;

	for (int i = 0; IdnTable[i][0]; i++)
	{
		outFile << "\t";
		for (int j = 0; IdnTable[i][j]; j++)
		{
			cout << IdnTable[i][j];
			outFile << IdnTable[i][j];
		}
		cout << endl;
		outFile << endl;
	}
	outFile << endl;

	outFile.close();
}


int printParserTable(char* testPath, treeSignal PrSig, treeProg MainProg, treeBlock PrBlock, treeDeclarations PrDeclar, treeMathFunc PrMathFunc, treeFuncList* PrFuncList) {
	ofstream outFile;

	outFile.open(testPath);
	if (outFile.is_open()) {
		cout << "File (generated.txt) OK!\n\n";
	}
	else {
		cout << "File (generated.txt) error!\n\n";
		return(0);
	}
	
	cout << PrSig.SigName << endl;
	outFile << PrSig.SigName << endl;

	for (int i = 0; i < MainProg.treeLVL; i++)
	{
		cout << ".";
		outFile << ".";
	}
	cout << MainProg.ProgName << endl;
	outFile << MainProg.ProgName << endl;

	if (MainProg.Program.code != NULL)
	{
		for (int i = 0; i < MainProg.treeLVL + 2; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << MainProg.Program.code << " ";
		outFile << MainProg.Program.code << " ";
		for (int j = 0; MainProg.Program.value[j]; j++)
		{
			cout << MainProg.Program.value[j];
			outFile << MainProg.Program.value[j];
		}
		cout << endl;
		outFile << endl;

		for (int i = 0; i < MainProg.treeLVL + 2; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << MainProg.ProgIDN_Name << endl;
		outFile << MainProg.ProgIDN_Name << endl;

		for (int i = 0; i < MainProg.treeLVL + 4; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << MainProg.IDN_Name << endl;
		outFile << MainProg.IDN_Name << endl;

		if (MainProg.ProgIDN.code != NULL) {
			for (int i = 0; i < MainProg.treeLVL + 6; i++)
			{
				cout << ".";
				outFile << ".";
			}
			cout << MainProg.ProgIDN.code << " ";
			outFile << MainProg.ProgIDN.code << " ";
			for (int j = 0; MainProg.ProgIDN.value[j]; j++)
			{
				cout << MainProg.ProgIDN.value[j];
				outFile << MainProg.ProgIDN.value[j];
			}
			cout << endl;
			outFile << endl;

			if (MainProg.Semicolon.code != NULL)
			{
				for (int i = 0; i < MainProg.treeLVL + 2; i++)
				{
					cout << ".";
					outFile << ".";
				}
				cout << MainProg.Semicolon.code << " " << MainProg.Semicolon.value[0] << endl;
				outFile << MainProg.Semicolon.code << " " << MainProg.Semicolon.value[0] << endl;
			}
			else
			{
				cout << MainProg.ErrorLog << endl;
				outFile << MainProg.ErrorLog << endl;
				outFile.close();
				return 0;
			}
		}
		else
		{
			cout << MainProg.ErrorLog << endl;
			outFile << MainProg.ErrorLog << endl;
			outFile.close();
			return 0;
		}
	}
	else
	{
		cout << MainProg.ErrorLog << endl;
		outFile << MainProg.ErrorLog << endl;
		outFile.close();
		return 0;
	}
	
	for (int i = 0; i < PrBlock.treeLVL; i++)
	{
		cout << ".";
		outFile << ".";
	}
	cout << PrBlock.BlockName << endl;
	outFile << PrBlock.BlockName << endl;

	for (int i = 0; i < PrDeclar.treeLVL; i++)
	{
		cout << ".";
		outFile << ".";
	}
	cout << PrDeclar.DeclarationsName << endl;
	outFile << PrDeclar.DeclarationsName << endl;

	for (int i = 0; i < PrMathFunc.treeLVL; i++)
	{
		cout << ".";
		outFile << ".";
	}
	cout << PrMathFunc.MathFuncName << endl;
	outFile << PrMathFunc.MathFuncName << endl;

	if (PrMathFunc.Deffunc.code != NULL)
	{
		for (int i = 0; i < PrMathFunc.treeLVL + 2; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << PrMathFunc.Deffunc.code << " ";
		outFile << PrMathFunc.Deffunc.code << " ";
		for (int j = 0; PrMathFunc.Deffunc.value[j]; j++)
		{
			cout << PrMathFunc.Deffunc.value[j];
			outFile << PrMathFunc.Deffunc.value[j];
		}
		cout << endl;
		outFile << endl;

		while (PrFuncList)
		{
			if (PrFuncList->AnotherFunc.FuncIDN.code != NULL)
			{
				for (int i = 0; i < PrFuncList->treeLVL; i++)
				{
					cout << ".";
					outFile << ".";
				}
				cout << PrFuncList->FuncListName << endl;
				outFile << PrFuncList->FuncListName << endl;

				for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL; i++)
				{
					cout << ".";
					outFile << ".";
				}
				cout << PrFuncList->AnotherFunc.FuncName << endl;
				outFile << PrFuncList->AnotherFunc.FuncName << endl;

				for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL + 2; i++)
				{
					cout << ".";
					outFile << ".";
				}
				cout << PrFuncList->AnotherFunc.FuncIDN_Name << endl;
				outFile << PrFuncList->AnotherFunc.FuncIDN_Name << endl;

				for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL + 4; i++)
				{
					cout << ".";
					outFile << ".";
				}
				cout << PrFuncList->AnotherFunc.IDN_Name << endl;
				outFile << PrFuncList->AnotherFunc.IDN_Name << endl;

				for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL + 6; i++)
				{
					cout << ".";
					outFile << ".";
				}
				cout << PrFuncList->AnotherFunc.FuncIDN.code << " ";
				outFile << PrFuncList->AnotherFunc.FuncIDN.code << " ";
				for (int j = 0; PrFuncList->AnotherFunc.FuncIDN.value[j]; j++)
				{
					cout << PrFuncList->AnotherFunc.FuncIDN.value[j];
					outFile << PrFuncList->AnotherFunc.FuncIDN.value[j];
				}
				cout << endl;
				outFile << endl;

				if (PrFuncList->AnotherFunc.Equ.code != NULL)
				{
					for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL + 6; i++)
					{
						cout << ".";
						outFile << ".";
					}
					cout << PrFuncList->AnotherFunc.Equ.code << " " << PrFuncList->AnotherFunc.Equ.value[0] << endl;
					outFile << PrFuncList->AnotherFunc.Equ.code << " " << PrFuncList->AnotherFunc.Equ.value[0] << endl;

					if (PrFuncList->AnotherFunc.Constant.code != NULL)
					{
						for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL + 6; i++)
						{
							cout << ".";
							outFile << ".";
						}
						cout << PrFuncList->AnotherFunc.Constant.code << " ";
						outFile << PrFuncList->AnotherFunc.Constant.code << " ";
						for (int j = 0; PrFuncList->AnotherFunc.Constant.value[j]; j++)
						{
							cout << PrFuncList->AnotherFunc.Constant.value[j];
							outFile << PrFuncList->AnotherFunc.Constant.value[j];
						}
						cout << endl;
						outFile << endl;

						for (int i = 0; i < PrFuncList->AnotherFunc.FuncCharacteristic.treeLVL; i++)
						{
							cout << ".";
							outFile << ".";
						}
						cout << PrFuncList->AnotherFunc.FuncCharacteristic.FuncCharName << endl;
						outFile << PrFuncList->AnotherFunc.FuncCharacteristic.FuncCharName << endl;

						if (PrFuncList->AnotherFunc.FuncCharacteristic.BackSlash.code != NULL)
						{
							for (int i = 0; i < PrFuncList->AnotherFunc.FuncCharacteristic.treeLVL + 2; i++)
							{
								cout << ".";
								outFile << ".";
							}
							cout << PrFuncList->AnotherFunc.FuncCharacteristic.BackSlash.code << " " << PrFuncList->AnotherFunc.FuncCharacteristic.BackSlash.value[0] << endl;
							outFile << PrFuncList->AnotherFunc.FuncCharacteristic.BackSlash.code << " " << PrFuncList->AnotherFunc.FuncCharacteristic.BackSlash.value[0] << endl;
							if (PrFuncList->AnotherFunc.FuncCharacteristic.FirstConst.code != NULL)
							{
								for (int i = 0; i < PrFuncList->AnotherFunc.FuncCharacteristic.treeLVL + 2; i++)
								{
									cout << ".";
									outFile << ".";
								}
								cout << PrFuncList->AnotherFunc.FuncCharacteristic.FirstConst.code << " ";
								outFile << PrFuncList->AnotherFunc.FuncCharacteristic.FirstConst.code << " ";
								for (int j = 0; PrFuncList->AnotherFunc.FuncCharacteristic.FirstConst.value[j]; j++)
								{
									cout << PrFuncList->AnotherFunc.FuncCharacteristic.FirstConst.value[j];
									outFile << PrFuncList->AnotherFunc.FuncCharacteristic.FirstConst.value[j];
								}
								cout << endl;
								outFile << endl;

								if (PrFuncList->AnotherFunc.FuncCharacteristic.Coma.code != NULL)
								{
									for (int i = 0; i < PrFuncList->AnotherFunc.FuncCharacteristic.treeLVL + 2; i++)
									{
										cout << ".";
										outFile << ".";
									}
									cout << PrFuncList->AnotherFunc.FuncCharacteristic.Coma.code << " " << PrFuncList->AnotherFunc.FuncCharacteristic.Coma.value[0] << endl;
									outFile << PrFuncList->AnotherFunc.FuncCharacteristic.Coma.code << " " << PrFuncList->AnotherFunc.FuncCharacteristic.Coma.value[0] << endl;
									
									if (PrFuncList->AnotherFunc.FuncCharacteristic.SecondConst.code != NULL)
									{
										for (int i = 0; i < PrFuncList->AnotherFunc.FuncCharacteristic.treeLVL + 2; i++)
										{
											cout << ".";
											outFile << ".";
										}
										cout << PrFuncList->AnotherFunc.FuncCharacteristic.SecondConst.code << " ";
										outFile << PrFuncList->AnotherFunc.FuncCharacteristic.SecondConst.code << " ";
										for (int j = 0; PrFuncList->AnotherFunc.FuncCharacteristic.SecondConst.value[j]; j++)
										{
											cout << PrFuncList->AnotherFunc.FuncCharacteristic.SecondConst.value[j];
											outFile << PrFuncList->AnotherFunc.FuncCharacteristic.SecondConst.value[j];
										}
										cout << endl;
										outFile << endl;
									}
									else
									{
										cout << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
										outFile << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
										outFile.close();
										return 0;
									}
								}
								else
								{
									cout << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
									outFile << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
									outFile.close();
									return 0;
								}
							}
							else
							{
								cout << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
								outFile << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
								outFile.close();
								return 0;
							}
						}
						else
						{
							cout << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
							outFile << PrFuncList->AnotherFunc.FuncCharacteristic.ErrorLog << endl;
							outFile.close();
							return 0;
						}
						if (PrFuncList->AnotherFunc.Semicolon.code != NULL)
						{
							for (int i = 0; i < PrFuncList->AnotherFunc.treeLVL + 2; i++)
							{
								cout << ".";
								outFile << ".";
							}
							cout << PrFuncList->AnotherFunc.Semicolon.code << " " << PrFuncList->AnotherFunc.Semicolon.value[0] << endl;
							outFile << PrFuncList->AnotherFunc.Semicolon.code << " " << PrFuncList->AnotherFunc.Semicolon.value[0] << endl;
						}
						else
						{
							cout << PrFuncList->AnotherFunc.ErrorLog << endl;
							outFile << PrFuncList->AnotherFunc.ErrorLog << endl;
							outFile.close();
							return 0;
						}
					}
					else
					{
						cout << PrFuncList->AnotherFunc.ErrorLog << endl;
						outFile << PrFuncList->AnotherFunc.ErrorLog << endl;
						outFile.close();
						return 0;
					}
				}
				else
				{
					cout << PrFuncList->AnotherFunc.ErrorLog << endl;
					outFile << PrFuncList->AnotherFunc.ErrorLog << endl;
					outFile.close();
					return 0;
				}

			}
			else
			{
				if (PrFuncList->Empty != "")
				{
					for (int i = 0; i < PrFuncList->treeLVL; i++)
					{
						cout << ".";
						outFile << ".";
					}
					cout << PrFuncList->FuncListName << endl;
					outFile << PrFuncList->FuncListName << endl;

					for (int i = 0; i < PrFuncList->treeLVL + 2; i++)
					{
						cout << ".";
						outFile << ".";
					}
					cout << PrFuncList->Empty << endl;
					outFile << PrFuncList->Empty << endl;
					break;
				}
				else
				{
					cout << PrFuncList->AnotherFunc.ErrorLog << endl;
					outFile << PrFuncList->AnotherFunc.ErrorLog << endl;
					outFile.close();
					return 0;
				}
			}
			PrFuncList = PrFuncList->AnotherList;
		}
	}
	else
	{
		if (PrMathFunc.Empty != "")
		{
			for (int i = 0; i < PrMathFunc.treeLVL + 2; i++)
			{
				cout << ".";
				outFile << ".";
			}
			cout << PrMathFunc.Empty << endl;
			outFile << PrMathFunc.Empty << endl;
		}
		else
		{
			cout << PrMathFunc.ErrorLog << endl;
			outFile << PrMathFunc.ErrorLog << endl;
			outFile.close();
			return 0;
		}
	}

	if (PrBlock.Begin.code != NULL)
	{
		for (int i = 0; i < PrBlock.treeLVL + 2; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << PrBlock.Begin.code << " ";
		outFile << PrBlock.Begin.code << " ";
		for (int j = 0; PrBlock.Begin.value[j]; j++)
		{
			cout << PrBlock.Begin.value[j];
			outFile << PrBlock.Begin.value[j];
		}
		cout << endl;
		outFile << endl;
		
		for (int i = 0; i < PrBlock.treeLVL + 2; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << PrBlock.StatementsList << endl;
		outFile << PrBlock.StatementsList << endl;

		if (PrBlock.End.code != NULL)
		{
			for (int i = 0; i < PrBlock.treeLVL + 4; i++)
			{
				cout << ".";
				outFile << ".";
			}
			cout << PrBlock.Empty << endl;
			outFile << PrBlock.Empty << endl;

			for (int i = 0; i < PrBlock.treeLVL + 2; i++)
			{
				cout << ".";
				outFile << ".";
			}
			cout << PrBlock.End.code << " ";
			outFile << PrBlock.End.code << " ";
			for (int j = 0; j < PrBlock.End.value[j]; j++)
			{
				cout << PrBlock.End.value[j];
				outFile << PrBlock.End.value[j];
			}
			cout << endl;
			outFile << endl;
		}
		else
		{
			cout << PrBlock.ErrorLog << endl;
			outFile << PrBlock.ErrorLog << endl;
			outFile.close();
			return 0;
		}
	}
	else
	{
		cout << PrBlock.ErrorLog << endl;
		outFile << PrBlock.ErrorLog << endl;
		outFile.close();
		return 0;
	}

	if (MainProg.Point.code != NULL)
	{
		for (int i = 0; i < MainProg.treeLVL + 2; i++)
		{
			cout << ".";
			outFile << ".";
		}
		cout << MainProg.Point.code << " " << MainProg.Point.value[0] << endl;
		outFile << MainProg.Point.code << " " << MainProg.Point.value[0] << endl;
	}
	else
	{
		cout << MainProg.ErrorLog << endl;
		outFile << MainProg.ErrorLog << endl;
		outFile.close();
		return 0;
	}

	outFile.close();
	return 0;
}

char** testPath(char** argv)
{
	char** tablePath;
	tablePath = new char* [100];
	for (int k = 0; k < 100; k++)
	{
		tablePath[k] = new char[100];
		for (int i = 0; i < 100; i++)
		{
			tablePath[k][i] = NULL;
		}
	}

	int lastColumn;

	char Input[] = "input.sig";
	char Generated[] = "generated.txt";

	for (int i = 0, indexPath = 0; argv[i + 1]; i++, indexPath += 2)
	{
		for (int j = 0; argv[i + 1][j]; j++)
		{
			tablePath[indexPath][j] = argv[i + 1][j];
			tablePath[indexPath + 1][j] = argv[i + 1][j];
			lastColumn = j + 1;
		}

		for (int k = 0; Input[k]; k++)
		{
			tablePath[indexPath][lastColumn + k] = Input[k];
		}

		for (int l = 0; Generated[l]; l++)
		{
			tablePath[indexPath + 1][lastColumn + l] = Generated[l];
		}
	}

	return tablePath;
}
