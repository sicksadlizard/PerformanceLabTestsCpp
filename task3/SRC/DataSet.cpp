#include "DataSet.h"

DataSet::DataSet(string path)
{
	try
	{
		ifstream ifs(path);
		if (!ifs.is_open()) throw(std::runtime_error("Cannot open file!"));
		string result;
		getline(ifs, result);
		getline(ifs, result);
		this->barrelVol = atoi(result.c_str());
		getline(ifs, result);
		this->waterLevel = atoi(result.c_str());
		this->initialWaterLevel = this->waterLevel;
		/*	tm_sec	int	seconds after the minute	0-61*
			tm_min	int	minutes after the hour	0-59
			tm_hour	int	hours since midnight	0-23
			tm_mday	int	day of the month	1-31
			tm_mon	int	months since January	0-11
			tm_year	int	years since 1900
			tm_wday	int	days since Sunday	0-6
			tm_yday	int	days since January 1	0-365
			tm_isdst	int	Daylight Saving Time flag*/
		int yy, mm, dd, hh, min, ss, mcs, volume;
		char buf1[50];
		char buf2[50];
		while (!ifs.eof())
		{
			getline(ifs, result);
			EventContainer e(result, this->barrelVol, this->waterLevel);
			if (e.IsSuccess())
			{
				if (e.GetAction().compare(SCOOP) == 0)
				{
					e.SetInitialWaterLevel(this->waterLevel);
					this->waterLevel -= e.GetVolume();
					e.SetWaterLevel(this->waterLevel);
				}
				else
				{
					e.SetInitialWaterLevel(this->waterLevel);
					this->waterLevel += e.GetVolume();
					e.SetWaterLevel(this->waterLevel);
				}
			}
			this->ecList.push_back(e);
		}
		ifs.close();
		if (ecList.size() == 0) throw(std::runtime_error("No entities detected!"));
	}
	catch (exception e)
	{
		cout << "Dataset exception!" << endl << e.what() << endl;
	}

}
void DataSet::GenerateTestFile() 
{
	int byteWritten = 0;
	ofstream ofs;
	string out;
	ofs.open("RandomTable.txt");
	if (!ofs.is_open()) return;
	out = "META DATA:";
	
	ofs << out <<endl;
	byteWritten += out.length() + 1;

	out.clear();
	out = to_string(this->barrelVol);
	
	ofs << out << endl;
	byteWritten += out.length() + 1;

	out.clear();
	out = to_string(this->waterLevel);

	ofs << out << endl;
	byteWritten += out.length() + 1;
	EventContainer e(ecList.front());
	while (byteWritten < 1048576 && ofs.is_open())
	{
		e = e.GenerateRandomShiftedForward();
		out = e.ToFormatedString();
		ofs << out << endl;
		byteWritten += out.length() + 1;
	}
	ofs.close();
}
list<EventContainer> DataSet::GetEvents(time_t from, time_t to)
{
	if (ecList.size() == 0) throw(std::runtime_error("No entities parsed"));
	list<EventContainer> ecResultList;
	int curWaterLevel = this->initialWaterLevel;
	for (int i=0; i<this->ecList.size(); i++)
	{
		EventContainer e = this->ecList.front();
		if (e.IsSuccess())
		{
			string action = e.GetAction();
			if (action.compare(TOPUP) == 0)
			{
				curWaterLevel += e.GetVolume();
			}
			else
			{
				curWaterLevel -= e.GetVolume();
			}
		}
		if (e.GetTime() >= chrono::system_clock::from_time_t(from) &&
			e.GetTime() <= chrono::system_clock::from_time_t(to))
		{
			string DEBUG = e.ToFormatedString();
			ecResultList.push_back(e);
		}
		this->ecList.pop_front();
	}
	if (ecResultList.size() == 0) throw(std::runtime_error("No entities in time range!"));
	return ecResultList;
}
