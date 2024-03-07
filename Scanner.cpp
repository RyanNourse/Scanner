#include "Scanner.h"
#include <string>
using namespace std;
//set up program argument
//this function returns a string representation of the TokenType
string Scanner::toString(TokenType t)
{
	if (t == NONE)
		return "NONE";
	if (t == EQUALASSIGN)
		return "EQL";
	if (t == LBRACE)
		return "LBRACE";
	if (t == RBRACE)
		return "RBRACE";
	if (t == EE)
		return "EE";
	if (t == STRING)
		return "STRING";
	if (t == LPAREN)
		return "LPAREN";
	if (t == RPAREN)
		return "RPAREN";
	if (t == SEMI)
		return "SEMI";
	if(t == COMMA)
		return "COMMA";
	if (t == GRE)
		return "GRE";
	if (t == GR)
		return "GR";
	if (t == MULTIPLY)
		return "MULTIPLY";
	if (t == DIVIDE)
		return "DIVIDE";
	if (t == MOD)
		return "MOD";
	if (t == PLUS)
		return "PLUS";
	if (t == MINUS)
		return "MINUS";
	if (t == AND)
		return "AND";
	if (t == OR)
		return "OR";
	if (t == NOT)
		return "NOT";
	if (t == FLOAT)
		return "FLOAT";
	if (t == ERROR)
		return "error: ";
	return "ERROR in tostring";
}

string Scanner::currentTokenString()
{
	return currents;
}

string Scanner::nextTokenString()
{
	return nexts;
}

TokenType Scanner::currentTokenType()
{
	return currenttt;
}

TokenType Scanner::nextTokenType()
{
	return nexttt;
}


//constructor for the scanner. Right now it also iterates over everything in the scanner.
Scanner::Scanner(string fname)
{
	filestream.open(fname);

	linenext = 1;

	

	if (!filestream.good())
	{
		cout << "Could not open file: "<< fname<<"\n";
		return;
	}

	
	advance(); //fill up first slot
	advance(); //fill up second slot

	while (currentTokenType() != ENDOFFILE)
	{
		cout << toString(currentTokenType()) << " " << currentTokenString() << "\n";
		advance();
	}
}


//this function takes the next thing in the stream and adds it to the buffer
void addToBuffer(string & buf, ifstream & stream)
{
	int next = stream.get();

	if (next == -1)
	{
		buf = buf + (char)0; //null signifies eof for today!
	}
	else
	{
		buf = buf + (char)next;
	}

}


//this function removes the end of the buffer and sticks it back in the stream so it can be read again)
void removeFromBuffer(string & buf, ifstream & stream)
{
	char last = buf.back();
	stream.putback(last);
	buf = buf.substr(0, buf.size() - 1);
}


//returns true if the character is a number
bool isNum(char test)
{
	return (test == '0' || test == '1' || test == '2' || test == '3' || test == '4' || test == '5' || test == '6' || test == '7' || test == '8' || test == '9');
}

//returns true if lowercase character (and _)
bool isLowerCharacter(char test)
{
	return (test == 'a' || test == 'b' || test == 'c' || test == 'd' ||
		test == 'e' || test == 'f' || test == 'g' || test == 'h' ||
		test == 'i' || test == 'j' || test == 'k' || test == 'l' ||
		test == 'm' || test == 'n' || test == 'o' || test == 'p' ||
		test == 'q' || test == 'r' || test == 's' || test == 't' ||
		test == 'u' || test == 'v' || test == 'w' || test == 'x' || test == 'y' || test == 'z' || test == '_');
}

//returns true if uppercase case character
bool isUpperCharacter(char test)
{
	return (test == 'A' || test == 'B' || test == 'C' || test == 'D' ||
		test == 'E' || test == 'F' || test == 'G' || test == 'H' ||
		test == 'I' || test == 'J' || test == 'K' || test == 'L' ||
		test == 'M' || test == 'N' || test == 'O' || test == 'P' ||
		test == 'Q' || test == 'R' || test == 'S' || test == 'T' ||
		test == 'U' || test == 'V' || test == 'W' || test == 'X' || test == 'Y' || test == 'Z');
}

