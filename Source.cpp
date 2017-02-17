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
/*
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>

using namespace std;

void output();
int lineNum = 1;
string define;

string getChar();
int ID;

struct lex {

};


int main()
{
	ifstream inFile;
	inFile.open("lexerExamp.txt");
	while (getline(inFile, define))
	{
		getChar();
		lineNum++;
	}
	return 0;
}


void output()
{
	/*cout << "(:Token " << lineNum << keyWD << ")" << endl;
	if (option == 3)
	{
	cout << ":ix " << ixNum;
	}
	else if (option == 2)
	{
	cout << ":str" << "" << define << "" << ")";
	}
	*/
}

string getChar()
{

}


void lexerLine(string str)
{
	string token;
	stringstream stringStream(str);
	bool commentFound;
	while (stringStream >> token && !commentFound)
	{
		//token[0]
		if (isalpha(str[0]))
			//void
			alphAFunc(token);
		else if (isdigit(str[0]))
			//void
			digitFunc(token);
		else 
			//void
			commentFound = symbolFunc(token);
			
	}
}


void alphAFunc(string token)
{

}


bool symbolFunc(string token)
{
	// return if comment found
}

void digitFunc(string token) 
{
	if (isdigit[token])
	{
		setID();
	}
	else if (token == '.')
	{
		setID();
	}
	else
	{
		return 0;
	}

}


void setID(string y, string orange)
{
	if (y == "identifier")
		ID = 2;
	else if (y = "integer")
		ID = 3;
	else if (y = "float")
		ID = 4;
	else if (y = "string")
		ID = 5;
	//Unpaired delimiters
	else if (orange = ",")
		ID = 6;
	else if (orange = ";")
		ID = 7;
	//keywords
	else if (orange = "prog")
		ID = 10;
	else if (orange = "main")
		ID = 11;
	else if (orange = "fcn")
		ID = 12;
	else if (orange = "class")
		ID = 13;
	else if (orange = "float")
		ID = 15;
	else if (orange = "int")
		ID = 16;
	else if (orange = "string")
		ID = 17;
	else if (orange = "if")
		ID = 18;
	else if (orange = "elseif")
		ID = 19;
	else if (orange = "else")
		ID = 20;
	else if (orange = "while")
		ID = 21;
	else if (orange = "input")
		ID = 22;
	else if (orange = "print")
		ID = 23;
	else if (orange = "new")
		ID = 24;
	else if (orange = "return")
		ID = 25;
	// Paired delieters
	else if (orange = "<")
		ID = 31;
	else if (orange = ">")
		ID = 32;
	else if (orange = "{")
		ID = 33;
	else if (orange = "}")
		ID = 34;
	else if (orange = "[")
		ID = 35;
	else if (orange = "]")
		ID = 35;
	else if (orange = "(")
		ID = 37;
	else if (orange = ")")
		ID = 38;
	//Other punctuation
	else if (orange = "*")
		ID = 41;
	else if (orange = "^")
		ID = 42;
	else if (orange = ":")
		ID = 43;
	else if (orange = ".")
		ID = 44;
	else if (orange = "=")
		ID = 45;
	else if (orange = "-")
		ID = 46;
	else if (orange = "+")
		ID = 47;
	else if (orange = "/")
		ID = 48;
	//Multi-char operators
	else if (orange = "->")
		ID = 51;
	else if (orange = "==")
		ID = 52;
	else if (orange = "!=")
		ID = 53;
	else if (orange = "<=")
		ID = 54;
	else if (orange = ">=")
		ID = 55;
	else if (orange = "<<")
		ID = 56;
	else if (orange = ">>")
		ID = 57;
	//miscellaeous
	else if (orange = "error")
		ID = 99;
}
*/
