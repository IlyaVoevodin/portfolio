#include "Parser.h"

Parser::Parser(int row, int clmn, int** tokPosition, char** TokenCodTable, int lastRow, int lastClmn) {
	TableCodePosition = tokPosition;
	TokenTable = TokenCodTable;
	LastClmn = lastClmn;
	LastRow = lastRow;
	parserErrInfo.str() = "";
}

treeFuncList* Parser::createHead(treeFuncList** List, bool EmptyFlag)
{
	(*List) = new treeFuncList;
	(*List)->treeLVL = 10;
	(*List)->FuncListName = "<function-list>";
	if (EmptyFlag == false)
		(*List)->AnotherFunc = FuncTMP;
	else
		(*List)->Empty = "<empty>";
	(*List)->AnotherList = NULL;
	return (*List);
}

treeFuncList* Parser::addNode(treeFuncList** List, bool EmptyFlag) {

	if (*List)
	{
		treeFuncList* tmp = *List;
		while (tmp->AnotherList)
		{
			tmp = tmp->AnotherList;
		}
		tmp = new treeFuncList;
		tmp->treeLVL = 12;
		tmp->FuncListName = "<function-list>";
		tmp->AnotherList = NULL;
		if (EmptyFlag == false)
			tmp->AnotherFunc = FuncTMP;
		else
			tmp->Empty = "<empty>";
		(*List)->AnotherList = tmp;
		(*List) = tmp;
	}
	return 0;
}

void Parser::Signal() {
	Sig.SigName = "<signal-program>";
	ProgStart();
	Sig.StartProg = &Prog;
}

