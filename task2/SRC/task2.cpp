#include <iostream>
#include <fstream>
#include <string>
#include "Entity.h"
#include "Parser.h"
using namespace std;

string getFileContent(string path);

int main(int argc, char** argv)
{
	try
	{
		string fileContent = getFileContent(argv[1]);
		//DEBUG
		Entity* e = Parser::ParseInputString(fileContent);
		e->StolenSolve();
		delete e;
	}
	catch (exception& e)
	{
		cout << "Runtime error!\n" << e.what() << endl;
	}
}

string getFileContent(string path)
{
	string result;
	try
	{
		ifstream ifs(path);
		if (!ifs.is_open()) throw runtime_error("Cannot create stream!");
		getline(ifs, result);
		if (result.empty()) throw runtime_error("File is empty!");
		ifs.close();
	}
	catch (exception& e)
	{
		cout << "Error opening/reading file!\n" << e.what();
	}

	return result;
}