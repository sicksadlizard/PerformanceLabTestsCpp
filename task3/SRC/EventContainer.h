#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FORMAT "%d-%d-%dT%d:%d:%d.%dZ -[%[a-z, A-Z, 0-9%]] -%[a-z ] %i"
#include <chrono>
#include <string>
#include <time.h>
#include <iostream>
#include <cstdlib>
#define TOPUP "wanna top up "
#define SCOOP "wanna scoop "
using namespace std;
class EventContainer
{
private:
	string username;
	string action;
	chrono::system_clock::time_point timePoint;
	int ms = 0;
	int barrelVolume = 0;
	int currentWaterLevel = 0;
	int volume = 0;
	bool isSuccess = false;
	int initialWaterLevel = 0;
public:
	//EventContainer(tm tm_time, int mils, string username, string action, int volume, int barelVolume, int waterLevel);
	string Getusername();
	string GetAction();
	chrono::system_clock::time_point GetTime();
	int GetMs();
	int GetBarrelVolume();
	int GetInitialWaterLevel();
	int GetWaterLevel();
	int GetVolume();
	bool IsSuccess();
	void SetWaterLevel(int);
	void SetInitialWaterLevel(int);
	EventContainer(const EventContainer&);
	EventContainer(string raw, int bv, int cwl);
	string ToFormatedString();
	EventContainer GenerateRandomShiftedForward();
};

