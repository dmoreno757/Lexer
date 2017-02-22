#include <iostream>
#include <string>
#include <fstream>

enum States { start = 1, ident = 2, endIdent = 3, num = 4, endNum = 5, eq = 6, eqeq = 7, semi = 8, floater = 9, endfloater = 10, stringStart = 11, stringEnd = 12, aster = 13, caret = 14, colon = 15,
			  dot = 16, minus = 17, plus = 18, slash = 19, comment = 20, comma = 21, angle1 = 22, angle2 = 23, brace1 = 24, brace2 = 25, bracket1 = 26, bracket2 = 27, parens1 = 28, parens2 = 29 };

const int TABLELENGTH = 83;
void createTable(int arr[][TABLELENGTH]);
void printTable(int arr[][TABLELENGTH]);
int stateChange(int arr[][TABLELENGTH], int currState, int index);
char peek_token();

int main()
{

	std::ifstream input("mycode.txt"); //Read in the code
	if (!input.is_open())
	{
		std::cout << "Error opening code file.\n";
	}

	int stateTable[30][TABLELENGTH];  //Generate the State Table
	createTable(stateTable);
	printTable(stateTable);

	int charLocation;
	int tokenLocation;
	int strLength = 0;
	int lineNum = 0;
	char c;
	std::string textLine;
	std::string currentToken;
	States currentState = start;
	
	while (std::getline(input, textLine))
	{
		lineNum++;
		charLocation = 0;
		tokenLocation = 0;
		//std::cout << textLine << std::endl;
		strLength = textLine.length();
		//std::cout << " Length: " <<  strLength << std::endl;
		while (charLocation <= strLength)
		{
			switch (currentState)
			{
				case start:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "character: " << c << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}
					
					if (index > TABLELENGTH)
					{
						break;
					}
					//std::cout << "index: " << index << std::endl;
					
					//SateChange Function
					currentState = States(stateChange(stateTable, start, index));
					//std::cout << "index: " << index << " character: " << c << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl << std::endl;

					if (index == 71) //for whitespace
					{
						tokenLocation++;
					}
					break;
				}
				case ident:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//SateChange Function
					currentState = States(stateChange(stateTable, ident, index));
					//std::cout << "index: " << index << " character: " << c << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl << std::endl;

					break;
				}
				case endIdent:
				{
					//Create ident token, return to starting state, back up character pointer
					std::cout << "(:token " << lineNum << " ident :str \"";
					int stringSize = charLocation - tokenLocation;
					char* temp = new char[stringSize];

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//std::cout << "stringSize: " << stringSize << std::endl;
					for (int i = 0; i < stringSize-1; i++)
					{
						temp[i] = textLine[tokenLocation];
						tokenLocation++;
					}
					temp[stringSize-1] = '\0';
					currentToken = std::string(temp);
					delete[] temp;

					currentState = start;
					charLocation--;

					std::cout << currentToken << "\")" << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl;
					//std::cout << "charLocation: " << charLocation << std::endl << std::endl;
					//tokenLocation = charLocation;
					

					break;
				}
				case num:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//std::cout << "index: " << index;
					//std::cout << TABLELENGTH;
					if (index > TABLELENGTH)
					{
						std::cout << "(:token " << lineNum << " int :str \"";
						int stringSize = charLocation - tokenLocation;
						char* temp = new char[stringSize];

						//std::cout << "tokenLocation: " << tokenLocation << std::endl;
						//std::cout << "stringSize: " << stringSize << std::endl;
						for (int i = 0; i < stringSize - 1; i++)
						{
							temp[i] = textLine[tokenLocation];
							tokenLocation++;
						}
						temp[stringSize - 1] = '\0';
						currentToken = std::string(temp);
						delete[] temp;

						currentState = start;
						charLocation--;

						std::cout << currentToken << "\")" << std::endl;
						break;
					}

					//SateChange Function
					currentState = States(stateChange(stateTable, num, index));
					//std::cout << "index: " << index << " character: " << c << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl << std::endl;

					break;
				}
				case endNum:
				{
					//Create num token, return to starting state, back up character pointer
					std::cout << "(:token " << lineNum << " int :str \"";
					int stringSize = charLocation - tokenLocation;
					char* temp = new char[stringSize];

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//std::cout << "stringSize: " << stringSize << std::endl;
					for (int i = 0; i < stringSize - 1; i++)
					{
						temp[i] = textLine[tokenLocation];
						tokenLocation++;
					}
					temp[stringSize - 1] = '\0';
					currentToken = std::string(temp);
					delete[] temp;

					currentState = start;
					charLocation--;

					std::cout << currentToken << "\")" << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl;
					//std::cout << "charLocation: " << charLocation << std::endl << std::endl;
					//tokenLocation = charLocation;

					break;
				}
				case eq:
				{
					c = textLine[charLocation];
					charLocation++;

					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//SateChange Function
					currentState = States(stateChange(stateTable, eq, index));

					if (currentState != eqeq) //equal token else its opeq token
					{
						std::cout << "(:token " << lineNum << " equal)" << std::endl;
						charLocation--; //Back up location
					}

					/*
					std::cout << "index: " << index << " character: " << c << std::endl;
					std::cout << "Going To State: " << currentState << std::endl;
					std::cout << "charLocation: " << charLocation << std::endl << std::endl;
					*/
					
					tokenLocation = charLocation;
					
					break;
				}
				case eqeq:
				{


					break;
				}
				case semi:
				{
					std::cout << "(:token " << lineNum << " semi)" << std::endl;
					currentState = start;
					break;
				}
				case floater:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//SateChange Function
					currentState = States(stateChange(stateTable, floater, index));
					//std::cout << "index: " << index << " character: " << c << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl << std::endl;
					break;
				}
				case endfloater:
				{
					//Create num token, return to starting state, back up character pointer
					std::cout << "(:token " << lineNum << " float :str \"";
					int stringSize = charLocation - tokenLocation;
					char* temp = new char[stringSize];

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//std::cout << "stringSize: " << stringSize << std::endl;
					for (int i = 0; i < stringSize - 1; i++)
					{
						temp[i] = textLine[tokenLocation];
						tokenLocation++;
					}
					temp[stringSize - 1] = '\0';
					currentToken = std::string(temp);
					delete[] temp;

					currentState = start;
					charLocation--;

					std::cout << currentToken << "\")" << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl;
					//std::cout << "charLocation: " << charLocation << std::endl << std::endl;
					//tokenLocation = charLocation;
				}
				case stringStart:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//SateChange Function
					currentState = States(stateChange(stateTable, stringStart, index));
					//std::cout << "index: " << index << " character: " << c << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl << std::endl;
					break;
				}
				case stringEnd:
				{
					//Create num token, return to starting state, back up character pointer
					std::cout << "(:token " << lineNum << " string :str ";
					int stringSize = charLocation - tokenLocation;
					char* temp = new char[stringSize];

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//std::cout << "stringSize: " << stringSize << std::endl;
					for (int i = 0; i < stringSize - 1; i++)
					{
						temp[i] = textLine[tokenLocation];
						tokenLocation++;
					}
					temp[stringSize - 1] = '\0';
					currentToken = std::string(temp);
					delete[] temp;

					currentState = start;
					charLocation--;

					std::cout << currentToken << "\")" << std::endl;

					tokenLocation++;
					charLocation++;
					//std::cout << "Going To State: " << currentState << std::endl;
					//std::cout << "charLocation: " << charLocation << std::endl;
					//std::cout << "tokenLocation: " << tokenLocation << std::endl << std::endl;
					
					break;
				}
				case aster:
				{
					std::cout << "(:token " << lineNum << " aster)" << std::endl;
					currentState = start;
					tokenLocation++;
					break;
				}
				case caret:
				{
					std::cout << "(:token " << lineNum << " caret)" << std::endl;
					currentState = start;
					tokenLocation++;
					break;
				}
				case colon:
				{
					std::cout << "(:token " << lineNum << " colon)" << std::endl;
					currentState = start;
					tokenLocation++;
					break;
				}
				case dot:
				{
					std::cout << "(:token " << lineNum << " dot)" << std::endl;
					currentState = start;
					tokenLocation++;
					break;
				}
				case minus:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//SateChange Function
					currentState = States(stateChange(stateTable, num, index));
					//std::cout << "index: " << index << " character: " << c << std::endl;
					//std::cout << "Going To State: " << currentState << std::endl << std::endl;
					if (currentState != 4)
					{
						std::cout << "(:token " << lineNum << " minus)" << std::endl;
						currentState = start;
						charLocation--;
					}
					tokenLocation++;
					break;
				}
				case plus:
				{
					std::cout << "(:token " << lineNum << " plus)" << std::endl;
					currentState = start;
					tokenLocation++;
					break;
				}
				case slash:
				{
					c = textLine[charLocation];
					charLocation++;

					//std::cout << "tokenLocation: " << tokenLocation << std::endl;
					//loop through table and find character
					int index = 0;
					while (stateTable[0][index] != int(c) && index <= TABLELENGTH)
					{
						index++;
					}

					//StateChange Function
					currentState = States(stateChange(stateTable, slash, index));

					if (currentState != 20)
					{
						std::cout << "(:token " << lineNum << " slash)" << std::endl;
						currentState = start;
						charLocation--;
						tokenLocation++;
					}
					break;
				}
				case comment:
				{
					do
					{
						c = textLine[charLocation];
						charLocation++;
					} while (c != '\n' && c!='\0');
					currentState = start;

					break;
				}
				case comma:
				{
					std::cout << "(:token " << lineNum << " comma)" << std::endl;
					currentState = start;
					tokenLocation++;
					break;
				}
				case angle1:
				{
					std::cout << "(:token " << lineNum << " angle1)" << std::endl;
					currentState = start;
					tokenLocation++;
					
					break;
				}
				case angle2:
				{
					std::cout << "(:token " << lineNum << " angle2)" << std::endl;
					currentState = start;
					tokenLocation++;
					
					break;
				}
				case brace1:
				{
					std::cout << "(:token " << lineNum << " brace1)" << std::endl;
					currentState = start;
					//tokenLocation++;
					
					break;
				}
				case brace2:
				{
					std::cout << "(:token " << lineNum << " brace2)" << std::endl;
					currentState = start;
					tokenLocation++;
					
					break;
				}
				case bracket1:
				{
					std::cout << "(:token " << lineNum << " brackets1)" << std::endl;
					currentState = start;
					tokenLocation++;
					
					break;
				}
				case bracket2:
				{
					std::cout << "(:token " << lineNum << " brackets2)" << std::endl;
					currentState = start;
					tokenLocation++;
					
					break;
				}
				case parens1:
				{
					std::cout << "(:token " << lineNum << " parens1)" << std::endl;
					currentState = start;
					tokenLocation++;
					
					break;
				}
				case parens2:
				{
					std::cout << "(:token " << lineNum << " parens2)" << std::endl;
					currentState = start;
					tokenLocation++;
					;
					break;
				}
			}
		}
	}

	return 0;
}

