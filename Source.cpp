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