// CS4303 Programming Language Concepts
// Lab exercise - Parser
//
// Name Anh Dang
//
// A simple parser for C/C++-style variable declarations.
// THe grammar is as follows:
//
// <declaration> 	::= 	<type>  <var> ';' | <type> <var> '=' <number> ';'
// <type> 		::= 	int | float
// <var> 		::= 	A | B | C | D | E
// <number> 	::= 	<integer> | <float>
// <integer> 	::= 	<integer> <digit> | <digit>
// <digit> 		::= 	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
// <float> 		::= 	<integer> '.' <integer>
// 
// Input is entered at the keyboard.
// If the input is correct, the program should print
// "no error found", otherwise, it should print the type
// of error and terminate its execution. There are four
// possible errors:
// 
// "unrecognizable type"
// "illegal variable name"
// "unexpected number"
// "; expected"
//
// Error message is printed out by calling function 
// "error". An error code ranging from 0 to 4 can be
// passed as an argument to the function indicating what
// message is to be printed. The mapping from the error
// code to the message can be found by looking at the
// definition of function "error".
//
// The following are some sample input and the response
// from the program:
//
// Please enter a declaration in format <type> <variable> [= number] ;
// int A;
// no error found
//
// Please enter a declaration in format <type> <variable> [= number] ;
// int a;
// illegal variable name
//
// Please enter a declaration in format <type> <variable> [= number] ;
// short B;
// unrecognizable type
// 
// Please enter a declaration in format <type> <variable> [= number] ;
// float C = 0.5;
// no error found
// 
// Please enter a declaration in format <type> <variable> [= number] ;
// int A = 10,
// ; expected
//
// float C = ;
// unexpected number
//
// float D = 2;
// no errors found
//
// int E = 2.2;
// no errors found
//
// float B 40.5;
// ; expected
//
// Other sample input:
//		float B;
//		float C=0.2;
//		short D;
//		float F;
//
// The last two sample inputs should generate errors because "short" and "F" are
// not acceptable tokens.

#include <iostream>
#include <string>

using namespace std;

string GetToken();
void error(int);

bool a1 = false;
bool a2 = false;
bool a3 = false;
bool a4 = false;
bool isFloat;// check if user input is Float

int main() {
	string token;

	cout << "Please enter a declaration in format "
		<< "<type> <variable> [= number] ;" << endl;

	string temp = "";
	
	token = GetToken();
	int i = 0;

	// check for float or int
	if (token == "int" || token == "float") {
		if (token == "float")
			isFloat = true;

		if (token == "int")
			isFloat = false;
	}
	else {
		error(1);// error 1 if not float or int
		a1 = true;
	}

	if (a1 == false)
	{
		token = GetToken();

		// check for A | B | C | D | E
		if (!(token == "A" || token == "B" || token == "C" || token == "D" || token == "E")) {
			error(2);
		}
		if (token == "A" || token == "B" || token == "C" || token == "D" || token == "E") {
			token = GetToken();
			if (isdigit(token[0]))
			{
				error(4);
			}
			a2 = true;

			// error 0 if <type> <var> ";"
			if (token == ";") {
				error(0);
			}
			else if (token == "=") {
				token = GetToken();

				// if float then check condition
				if (isFloat == true) {
					while (i < token.length()) {

						// if float <var> <int> then error 3
						if (token[0] == ';') {
							error(3);
							a3 = true;
							break;
						}
						else if (token[i] >= '0' && token[i] <= '9' || token[i] == '.') {
							temp += token[i];
						}

						// if not ";" then error 4
						else {
							error(4);
							break;
						}

						// if last index is ";" then error 0
						if (token[token.length() - 1] == ';') {
							error(0);
							break;
						}
						i++;
					}
				}

				// if in then check condition
				else if (isFloat == false) {
					while (i < token.length()) {
						if (token[0] == ';') {
							error(3);
							a3 = true;
							break;
						}
						else if (token[i] >= '0' && token[i] <= '9' || token[i] == '.') {
							temp += token[i];
							if (token[i] == '.') {
								error(3);
								a4 = true;
								break;
							}
						}
						else {
							a2 = true;
							break;
						}
						i++;

					}
					if (a4 == false) {
						if (a2 == true) {
							error(4);
						}
					}
					for (int i = 0; i < token.length(); i++) {

						// if last index is ";" then error 0
						if (a4 == 0 && token[token.length() - 1] == ';')
							error(0);
						break;
					}
				}
			}
		}
		
	}
	system("PAUSE");
	return 0;
}


string GetToken() {

	string token;
	bool getToken = true;
	char ch;

	while (getToken == true)
	{
		cin.get(ch);

		while (ch == ' ')
		{
			cin.get(ch);
		}
		if (isdigit(ch))
		{
			while (isdigit(ch))
			{
				token = token + ch;
				cin.get(ch);
				if (ch == '.')
				{
					token = token + ch;
					cin.get(ch);
				}
				if (ch == ';')
				{
					token = token + '\n' + ch;
					cin.get(ch);
				}
			}
			getToken = false;
		}
		else
		{
			token = token + ch;
			if (token == "i")
			{
				getToken = true;
			}
			else if (token == "in")
			{
				getToken = true;
			}
			else if (token == "int")
			{
				getToken = false;
			}
			else if (token == "f")
			{
				getToken = true;
			}
			else if (token == "fl")
			{
				getToken = true;
			}
			else if (token == "flo")
			{
				getToken = true;
			}
			else if (token == "floa")
			{
				getToken = true;
			}
			else if (token == "float")
			{
				getToken = false;
			}
			else if (token == "A" || token == "B" || token == "C" || token == "D" || token == "E")
			{
				getToken = false;
			}
			else if (token == "=")
			{
				getToken = false;
			}
			else if (token == ";")
			{

				getToken = false;
			}
			else if (token == "\n")
			{
				token = "";
				getToken = false;
			}
			else
			{
				getToken = false;
			}
		}

	}
	return token;
}

void error(int code) {
	switch (code) {
	case 0: cout << "no errors found" << endl; break;
	case 1: cout << "unrecognizable type" << endl; break;
	case 2: cout << "illegal variable name" << endl; break;
	case 3: cout << "unexpected number" << endl; break;
	case 4: cout << "; expected" << endl;
	}
	return;
}