//returns if it is a white space character
bool isWhiteSpace(char test)
{
	return (test == ' ' || test == '\t' || test == '\n');
}

char peekSecondNextChar(std::ifstream & filestream) {
    char firstChar = filestream.get(); // Get the next character (this will be the first character we're "peeking" over)
    if (filestream.eof()) { // Check if we've hit the end of the file
        return EOF; // Return a special value or handle this case as needed
    }
    char secondChar = filestream.get(); // Get the second character
    if (filestream.eof()) { // Check if the second get operation hit the end of the file
        filestream.unget(); // Only one unget needed if eof was reached here
        return EOF; // Return a special value or handle this case as needed
    }
    filestream.unget(); // Put back the second character
    filestream.unget(); // Put back the first character

    return secondChar; // Return the second character we "peeked" at
}


//advance places whatever is in the "next" variables into the "current" variables and then finds what the next variables are supposed to be. Next variables are things we are looking ahead at.
void Scanner::advance()
{
	currents = nexts;
	currenttt = nexttt;
	linecurrent = linenext;


	//set that the scanner has not picked something yet. We will use this later on.
	nexttt = NONE;

	//holds what is currently read in but not yet processed
	string buffer;

	bool start = true;
	while (start)
	{
		start = false;

		buffer = "";

		//add the first thing to the buffer
		addToBuffer(buffer, filestream);

		
		//if the first thing is a {, then say we have an LBrace and set the string representation of it to "{"
		if (buffer[0] == '{')
		{
			nexttt = LBRACE;
			nexts = "{";
		}
		else if (buffer[0] == '}')
		{
			nexttt = RBRACE;
			nexts = "}";
		}
		else if (buffer[0] == '(')
		{
			nexttt = LPAREN;
			nexts = "(";
		}
		else if (buffer[0] == ')')
		{
			nexttt = RPAREN;
			nexts = ")";
		}
		else if (buffer[0] == '+')
		{
			nexttt = PLUS;
			nexts = "+";
		}
		else if (buffer[0] == '/')
		{
			nexttt = DIVIDE;
			nexts = "/";
		}
		else if (buffer[0] == '*')
		{
			nexttt = MULTIPLY;
			nexts = "*";
		}
		else if (buffer[0] == '%')
		{
			nexttt = MOD;
			nexts = "%";
		}
		else if (buffer[0] == '&')
		{
			nexttt = AND;
			nexts = "&";
		}
		else if (buffer[0] == '|')
		{
			nexttt = OR;
			nexts = "|";
		}
		else if (buffer[0] == ',')
		{
			nexttt = COMMA;
			nexts = ",";
		}
		else if (buffer[0] == '!')
		{
			nexttt = NOT;
			nexts = "!";
		}
		else if (buffer[0] == ';')
		{
			nexttt = SEMI;
			nexts = ";";
		}
		else if (buffer[0] == '=')
		{
			//this one is harder because you have to determine if you have an = or if you have ==

			addToBuffer(buffer, filestream);
			if (buffer[1] == '=') //check if both are =
			{
				//if yes then you know you have an ==
				nexttt = EE;
				nexts = "==";
			}
			else //otherwise remove the "bad" character from the buffer and just use =
			{
				removeFromBuffer(buffer, filestream);
				nexttt = EQUALASSIGN;
				nexts = "=";
			}
		}
		else if (buffer[0] == '>')
		{
			addToBuffer(buffer, filestream);
			if (buffer[1] == '=') //check if both are =
			{
				//if yes then you know you have an ==
				nexttt = GRE;
				nexts = ">=";
			}
			else //otherwise remove the "bad" character from the buffer and just use =
			{
				removeFromBuffer(buffer, filestream);
				nexttt = GR;
				nexts = ">";
			}
		}
		else if (buffer[0] == 0) //add buffer puts a null char if the file is empty
		{
			nexttt = ENDOFFILE;
			nexts = "eof";
		}//here is for a string. It requres to start with a lowercase or uppercase (_ is marked as a lowercase letter) then the remainder can be lower/upper/ or nums
		else if (isLowerCharacter(buffer[0]) || isUpperCharacter(buffer[0]))
		{
			addToBuffer(buffer, filestream);
			while (isLowerCharacter(buffer[buffer.size() - 1]) || isUpperCharacter(buffer[buffer.size() - 1]) || isNum(buffer[buffer.size() - 1]))
			{
				addToBuffer(buffer, filestream);
			}
			removeFromBuffer(buffer, filestream);

			nexttt = STRING;
			nexts = buffer;
			
		}
		
		else if (buffer[0] == '-') {
			char nextChar = filestream.peek();
			// Check if the next character is not a digit and not a '.'
			if (!isNum(nextChar) && nextChar != '.') {
				nexttt = MINUS; // Assign MINUS token if '-' is alone
				nexts = "-";
			} else {
				buffer.clear(); // Clear to restart buffer for number parsing
				buffer += '-'; // Re-add the minus sign to buffer
				bool hasDecimal = false;
				addToBuffer(buffer, filestream); // Add the digit or '.' after '-'
				while (!filestream.eof()) {
					nextChar = filestream.peek();
					if (isNum(nextChar) || (!hasDecimal && nextChar == '.')) {
						if (nextChar == '.') {
							hasDecimal = true; // we've encountered a decimal point
						}
						addToBuffer(buffer, filestream);
					} else {
						break; // No more valid characters for a number
					}
				}
				if (hasDecimal && buffer.back() == '.') {
					removeFromBuffer(buffer, filestream);
					dealWithError(buffer);
					return;
				} else {
					nexttt = FLOAT;
					nexts = buffer;
				}
			}
		}
		else if (isNum(buffer[0])) { //positive numbers 
			bool hasDecimal = false;
			addToBuffer(buffer, filestream);
			
			while (!filestream.eof()) {
				char nextChar = filestream.peek();
				if (isNum(nextChar) || (!hasDecimal && nextChar == '.')) {
					if (nextChar == '.') {
						hasDecimal = true; //we've found a decimal point
					}
					addToBuffer(buffer, filestream);
				} else {
					break; 
				}
			}
			if (hasDecimal && buffer.back() == '.') {
				removeFromBuffer(buffer, filestream); 
				dealWithError(buffer);
				return;
			} else {
				nexttt = FLOAT;
				nexts = buffer;
			}
		}

		else
		{

			//nothing matched so far //// white space and error checking
			if(nexttt == NONE)
			{
			
				//white space
				if (isWhiteSpace(buffer[0]))
				{
					while (isWhiteSpace(buffer[buffer.size() - 1]))
					{
						
						if (buffer[buffer.size() - 1] == '\n')
						{
							linenext++;
						}
						addToBuffer(buffer, filestream);
					}
					removeFromBuffer(buffer, filestream);
					start = true;
				}
				else
				{
					//or is an error character.
					dealWithError(buffer);
				}
			}
		}
	}
	/*cout << "***"<<endl;
	cout << linecurrent << " " << currentTokenString()<<endl;
	cout << linenext << " " << nextTokenString() << endl;
	cout << "***" << endl;*/
}

//this function should be called if you know an error character is currently in the buffer
void Scanner::dealWithError(string buffer)
{
	while (!isWhiteSpace(buffer[buffer.size() - 1]) && buffer[buffer.size() - 1] != 0)
	{
		addToBuffer(buffer, filestream);
	}
	removeFromBuffer(buffer, filestream);
	nexttt = ERROR;
	nexts = "IT2: Invalid Token detected on line: " + to_string(linenext) + " [ " + buffer + " ]";
}


//returns the current line number
int Scanner::getLine()
{
	return linecurrent;
}