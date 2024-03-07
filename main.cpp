#include "Scanner.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{


	if (argc < 2)
	{
		cout << "Usage: <executable name> <filename>";
	}

	//the constructor reads the entire file at this present moment. Eventually this won't be the case, but while we test the scanner it is necessary
	Scanner scan(argv[1]);

	//cin.ignore();
}


