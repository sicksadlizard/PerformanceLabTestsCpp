#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <time.h>
#include "EventContainer.h"
#include <list>
#include "DataSet.h"
#include "Utils.h"
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		if (Utils::bCheckArgs(argc, argv) == false)
		{
			cout << Utils::sGetUsage();
			return -1;
		}
		DataSet ds(argv[1]);
		list<EventContainer> selected = ds.GetEvents(Utils::ttParseDateTime(argv[2]), Utils::ttParseDateTime(argv[3]));
		Utils::ParseEcListToCSV(selected);
	}
	catch (exception e)
	{
		cout << "Runtime error!\n" << e.what();
	}
	return 0;
}

