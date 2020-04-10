#include "Utils.h"

time_t Utils::ttParseDateTime(string raw)
{
	struct tm tmtime = { 0 };
	tmtime.tm_isdst = -1;
	sscanf(raw.c_str(), "%d-%d-%dT%d:%d:%d",
		&tmtime.tm_year, &tmtime.tm_mon, &tmtime.tm_mday,			//DATE
		&tmtime.tm_hour, &tmtime.tm_min, &tmtime.tm_sec);
	tmtime.tm_year -= 1900;
	tmtime.tm_mon -= 1;
	time_t t = mktime(&tmtime);
	return t;
}
void Utils::ParseEcListToCSV(list<EventContainer> ecList)
{
	
	int topUpActions = 0;
	float topUpFailRate = 0;
	int pouredVol = 0;
	int failedToPourVol = 0;

	int scoopActions = 0;
	float scoopFailRate = 0;
	int scoopedVol = 0;
	int failedToScoopVol = 0;

	int initialWaterLevel = 0;
	int resultWaterLevel = 0;
	initialWaterLevel = ecList.front().GetInitialWaterLevel();
	resultWaterLevel = ecList.back().GetWaterLevel();
	for (EventContainer e : ecList)
	{
		if (e.GetAction().compare(TOPUP) == 0) 
		{ 
			topUpActions++; 
			if (e.IsSuccess())
			{
				pouredVol += e.GetVolume();
			}
			else
			{
				topUpFailRate++;
				failedToPourVol += e.GetVolume();
			}
		}
		else 
		{ 
			scoopActions++;
			if (e.IsSuccess())
			{
				scoopedVol += e.GetVolume();
			}
			else
			{
				scoopFailRate++;
				failedToScoopVol += e.GetVolume();
			}
		}

	}

	if(topUpActions > 0) topUpFailRate /= topUpActions;
	if (scoopActions > 0) scoopFailRate /= scoopActions;
	topUpFailRate *= 100;
	scoopFailRate *= 100;

	try
	{
		/*-какое количество попыток налить воду в бочку было за указанный период?
	-какой процент ошибок был допущен за указанный период?
	-какой объем воды был налит в бочку за указанныйпериод?
	-какой объем воды был не налит в бочку за указанный период?
	-... тоже самое для забора воды из бочки ...
	-какой объем воды был в бочке в начале указанного периода?
	Какой в конце указанного периода
	int topUpActions = 0;
	float topUpFailRate = 0;
	int pouredVol = 0;
	int failedToPourVol = 0;

	int scoopActions = 0;
	int scoopFailRate = 0;
	int scoopedVol = 0;
	int failedToScoopVol = 0;

	int initialWaterLevel = 0;
	int resultWaterLevel = 0;*/
		ofstream ofs;
		ofs.open("Statistic.csv");
		string sScoopFailRate = to_string(scoopFailRate);
		int commaPos = sScoopFailRate.find_first_of(',');
		if(commaPos != string::npos) sScoopFailRate[commaPos] = '.';

		string sTopUpFailRate = to_string(topUpFailRate);
		commaPos = sTopUpFailRate.find_first_of(',');

		sTopUpFailRate = sTopUpFailRate.substr(0, 4) + '%';
		sScoopFailRate = sScoopFailRate.substr(0, 4) + '%';
		if (commaPos != string::npos) sTopUpFailRate[commaPos] = '.';
		if (ofs.is_open())
		{
			ofs << "Top up attempts, Top up fail rate, Poured water volume, Failed to pour volume, Scoop attempts, Scoop fail rate, Scooped water volume, Failed to scoop volume, Initial water level, Result water level" << endl;
			ofs << topUpActions << ',' << sTopUpFailRate << ',' << pouredVol << ',' 
				<<failedToPourVol << ',' << scoopActions << ',' << sScoopFailRate << ',' 
				<< scoopedVol << ','<< failedToScoopVol <<','<< initialWaterLevel << ',' 
				<< resultWaterLevel << endl;
			ofs.close();
		}
	}
	catch (exception e)
	{
		cout << "Runtime error!\n" << e.what() << endl;
	}
}
string Utils::sGetUsage()
{
	string Usage = "task3 <path> <datetime from> <datetime to>\n";
	Usage += "<path> - filepath to parsing file\n";
	Usage += "<datetime from> <datetime to> - timestamps of the begin and the end of analyzed period in format yyyy.mm.ddThh::min::sec\n";
	return Usage;
}

bool Utils::bCheckArgs(int argc, char* argv[])
{
	int mockVal;
	if (argc < 4 ||
		sscanf(argv[2], "%d-%d-%dT%d:%d:%d", &mockVal, &mockVal, &mockVal, &mockVal, &mockVal, &mockVal) != 6 ||
		sscanf(argv[3], "%d-%d-%dT%d:%d:%d", &mockVal, &mockVal, &mockVal, &mockVal, &mockVal, &mockVal) != 6)
		return false;
	ifstream f(argv[1]);
	if (f.good() == false)
	{
		f.close();
		return false;
	}
	return true;
}