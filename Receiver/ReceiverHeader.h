#pragma once
#include <vector>
#include <string>

using namespace std;

class Receiver
{
private:
	vector<Receiver> footfallData;
	int id = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
	int day = 0;
	int date;
	int month;
	int year;
	float hourlyAverage = 0;
public:
	Receiver();
	Receiver(int, int, int, float);
	Receiver(int, int, int, int, int, int, int, int);
	void readSenderData();
	void storeFootfallData(const string&);
	void averageFootfallsPerHourDaily();
	void displayhourlyAverageDailyData(vector<Receiver>);
	//float averageDailyFootfallsWeekly();
	//float peakDailyFootfallLastMonth();
};