bool Parser::ProgStart() {
	TokenInfo tok;
	Prog.treeLVL = 2;
	Prog.ProgName = "<program>";
	if (TableCodePosition[tokenCodePosition][2] == 401)
	{
		tok.row = TableCodePosition[tokenCodePosition][0];
		tok.clmn = TableCodePosition[tokenCodePosition][1];
		tok.code = TableCodePosition[tokenCodePosition][2];
		for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
		{
			tok.value[j] = TokenTable[tokenCodePosition][j];
		}
		Prog.Program = tok;
		tokenCodePosition++;

		Prog.ProgIDN_Name = "<procedure-identifier>";
		Prog.IDN_Name = "<identifier>";
		if (Identifier() == true)
		{
			tok.row = TableCodePosition[tokenCodePosition][0];
			tok.clmn = TableCodePosition[tokenCodePosition][1];
			tok.code = TableCodePosition[tokenCodePosition][2];

			for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
			{
				tok.value[j] = TokenTable[tokenCodePosition][j];
				tok.value[j + 1] = NULL; 
			}
			Prog.ProgIDN = tok;
			tokenCodePosition++;

			if (TableCodePosition[tokenCodePosition][2] == 59)
			{
				tok.row = TableCodePosition[tokenCodePosition][0];
				tok.clmn = TableCodePosition[tokenCodePosition][1];
				tok.code = TableCodePosition[tokenCodePosition][2];
				tok.value[0] = TokenTable[tokenCodePosition][0];
				Prog.Semicolon = tok;
				tokenCodePosition++;

				if (Block() == true)
				{
					Prog.ProgBlock = &MainBlock;
					tokenCodePosition++;
					if (TableCodePosition[tokenCodePosition][2] == 46)
					{
						tok.row = TableCodePosition[tokenCodePosition][0];
						tok.clmn = TableCodePosition[tokenCodePosition][1];
						tok.code = TableCodePosition[tokenCodePosition][2];
						tok.value[0] = TokenTable[tokenCodePosition][0];
						Prog.Point = tok;
						return true;
					}
					else
					{
						//err expected '.'
						parserErrInfo << "Parser: Error( Symbol '.' expected, but '";

						if (TableCodePosition[tokenCodePosition][0] != NULL) {
							for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
							{
								parserErrInfo << TokenTable[tokenCodePosition][j];
							}

							parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
						}
						else {
							parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn << ")";
						}
						Prog.ErrorLog = parserErrInfo.str();
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				//err expected ';'
				parserErrInfo << "Parser: Error( Symbol ';'  expected, but '";

				if (TableCodePosition[tokenCodePosition][0] != NULL) {
					for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
					{
						parserErrInfo << TokenTable[tokenCodePosition][j];
					}

					parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
				}
				else {
					parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
				}
				Prog.ErrorLog = parserErrInfo.str();
				return false;
			}
		}
		else
		{
			//err not PROGRAM Identifier
			parserErrInfo << "Parser: Error( Program identifier expected, but '";

			if (TableCodePosition[tokenCodePosition][0] != NULL) {
				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					parserErrInfo << TokenTable[tokenCodePosition][j];
				}

				parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
			}
			else {
				parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
			}			
			Prog.ErrorLog = parserErrInfo.str();
			return false;
		}
	}
	else
	{
		//err not PROGRAM
		parserErrInfo << "Parser: Error( Reserved word 'PROGRAM' expected, but '";

		if (TableCodePosition[tokenCodePosition][0] != NULL) {
			for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
			{
				parserErrInfo << TokenTable[tokenCodePosition][j];
			}

			parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
		}
		else {
			parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
		}
		Prog.ErrorLog = parserErrInfo.str();
		
		return false;
	}
}

bool Parser::Identifier() {
	if ((1001 <= TableCodePosition[tokenCodePosition][2])&&(TableCodePosition[tokenCodePosition][2] <= 2001))
	{
		return true;
	}
	else {
		return false;
	}
}

bool Parser::Block() {
	TokenInfo tok;
	MainBlock.treeLVL = 4;
	MainBlock.BlockName = "<block>";
	
	if (Declarations() == true)
	{
		MainBlock.Declaration = &AllDeclarations;
		tokenCodePosition++;
		if (TableCodePosition[tokenCodePosition][2] == 402)
		{
			tok.row = TableCodePosition[tokenCodePosition][0];
			tok.clmn = TableCodePosition[tokenCodePosition][1];
			tok.code = TableCodePosition[tokenCodePosition][2];

			for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
			{
				tok.value[j] = TokenTable[tokenCodePosition][j];
				tok.value[j + 1] = NULL;
			}
			MainBlock.Begin = tok;
			tokenCodePosition++;

			MainBlock.StatementsList = "<statements-list>";

			if (TableCodePosition[tokenCodePosition][2] == 403)
			{
				MainBlock.Empty = "<empty>";
				
				tok.row = TableCodePosition[tokenCodePosition][0];
				tok.clmn = TableCodePosition[tokenCodePosition][1];
				tok.code = TableCodePosition[tokenCodePosition][2];

				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					tok.value[j] = TokenTable[tokenCodePosition][j];
					tok.value[j + 1] = NULL;
				}
				MainBlock.End = tok;

				return true;
			}
			else
			{
				//err not END
				parserErrInfo << "Parser: Error( Reserved word 'END' expected, but '";

				if (TableCodePosition[tokenCodePosition][0] != NULL) {
					for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
					{
						parserErrInfo << TokenTable[tokenCodePosition][j];
					}

					parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
				}
				else {
					parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
				}
				MainBlock.ErrorLog = parserErrInfo.str();
				return false;
			}
		}
		else
		{
			//err not BEGIN
			parserErrInfo << "Parser: Error( Reserved word 'BEGIN' expected, but '";

			if (TableCodePosition[tokenCodePosition][0] != NULL) {
				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					parserErrInfo << TokenTable[tokenCodePosition][j];
				}

				parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
			}
			else {
				parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
			}
			MainBlock.ErrorLog = parserErrInfo.str();
			
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Parser::Declarations() {
	AllDeclarations.treeLVL = 6;
	AllDeclarations.DeclarationsName = "<declarations>";
	
	if (MathFunction() == true)
	{
		AllDeclarations.MathFunctions = &MathFunc;
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::MathFunction() {
	TokenInfo tok;
	MathFunc.treeLVL = 8;
	MathFunc.MathFuncName = "<math-function-declarations>";
	if (TableCodePosition[tokenCodePosition][2] == 404)
	{
		tok.row = TableCodePosition[tokenCodePosition][0];
		tok.clmn = TableCodePosition[tokenCodePosition][1];
		tok.code = TableCodePosition[tokenCodePosition][2];

		for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
		{
			tok.value[j] = TokenTable[tokenCodePosition][j];
			tok.value[j + 1] = NULL;
		}
		MathFunc.Deffunc = tok;
		tokenCodePosition++;

		if (FuncList() == true)
		{
			MathFunc.FunctionList = FuncLists;
			return true;
		}
		else
		{
			MathFunc.FunctionList = FuncLists;
			return false;
		}
	}
	else
	{
		if (Empty() == true)
		{
			MathFunc.Empty = "<empty>";
			tokenCodePosition--;
			return true;
		}
		else
		{
			//err not DEFFUNC & not empty
			parserErrInfo << "Parser: Error( Reserved word 'DEFFUNC' expected (or empty), but '";

			if (TableCodePosition[tokenCodePosition][0] != NULL) {
				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					parserErrInfo << TokenTable[tokenCodePosition][j];
				}

				parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
			}
			else {
				parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
			}
			MathFunc.ErrorLog = parserErrInfo.str();

			return false;
		}
	}
	
}

bool Parser::FuncList() { 
	if (Empty() == true)
	{
		if (FuncLists == NULL)
		{
			createHead(&FuncLists, true);
			LastList = FuncLists;
		}
		else {
			addNode(&LastList, true);
		}
		tokenCodePosition--;
		return true;
	}
	else
	{
		funcExist = Func();

		if (FuncLists == NULL)
		{
			createHead(&FuncLists, false);
			LastList = FuncLists;
		}
		else {
			addNode(&LastList, false);
		}

		FuncTMP = NullFunc;
		FuncCharTMP = NullFuncChar;
	}
	tokenCodePosition++;

	if (funcExist == true)
	{
		bool funcEx = FuncList();
		return funcEx;
	}
	else
	{
		//err not empty & not identifier
		return false;
	}
}

bool Parser::Func() {
	TokenInfo tok;
	if (FuncLists == NULL)
		FuncTMP.treeLVL = 12;
	else
		FuncTMP.treeLVL = 14;
	FuncTMP.FuncName = "<function>";
	FuncTMP.FuncIDN_Name = "<function-identifier>";
	FuncTMP.IDN_Name = "<identifier>";

	if (Identifier() == true)
	{
		tok.row = TableCodePosition[tokenCodePosition][0];
		tok.clmn = TableCodePosition[tokenCodePosition][1];
		tok.code = TableCodePosition[tokenCodePosition][2];

		for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
		{
			tok.value[j] = TokenTable[tokenCodePosition][j];
			tok.value[j + 1] = NULL;
		}
		FuncTMP.FuncIDN = tok;
		tokenCodePosition++;

		if (TableCodePosition[tokenCodePosition][2] == 61)
		{
			tok.row = TableCodePosition[tokenCodePosition][0];
			tok.clmn = TableCodePosition[tokenCodePosition][1];
			tok.code = TableCodePosition[tokenCodePosition][2];
			tok.value[0] = TokenTable[tokenCodePosition][0];
			FuncTMP.Equ = tok;
			tokenCodePosition++;

			if (Const() == true)
			{
				tok.row = TableCodePosition[tokenCodePosition][0];
				tok.clmn = TableCodePosition[tokenCodePosition][1];
				tok.code = TableCodePosition[tokenCodePosition][2];

				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					tok.value[j] = TokenTable[tokenCodePosition][j];
					tok.value[j + 1] = NULL;
				}
				FuncTMP.Constant = tok;
				tokenCodePosition++;

				if (FuncCharcteristic() == true)
				{
					FuncTMP.FuncCharacteristic = FuncCharTMP;
					tokenCodePosition++;
					if (TableCodePosition[tokenCodePosition][2] == 59)
					{
						tok.row = TableCodePosition[tokenCodePosition][0];
						tok.clmn = TableCodePosition[tokenCodePosition][1];
						tok.code = TableCodePosition[tokenCodePosition][2];
						tok.value[0] = TokenTable[tokenCodePosition][0];
						FuncTMP.Semicolon = tok;
						return true;
					}
					else
					{
						//err expected ';'
						parserErrInfo << "Parser: Error( Symbol ';' expected, but '";

						if (TableCodePosition[tokenCodePosition][0] != NULL) {
							for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
							{
								parserErrInfo << TokenTable[tokenCodePosition][j];
							}

							parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
						}
						else {
							parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
						}
						FuncTMP.ErrorLog = parserErrInfo.str();
						return false;
					}
				}
				else
				{
					FuncTMP.FuncCharacteristic = FuncCharTMP;
					return false;
				}
			}
			else
			{
				//err not CONST
				parserErrInfo << "Parser: Error( Constant expected, but '";

				if (TableCodePosition[tokenCodePosition][0] != NULL) {
					for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
					{
						parserErrInfo << TokenTable[tokenCodePosition][j];
					}

					parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
				}
				else {
					parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
				}
				FuncTMP.ErrorLog = parserErrInfo.str();
				return false;
			}
		}
		else
		{
			//err expected '='
			parserErrInfo << "Parser: Error( Symbol '=' expected, but '";

			if (TableCodePosition[tokenCodePosition][0] != NULL) {
				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					parserErrInfo << TokenTable[tokenCodePosition][j];
				}

				parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
			}
			else {
				parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
			}
			FuncTMP.ErrorLog = parserErrInfo.str();
			return false;
		}
	}
	else
	{
		//err not Identifier
		parserErrInfo << "Parser: Error( Function identifier expected, but '";

		if (TableCodePosition[tokenCodePosition][0] != NULL) {
			for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
			{
				parserErrInfo << TokenTable[tokenCodePosition][j];
			}

			parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
		}
		else {
			parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
		}
		FuncTMP.ErrorLog = parserErrInfo.str();
		
		return false;
	}
}

bool Parser::Const() {
	if ((501 <= TableCodePosition[tokenCodePosition][2])&&(TableCodePosition[tokenCodePosition][2] <= 1000))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::FuncCharcteristic(){
	TokenInfo tok;
	if (FuncLists == NULL)
		FuncCharTMP.treeLVL = 18;
	else
		FuncCharTMP.treeLVL = 20;
	FuncCharTMP.FuncCharName = "<function-characteristic>";
	if (TableCodePosition[tokenCodePosition][2] == 92)
	{
		tok.row = TableCodePosition[tokenCodePosition][0];
		tok.clmn = TableCodePosition[tokenCodePosition][1];
		tok.code = TableCodePosition[tokenCodePosition][2];
		tok.value[0] = TokenTable[tokenCodePosition][0];
		FuncCharTMP.BackSlash = tok;
		tokenCodePosition++;

		if (Const() == true)
		{
			tok.row = TableCodePosition[tokenCodePosition][0];
			tok.clmn = TableCodePosition[tokenCodePosition][1];
			tok.code = TableCodePosition[tokenCodePosition][2];

			for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
			{
				tok.value[j] = TokenTable[tokenCodePosition][j];
				tok.value[j + 1] = NULL;
			}
			FuncCharTMP.FirstConst = tok;
			tokenCodePosition++;

			if (TableCodePosition[tokenCodePosition][2] == 44)
			{
				tok.row = TableCodePosition[tokenCodePosition][0];
				tok.clmn = TableCodePosition[tokenCodePosition][1];
				tok.code = TableCodePosition[tokenCodePosition][2];
				tok.value[0] = TokenTable[tokenCodePosition][0];
				FuncCharTMP.Coma = tok;
				tokenCodePosition++;

				if (Const() == true)
				{
					tok.row = TableCodePosition[tokenCodePosition][0];
					tok.clmn = TableCodePosition[tokenCodePosition][1];
					tok.code = TableCodePosition[tokenCodePosition][2];

					for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
					{
						tok.value[j] = TokenTable[tokenCodePosition][j];
						tok.value[j + 1] = NULL;
					}
					FuncCharTMP.SecondConst = tok;
					return true;
				}
				else
				{
					//err not Constant
					parserErrInfo << "Parser: Error( Constant expected, but '";

					if (TableCodePosition[tokenCodePosition][0] != NULL) {
						for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
						{
							parserErrInfo << TokenTable[tokenCodePosition][j];
						}

						parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
					}
					else {
						parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
					}
					FuncCharTMP.ErrorLog = parserErrInfo.str();
					return false;
				}
			}
			else
			{
				//err expected ','
				parserErrInfo << "Parser: Error( Symbol ',' expected, but '";

				if (TableCodePosition[tokenCodePosition][0] != NULL) {
					for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
					{
						parserErrInfo << TokenTable[tokenCodePosition][j];
					}

					parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
				}
				else {
					parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
				}
				FuncCharTMP.ErrorLog = parserErrInfo.str();
				return false;
			}
		}
		else
		{
			//err not Constant
			parserErrInfo << "Parser: Error( Constant expected, but '";

			if (TableCodePosition[tokenCodePosition][0] != NULL) {
				for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
				{
					parserErrInfo << TokenTable[tokenCodePosition][j];
				}

				parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
			}
			else {
				parserErrInfo << "Nothing' found! )(row: " << LastRow + 1 << ", column: " << LastClmn + 1 << ")";
			}
			FuncCharTMP.ErrorLog = parserErrInfo.str();
			return false;
		}
	}
	else
	{
		//err expected '\'
		parserErrInfo << "Parser: Error( Symbol '\' expected, but '";

		if (TableCodePosition[tokenCodePosition][0] != NULL) {
			for (int j = 0; TokenTable[tokenCodePosition][j]; j++)
			{
				parserErrInfo << TokenTable[tokenCodePosition][j];
			}

			parserErrInfo << "' found!)(row: " << TableCodePosition[tokenCodePosition][0] << ", column : " << TableCodePosition[tokenCodePosition][1] << ")";
		}
		else {
			parserErrInfo << "Nothing' found! )(row: " << LastRow + 1<< ", column: " << LastClmn + 1<< ")";
		}
		FuncCharTMP.ErrorLog = parserErrInfo.str();
		
		return false;
	}
}

bool Parser::Empty() {
	if (TableCodePosition[tokenCodePosition][2] == 402)
		return true;
	else
		return false;
}
