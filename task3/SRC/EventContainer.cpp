#include "EventContainer.h"

/*EventContainer::EventContainer(tm tm_time, int mils, string username, string action, int volume, int barelVolume, int waterLevel)
{

}*/
EventContainer::EventContainer(const EventContainer& e)
{
	this->action = e.action;
	this->barrelVolume = e.barrelVolume;
	this->currentWaterLevel = e.currentWaterLevel;
	this->isSuccess = e.isSuccess;
	this->ms = e.ms;
	this->timePoint = e.timePoint;
	this->username = e.username;
	this->volume = e.volume;
	this->initialWaterLevel = e.initialWaterLevel;
}
EventContainer::EventContainer(string raw, int bv, int cwl)
{
	this->barrelVolume = bv;
	this->currentWaterLevel = cwl;
	char buf1[50] = { '\0' };
	char buf2[50] = { '\0' };
	struct tm tmtime = { 0 };
	tmtime.tm_isdst = -1;
	sscanf(raw.c_str(), FORMAT,
		&tmtime.tm_year, &tmtime.tm_mon, &tmtime.tm_mday,			//DATE
		&tmtime.tm_hour, &tmtime.tm_min, &tmtime.tm_sec, &ms,	//TIME
		buf1, buf2, &volume); //username action volume
	tmtime.tm_year -= 1900;
	tmtime.tm_mon -= 1;
	time_t t = mktime(&tmtime);
	chrono::system_clock::time_point chronoT = chrono::system_clock::from_time_t(t);
	t = chrono::system_clock::to_time_t(chronoT);
	chronoT += chrono::milliseconds(this->ms);
	this->timePoint = chronoT;
	this->username = string(buf1);
	this->action = string(buf2);
	if (this->action.compare(TOPUP) == 0)
	{
		if ((this->currentWaterLevel + this->volume) < this->barrelVolume)
		{
			isSuccess = true;
			this->currentWaterLevel += this->volume;
		}
		else
		{
			isSuccess = false;
		}
	}
	else
	{
		if ((this->currentWaterLevel - this->volume) > 0)
		{
			isSuccess = true;
			this->currentWaterLevel -= this->volume;
		}
		else
		{
			isSuccess = false;
		}
	}

}
string EventContainer::Getusername()
{
	return this->username;
}
string EventContainer::GetAction()
{
	return this->action;
}
chrono::system_clock::time_point EventContainer::GetTime()
{
	return this->timePoint;
}
int EventContainer::GetMs()
{
	return this->ms;
}
int EventContainer::GetBarrelVolume()
{
	return this->barrelVolume;
}
int EventContainer::GetWaterLevel()
{
	return this->currentWaterLevel;
}
int EventContainer::GetVolume()
{
	return this->volume;
}
bool EventContainer::IsSuccess()
{
	return this->isSuccess;
}
string EventContainer::ToFormatedString()
{
	char buf[100] = { '\0' };
	struct tm tmTime = { 0 };
	time_t tTime;
	tTime = chrono::system_clock::to_time_t(this->timePoint);
	tmTime = *localtime(&tTime);
	snprintf(buf, 100, "%d-%.2d-%.2dT%.2d:%.2d:%.2d.%.2dZ -[%s] -%s%dl",
		tmTime.tm_year + 1900, tmTime.tm_mon + 1, tmTime.tm_mday,			//DATE
		tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec, ms,	//TIME
		username.c_str(), action.c_str(), volume);
	return string(buf);
}

EventContainer EventContainer::GenerateRandomShiftedForward()
{
	EventContainer e(*this);
	srand(time(0));
	int minutes = rand()%60;
	int seconds = rand() % 60;
	int mseconds = rand() % 274 - 137;
	e.timePoint += chrono::minutes(minutes) +
		chrono::seconds(seconds) + chrono::milliseconds(mseconds);

	std::chrono::duration<double> msc = e.timePoint -
		std::chrono::system_clock::from_time_t(chrono::system_clock::to_time_t(e.timePoint));
	//   Then print out that double using whatever format you prefer.
	e.ms = msc.count()*1000;
	e.action = (rand() % 2 || rand() % 2) ? SCOOP : TOPUP;
	e.volume = rand() % 30 + rand() % 10 + rand() % 10;
	if (e.action.compare(TOPUP) == 0)
	{
		if ((e.currentWaterLevel + this->volume) < this->barrelVolume)
		{
			e.isSuccess = true;
			e.currentWaterLevel += e.volume;
		}
		else
		{
			e.isSuccess = false;
		}
	}
	else
	{
		if ((e.currentWaterLevel - e.volume) > 0)
		{
			e.isSuccess = true;
			e.currentWaterLevel -= e.volume;
		}
		else
		{
			e.isSuccess = false;
		}
	}
	
	return e;
}

void EventContainer::SetWaterLevel(int nl)
{
	this->currentWaterLevel = nl;
}
void EventContainer::SetInitialWaterLevel(int v)
{
	this->initialWaterLevel = v;
}
int EventContainer::GetInitialWaterLevel()
{
	return this->initialWaterLevel;
}