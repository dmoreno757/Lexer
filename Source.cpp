#include <iostream>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;

const int numChars = 63;
int advance(char input, int arr[][numChars], int currentState);

//test states
enum States{start = 1, id = 2, num = 3, finish = 4, error = 5};

/*
2 ident = LU LUD * // identifier.
LU = '_' | [a..zA..Z] // Letter-Underscore.
LUD = LU | DIGIT // Letter-Underscore-Digit.
DIGIT = [0..9]
*/



//using table driven version
int table[5][numChars];

int main()
{
	States state = start;
	char buffer;
	//fill first row with every possible valid character
	table[0][0] = 95;

	for (int i = 97; i < 123; i++)
	{
		table[0][i - 96] = i;
	}

	for (int i = 65; i < 91; i++)
	{
		table[0][i - 38] = i;
	}

	for (int i = 48; i < 58; i++)
	{
		table[0][i + 5] = i;
	}

	//---------------------table[1][...] Starting state----------------

	table[1][0] = 2; 	//'_'

	//a-z
	for (int i = 97; i < 123; i++)
	{
		table[1][i - 96] = 2;
	}

	//A-Z
	for (int i = 65; i < 91; i++)
	{
		table[1][i - 38] = 2;
	}

	//0-9
	for (int i = 48; i < 58; i++)
	{
		table[1][i + 5] = 4;
	}
	//----------------------------------------------------------------

	//-------------------table[2][...] ID State-----------------------

	table[2][0] = 1; 	//'_'

	//a-z
	for (int i = 97; i < 123; i++)
	{
		table[2][i - 96] = 2;
	}

	//A-Z
	for (int i = 65; i < 91; i++)
	{
		table[2][i - 38] = 2;
	}

	//0-9
	for (int i = 48; i < 58; i++)
	{
		table[2][i + 5] = 2;
	}

	//-----------------------------------------------------------------

	cout << "Test Below\n";
	for (int i = 0; i < numChars; i++)
	{
		cout << (char)table[0][i] << ' ';
	}

	while (state != finish && state != error)
	{
		switch (state)
		{
			case start:
				cout << "Enter character(Start State): ";
				cin >> buffer;
				int test;
				test = States(advance(buffer, table, 1));
				cout << "test: " << test << std::endl;
				state = (States)test;

				break;
			case id:
				cout << "Enter character(ID State): ";
				cin >> buffer;
				int test2;
				test2 = States(advance(buffer, table, 2));
				cout << "test2: " << test2;
				break;
			case num:
				cout << "Enter character(num State): ";
				cin >> buffer;
				state = States(advance(buffer, table, 3));
				break;
			case finish:
				cout << "Enter character(finish State): ";
				cin >> buffer;
				state = States(advance(buffer, table, 4));
				break;
			case error:
				cout << "Error in code";
				//exit(EXIT_FAILURE);
				break;
		}
	}

	return 0;
}

int advance(char input, int arr[][numChars], int currentState)
{
	std::cout << "CurrentState: " << currentState << std::endl;
	for (int i = 0; i < numChars; i++)
	{
		if (input == (char)arr[0][i])
		{
			return arr[currentState][i];
		}
	}
	cout << "couldn't find char\n";

    //store input in the lexeme* buffer
	//advance the buffer index
	//or refill the buffer and setindex to 0
	//watching out for EOF
	return -1;
}

//STEP 1 Write Regular Expressions for all tokens we need to recognize
//STEP 2 Form NFA using Thompson's construction that recognizes these tokens
//Step 3 From the NFA, the subset construction will give the DFA which can be embedded as a table in the lexical analyzer

//BELOW IS CODE THAT NEEDS TO BE MERGED INTO PRECEEDING CODE

**************************************************************************************************************************************
******************UPDATED*****************************************************
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <cstdlib>

using namespace std;

int lineNum = 1;
string define;

class lexer {
public:
	lexer();
	void setupID();
	void outPutStream();
	//void clear();
	int isKeyWD(string a);
	//int isDG(char a);
	//int isPunct(char a);
	//int isMultiPunc(char a, char b);
	int isSpace(char);

private:
	int ID;
	string inputSt;
	string token;
	string identifier;
	string placeHolder;

};


