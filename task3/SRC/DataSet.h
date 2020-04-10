#pragma once
#include "EventContainer.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

class DataSet
{
public:
	int barrelVol;
	int waterLevel;
	int initialWaterLevel;
	list<EventContainer> ecList;
	DataSet(string path);
	void GenerateTestFile();
	list<EventContainer> GetEvents(time_t from, time_t to);
};

