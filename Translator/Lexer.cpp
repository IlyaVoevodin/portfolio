#include "Lexer.h"
#define cnst 100

Lexer::Lexer(int row, int column)
{
	AllTableRowSize = row;
	AllTableClmnSize = clmn;

	Constant = 501;
	Idn = 1001;
	
	clmn = 0;
	clmnCount = 0;
	rowCount = 0;
	CommRowPos = 0;
	CommClmnPos = 0;

	indexTableToken = 0;
	indexConstTable = 0;
	indexIdentTable = 0;
	indexLog = 0;

	reservWord[0][9] = NULL;
	reservWord[1][7] = NULL;
	reservWord[2][5] = NULL;
	reservWord[3][9] = NULL;

	TokenPosition = new int* [row];
	tableToken = new char* [row];

	constTable = new char* [row];
	constCodeTable = new int[row]
		;
	identifierTable = new char* [row];
	idnCodeTable = new int[row];
	SymbolCategories = new int[128];

	resw = new char[row];
	tok = new char[row];
	log = new string[row];

	for (int i = 0; i < row; i++)
	{
		constCodeTable[i] = NULL;
		idnCodeTable[i] = NULL;

		TokenPosition[i] = new int[column];
		tableToken[i] = new char[column];
		constTable[i] = new char[column];
		identifierTable[i] = new char[column];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			tableToken[i][j] = NULL;
			TokenPosition[i][j] = NULL;
			constTable[i][j] = NULL;
			identifierTable[i][j] = NULL;
		}
	}
}

Lexer::~Lexer()
{
	for (int i = 0; i < AllTableRowSize; i++)
	{
		delete[] TokenPosition[i], tableToken[i], constTable[i], identifierTable[i], SymbolCategories, resw, tok, log;
	}
}

void Lexer::SymSort() {

	for (int i = 0; i < 128; i++)
	{
		SymbolCategories[i] = 6;

		if (((8 <= i)&&(i <= 13)) || (i == 32))
			SymbolCategories[i] = 0;

		if ((48 <= i)&&(i <= 57))
			SymbolCategories[i] = 1;

		if (((i > 64) && (i < 91)) || ((i > 96) && (i < 123)))
			SymbolCategories[i] = 2;

		if ((i == 59) || (i == 46) || (i == 61) || (i == 44) || (i == 92))
			SymbolCategories[i] = 3;

		if (i == 40)
			SymbolCategories[i] = 5;
	}
}