int main()
{
	ifstream inFile;
	inFile.open("check.txt");
	while (getline(inFile, define))
	{
		lexer();
		lineNum++;
	}
	return 0;
}

lexer::lexer()
{
	int x = 0;
	do
	{
		char fl = define[x];
		char sl = define[x + 1];
		if (isSpace(fl))
			continue;
		else if (fl == '"')
		{
			x++;
			while (fl != '"')
			{
				placeHolder += fl;
				x++;
				fl = define[x];
			}
			token = placeHolder;
			identifier = "string";
			setupID();
			outPutStream();
			//clearStream();
		}
		else if (isalpha(fl))
		{
			placeHolder += fl;
			while (isalpha(sl))
			{
				x++;
				fl = define[x];
				placeHolder += fl;
				sl = define[x + 1];
			}
			if (isKeyWD(placeHolder)) {
				token = placeHolder;
			}
			else {
				identifier = "identifier";
				token = placeHolder;
			}
			setupID();
			outPutStream();
			//clear();
		}
		
			
	} while (x == define.length());
}

void lexer::outPutStream()
{
	
		cout << "(:Token " << lineNum << " " << ID << ")" << endl;
		if (ID == 3)
		{
			cout << ":ix " << token;
		}
		else if (ID == 4)
		{
			cout << ":str" << "" << token << "" << ")";
		}
}

int lexer::isSpace(char a)
{
	if (a == ' ')
	{
		return 1;
	}
	else
		return 0;
}

int lexer::isKeyWD(string a)
{
	if (a == "prog" || a == "main" || a == "fcn" || a == "class" || a == "float" || a == "int" ||
		a == "string" || a == "if" || a == "elseif" || a == "else" || a == "while" || a == "input" ||
		a == "print" || a == "new" || a == "return")
	{
		return 1;
	}
	else
		return 0;

}

void lexer::setupID()
{
	if (identifier == "identifier")
		ID = 2;
	else if (identifier == "integer")
		ID = 3;
	else if (identifier == "float")
		ID = 4;
	else if (identifier == "string")
		ID = 5;
	//Unpaired delimiters
	else if (token == ",")
		ID = 6;
	else if (token == ";")
		ID = 7;
	//keywords
	else if (token == "prog")
		ID = 10;
	else if (token == "main")
		ID = 11;
	else if (token == "fcn")
		ID = 12;
	else if (token == "class")
		ID = 13;
	else if (token == "float")
		ID = 15;
	else if (token == "int")
		ID = 16;
	else if (token == "string")
		ID = 17;
	else if (token == "if")
		ID = 18;
	else if (token == "elseif")
		ID = 19;
	else if (token == "else")
		ID = 20;
	else if (token == "while")
		ID = 21;
	else if (token == "input")
		ID = 22;
	else if (token == "print")
		ID = 23;
	else if (token == "new")
		ID = 24;
	else if (token == "return")
		ID = 25;
	// Paired delieters
	else if (token == "<")
		ID = 31;
	else if (token == ">")
		ID = 32;
	else if (token == "{")
		ID = 33;
	else if (token == "}")
		ID = 34;
	else if (token == "[")
		ID = 35;
	else if (token == "]")
		ID = 35;
	else if (token == "(")
		ID = 37;
	else if (token == ")")
		ID = 38;
	//Other punctuation
	else if (token == "*")
		ID = 41;
	else if (token == "^")
		ID = 42;
	else if (token == ":")
		ID = 43;
	else if (token == ".")
		ID = 44;
	else if (token == "=")
		ID = 45;
	else if (token == "-")
		ID = 46;
	else if (token == "+")
		ID = 47;
	else if (token == "/")
		ID = 48;
	//Multi-char operators
	else if (token == "->")
		ID = 51;
	else if (token == "==")
		ID = 52;
	else if (token == "!=")
		ID = 53;
	else if (token == "<=")
		ID = 54;
	else if (token == ">=")
		ID = 55;
	else if (token == "<<")
		ID = 56;
	else if (token == ">>")
		ID = 57;
	//miscellaeous
	else if (token == "error")
		ID = 99;
	else
		ID = 0;

	return;
}