void createTable(int arr[][TABLELENGTH])
{
	//Top row is filled in with all possible characters//
	arr[0][0] = 95; //_
	for (int i = 1; i < 27; i++) //[a-z]
	{
		arr[0][i] = i + 96;
	}
	for (int i = 27; i < 53; i++) //[A-Z]
	{
		arr[0][i] = i + 38;
	}
	for (int i = 53; i < 63; i++) //[0-9]
	{
		arr[0][i] = i - 5;
	}

	//Other punctuation
	arr[0][63] = 42; // *
	arr[0][64] = 94; // ^
	arr[0][65] = 58; // :
	arr[0][66] = 46; // .
	arr[0][67] = 61; // =
	arr[0][68] = 45; // -
	arr[0][69] = 43; // +
	arr[0][70] = 47; // /
	arr[0][71] = 32; // whitespace

	//Unpaired Delimiters
	arr[0][72] = 44; // ,
	arr[0][73] = 59; // ;

	arr[0][74] = 34; // "

	//Paired Delimiters
	arr[0][75] = 60; // <
	arr[0][76] = 62; // >
	arr[0][77] = 123; // {
	arr[0][78] = 125; // }
	arr[0][79] = 91; // [
	arr[0][80] = 93; // ]
	arr[0][81] = 40; // (
	arr[0][82] = 41; // )

	/*-------------------State 1--------------------*/ //start
	for (int i = 0; i < 53; i++) // LU send to state 2
	{
		arr[1][i] = 2;
	}
	for (int i = 53; i < 63; i++) //[0-9] to state 4
	{
		arr[1][i] = 4;
	}
	arr[1][63] = 13;
	arr[1][64] = 14;
	arr[1][65] = 15;
	arr[1][66] = 16;
	arr[1][67] = 6;
	arr[1][68] = 17; // state 17 will check if its a negative digit
	arr[1][69] = 18;
	arr[1][70] = 19;
	arr[1][71] = 1;
	arr[1][72] = 21; //comma
	arr[1][73] = 8;
	arr[1][74] = 11;

	arr[1][75] = 22; // <
	arr[1][76] = 23; // >
	arr[1][77] = 24; // {
	arr[1][78] = 25; // }
	arr[1][79] = 26; // [
	arr[1][80] = 27; // ]
	arr[1][81] = 28; // (
	arr[1][82] = 29; // )


	/*-------------------State 2--------------------*/ //ident
	for (int i = 0; i < 63; i++) // LUD send to state 2
	{
		arr[2][i] = 2;
	}

	for (int i = 63; i < TABLELENGTH; i++) // Anything not LUD send to state 3
	{
		arr[2][i] = 3;
	}

	/*-------------------State 3--------------------*/ //end ident
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to state 1
	{
		arr[3][i] = 1;
	}

	/*-------------------State 4--------------------*/ //number
	for (int i = 0; i < 53; i++) // Anything to state 5 except digits
	{
		arr[4][i] = 5;
	}

	for (int i = 53; i < 63; i++) // Digits
	{
		arr[4][i] = 4;
	}

	for (int i = 63; i < TABLELENGTH; i++)
	{
		arr[4][i] = 5;
	}

	arr[4][66] = 9; // Send to float state

	/*-------------------State 5--------------------*/ //end number
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to state 1
	{
		arr[5][i] = 1;
	}

	/*-------------------State 6--------------------*/ // =
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1 except = 
	{
		arr[6][i] = 1;
	}

	arr[6][67] = 7; // = to state 7
	/*-------------------State 7--------------------*/ // ==
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[7][i] = 1;
	}

	/*-------------------State 8--------------------*/ // ;
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[8][i] = 1;
	}

	/*-------------------State 9--------------------*/ // floating point num 
	for (int i = 0; i < TABLELENGTH; i++) // Anything to 10 except digits
	{
		arr[9][i] = 10;
	}
	for (int i = 53; i < 63; i++) // Digits
	{
		arr[9][i] = 9;
	}

	/*-------------------State 10--------------------*/ // end floating point
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[10][i] = 1;
	}

	/*-------------------State 11--------------------*/ // string start
	for (int i = 0; i < TABLELENGTH; i++) // Anything to 11 except "
	{
		arr[11][i] = 11;
	}
	arr[11][74] = 12;

	/*-------------------State 12--------------------*/ // string end
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[12][i] = 1;
	}

	/*-------------------State 13--------------------*/ // aster *
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[13][i] = 1;
	}

	/*-------------------State 14--------------------*/ // caret ^
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[14][i] = 1;
	}

	/*-------------------State 15--------------------*/ // colon :
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[15][i] = 1;
	}

	/*-------------------State 16--------------------*/ // dot .
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[16][i] = 1;
	}

	/*-------------------State 17--------------------*/ // minus -   needs to check next char to see if it should get sent to state 4
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[17][i] = 1;
	}
	for (int i = 53; i < 63; i++) // Digits
	{
		arr[17][i] = 4;
	}

	/*-------------------State 18--------------------*/ // plus +
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[18][i] = 1;
	}

	/*-------------------State 19--------------------*/ // slash /
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[19][i] = 1;
	}
	arr[19][70] = 20;

	/*-------------------State 20--------------------*/ // comment //
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[20][i] = 1;
	}

	/*-------------------State 21--------------------*/ // comma ,
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[21][i] = 1;
	}

	/*-------------------State 22--------------------*/ // <
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[22][i] = 1;
	}

	/*-------------------State 23--------------------*/ // >
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[23][i] = 1;
	}

	/*-------------------State 24--------------------*/ // {
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[24][i] = 1;
	}

	/*-------------------State 25--------------------*/ // }
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[25][i] = 1;
	}

	/*-------------------State 26--------------------*/ // [
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[26][i] = 1;
	}

	/*-------------------State 27--------------------*/ // ]
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[27][i] = 1;
	}

	/*-------------------State 28--------------------*/ // (
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[28][i] = 1;
	}

	/*-------------------State 29--------------------*/ // )
	for (int i = 0; i < TABLELENGTH; i++) // Anything back to 1
	{
		arr[29][i] = 1;
	}
}

void printTable(int arr[][TABLELENGTH])
{
	std::cout << "-------------------Print Table------------------" << std::endl;
	int j = 0;
	for (int i = 0; i < TABLELENGTH; i++)
	{
		if (j == 24)
		{
			std::cout << std::endl;
			j = 0;
		}
		std::cout << char(arr[0][i]) << ' ';
		j++;
	}
	std::cout << std::endl << "------------------------------------------------" << std::endl;
}

int stateChange(int arr[][TABLELENGTH], int currState, int index)
{
	return arr[currState][index];
}

char peek_token()
{
	return 0;
}