void Lexer::divideToken(char sym, ifstream& file) {
	char num[1];
	stringstream fullErr;

	if (sym == '\n')
	{
		rowCount++;
		clmnCount = 0;
		file.get(sym);
	}

	if (SymbolCategories[(int)sym] == 1)
	{
		char tok[cnst] = { NULL };
		TokenPosition[indexTableToken][0] = rowCount + 1;
		TokenPosition[indexTableToken][1] = clmnCount + 1;

		for (int i = 0; SymbolCategories[(int)sym] == 1; i++)
		{
			tableToken[indexTableToken][clmn] = sym;
			tok[clmn] = sym;
			file.get(sym);
			clmn++;
			clmnCount++;
		}
		tok[clmn] = NULL;
		clmn = 0;

		bool f = false;
		for (int i = 0; constTable[i][0]; i++)
		{
			for (int j = 0; constTable[i][j]; j++)
			{
				if ((tok[j] == constTable[i][j]) && ((tok[j] != NULL) && (constTable[i][j] != NULL)))
				{
					f = true;
				}
				else
				{
					f = false;
					break;
				}
			}
			if (f == true)
			{
				TokenPosition[indexTableToken][2] = constCodeTable[i];
				break;
			}
		}

		if (f == false)
		{
			TokenPosition[indexTableToken][2] = Constant;
			constCodeTable[indexConstTable] = Constant;

			for (int i = 0; tok[i]; i++)
			{
				constTable[indexConstTable][i] = tok[i];
			}
			Constant++;
			indexConstTable++;
		}
		indexTableToken++;
	}

	if (SymbolCategories[(int)sym] == 2)
	{
		char tok[cnst] = { NULL };
		TokenPosition[indexTableToken][0] = rowCount + 1;
		TokenPosition[indexTableToken][1] = clmnCount + 1;

		for (int i = 0; (SymbolCategories[(int)sym] == 1) || (SymbolCategories[(int)sym] == 2); i++)
		{
			tableToken[indexTableToken][clmn] = sym;
			tok[clmn] = sym;
			file.get(sym);
			clmn++;
			clmnCount++;
			if (file.eof())
				break;
		}
		tok[clmn] = NULL;
		clmn = 0;

		bool res_f = false;
		for (int k = 0; reservWord[k][0]; k++)
		{
			for (int j = 0; reservWord[k][j]; j++)
			{
				resw[j] = reservWord[k][j + 2];
			}

			if (strcmp(resw, tok) == 0)
			{
				num[0] = { reservWord[k][0] };
				TokenPosition[indexTableToken][2] = idnResWord[atoi(num)];
				res_f = true;
				break;
			}
		}

		if (res_f == false)
		{
			bool f = false;
			for (int i = 0; identifierTable[i][0]; i++)
			{
				for (int j = 0; identifierTable[i][j]; j++)
				{
					if ((tok[j] == identifierTable[i][j]) && ((tok[j] != NULL) && (identifierTable[i][j] != NULL)))
						f = true;
					else
					{
						f = false;
						break;
					}
				}
				if (f == true)
				{
					TokenPosition[indexTableToken][2] = idnCodeTable[i];
					break;
				}
			}

			if (f == false)
			{
				TokenPosition[indexTableToken][2] = Idn;
				idnCodeTable[indexIdentTable] = Idn;

				for (int i = 0; tok[i]; i++)
				{
					identifierTable[indexIdentTable][i] = tok[i];
				}
				Idn++;
				indexIdentTable++;
			}
		}
		indexTableToken++;
	}

	if (SymbolCategories[(int)sym] == 3)
	{
		TokenPosition[indexTableToken][0] = rowCount + 1;
		TokenPosition[indexTableToken][1] = clmnCount + 1;
		TokenPosition[indexTableToken][2] = (int)sym;

		tableToken[indexTableToken][0] = sym;
		indexTableToken++;
		clmnCount++;
	}
	
	if (SymbolCategories[(int)sym] == 5)
	{
		clmnCount++;
		file.get(sym);
		CommRowPos = rowCount;
		CommClmnPos = clmnCount;
		
		if (sym == '*')
		{
			bool comm = false;
			clmnCount++;
			for (int i = 0; !file.eof(); i++)
			{
				file.get(sym);
				clmnCount++;
				if (sym == '*')
				{
					file.get(sym);
					clmnCount++;
					if (sym == ')')
					{
						comm = true;
						return;
					}
				}
				if (sym == '\n')
				{
					clmnCount = 0;
					rowCount++;
				}
			}

			if (comm == false)
			{
				try {
					throw (string)("Lexer: Error( You must close comment! )");
				}
				catch (string err) {
					fullErr << err << "(row: " << CommRowPos + 1 << ", column: " << CommClmnPos << ")";

					log[indexLog] = fullErr.str();
					fullErr.str("");
					indexLog++;
				}

			}
		}
		else
		{
			try {
				throw ((string)"Lexer: Error( Undefined symbol was found:");
			}
			catch (string err) {
				fullErr << err << "^" << sym << "^)(row: " << rowCount << ", column: " << clmnCount << ")";

				log[indexLog] = fullErr.str();
				fullErr.str("");
				indexLog++;
			}
		}
	}

	if (SymbolCategories[(int)sym] == 0)
	{
		if (sym == '\n')
		{
			rowCount++;
		}
		clmnCount++;
	}

	if (SymbolCategories[(int)sym] == 6)
	{
		try {
			throw ((string)"Lexer: Error( Undefined symbol was found:");
		}
		catch (string err) {
			fullErr << err << "^" << sym << "^)(row: " << rowCount + 1 << ", column: " << clmnCount + 1 << ")";

			log[indexLog] = fullErr.str();
			fullErr.str("");
			indexLog++;
		}
		clmnCount++;
	}
}

