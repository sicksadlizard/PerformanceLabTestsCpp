#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <time.h>
#include <string>
#include <list>
#include "EventContainer.h"
#include <fstream>
using namespace std;
class Utils
{
public:
	static time_t ttParseDateTime(string);
	static void ParseEcListToCSV(list<EventContainer>);
	static string sGetUsage();
	static bool bCheckArgs(int argc, char*argv[]);
};

