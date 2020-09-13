#include "ReceiverHeader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

Receiver::Receiver() {}

Receiver::Receiver(int d, int m, int y, float ha) : date(d), month(m), year(y), hourlyAverage(ha) {}

Receiver::Receiver(int dy, int dt, int m, int y, float wa) : day(dy), date(dt), month(m), year(y), weeklyAverage(wa) {}

Receiver::Receiver(int i, int hr, int min, int sec, int dy, int dt, int mon, int yr) : id(i), hour(hr), minute(min), second(sec), day(dy), date(dt), month(mon), year(yr) {}

vector<Receiver> Receiver::readSenderData()
{
	vector<Receiver> footfallData;
	string footfallRecordString;
	getline(cin, footfallRecordString);
	cout << footfallRecordString << endl;
	while (getline(cin, footfallRecordString))
	{
		cout << footfallRecordString << endl;
		footfallData = storeFootfallData(footfallRecordString, footfallData);
	}
	return footfallData;
}

vector<Receiver> Receiver::storeFootfallData(const string& footfallRecordString, vector<Receiver> footfallData)
{
	vector<int> footfallRecord;
	string footfallElement;
	stringstream footfallStream(footfallRecordString);
	while (getline(footfallStream, footfallElement, ','))
	{
		footfallRecord.push_back(stoi(footfallElement));
	}
	
	cout << "Record Pushed" << endl;
	cout << footfallRecord.size() << endl;
	Receiver receiverObj(footfallRecord[0], footfallRecord[1], footfallRecord[2], footfallRecord[3], footfallRecord[4], footfallRecord[5], footfallRecord[6], footfallRecord[7]);
	footfallData.push_back(receiverObj);
	return footfallData;
}

vector<Receiver> Receiver::averageFootfallsPerHourDaily(vector<Receiver> footfallData)
{
	vector<Receiver> hourlyAverageDailyData;
	Receiver receiverObj(footfallData[0].date, footfallData[0].month, footfallData[0].year, 0);
	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(receiverObj.date == footfallData[i].date)
		{
			receiverObj.hourlyAverage += 1;
		}
		else
		{
			receiverObj.hourlyAverage = receiverObj.hourlyAverage / 4;
			hourlyAverageDailyData.push_back(receiverObj);
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.hourlyAverage = 0;
			i--;
		}
	}
	receiverObj.hourlyAverage = receiverObj.hourlyAverage / 4;
	hourlyAverageDailyData.push_back(receiverObj);
	
	return hourlyAverageDailyData;
}

int Receiver::setFlagStatus(int day)
{
	if(day == 1)
		return 0;
	return 1;
}

vector<Receiver> Receiver::averageDailyFootfallsWeekly(vector<Receiver> footfallData)
{
	vector<Receiver> dailyAverageWeeklyData;
	Receiver receiverObj(footfallData[0].day, footfallData[0].date, footfallData[0].month, footfallData[0].year, 0);
	int flag = 0;

	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(footfallData[i].day != flag)
		{
			receiverObj.weeklyAverage += 1;
			flag = setFlagStatus(footfallData[i].day);
		}
		else
		{
			receiverObj.weeklyAverage = receiverObj.weeklyAverage / 7;
			dailyAverageWeeklyData.push_back(receiverObj);
			receiverObj.day = footfallData[i].day;
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.weeklyAverage = 0;
			flag = 0;
			i--;	
		}
	}
	receiverObj.weeklyAverage = receiverObj.weeklyAverage / 7;
	dailyAverageWeeklyData.push_back(receiverObj);
	
	return dailyAverageWeeklyData;
}

void Receiver::displayHourlyAverageDailyData(vector<Receiver> hourlyAverageDailyData)
{
	ofstream fout("test-data/Average Footfalls Hourly.csv");
	cout<<"Date "<<"Month "<<"Year "<<" Hourly Avg"<<endl;
	if(fout.is_open())
	{
		fout << "Date" << "," << "Month" << "," << "Year" << "," << "HourlyAverage" <<"\n";
		for(unsigned int i = 0; i < hourlyAverageDailyData.size(); i++)
		{
			cout<<hourlyAverageDailyData[i].date<<" "<<hourlyAverageDailyData[i].month<<" "<<hourlyAverageDailyData[i].year<<" "<<hourlyAverageDailyData[i].hourlyAverage<<endl;
			fout << hourlyAverageDailyData[i].date << "," << hourlyAverageDailyData[i].month << "," << hourlyAverageDailyData[i].year << "," << hourlyAverageDailyData[i].hourlyAverage <<"\n";
		}
	}
	fout.close();
}

void Receiver::displayDailyAverageWeeklyData(vector<Receiver> dailyAverageWeeklyData)
{
	ofstream fout("test-data/Average Footfalls Weekly.csv");
	cout<<"Date "<<"Month "<<"Year "<<" Weekly Avg"<<endl;
	if(fout.is_open())
	{
		fout << "Date" << "," << "Month" << "," << "Year" << "," << "WeeklyAverage" <<"\n";
		for(unsigned int i = 0; i < dailyAverageWeeklyData.size(); i++)
		{
			cout<<dailyAverageWeeklyData[i].date<<" "<<dailyAverageWeeklyData[i].month<<" "<<dailyAverageWeeklyData[i].year<<" "<<dailyAverageWeeklyData[i].weeklyAverage<<endl;
			fout<<dailyAverageWeeklyData[i].date<<","<<dailyAverageWeeklyData[i].month<<","<<dailyAverageWeeklyData[i].year<<","<<dailyAverageWeeklyData[i].weeklyAverage<<"\n";
		}
	}
	fout.close();
}

vector<Receiver> Receiver::peakDailyFootfallLastMonth(vector<Receiver> footfallData)
{
	vector<Receiver> dailyFootfallLastMonthData;
	vector<Receiver> footfallLastMonthData = getLastMonthFootfallData(footfallData);
	Receiver receiverObj(footfallLastMonthData[0].date, footfallLastMonthData[0].month, footfallLastMonthData[0].year, 0);
	for(unsigned int i = 0; i < footfallLastMonthData.size(); i++)
	{
		if(receiverObj.date == footfallLastMonthData[i].date)
		{
			receiverObj.dailyCount += 1;
		}
		else
		{
			dailyFootfallLastMonthData.push_back(receiverObj);
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.dailyCount = 0;
			i--;
		}
	}
	dailyFootfallLastMonthData.push_back(receiverObj);
	
	vector<Receiver> peakDailyFootfallsLastMonthData = getPeakDailyFootfallsLastMonth(dailyFootfallLastMonthData);
	
	return peakDailyFootfallsLastMonthData;
}

vector<Receiver> Receiver::getLastMonthFootfallData(vector<Receiver> footfallData)
{
	time_t currentTime = time(0);
	tm *localTime = localtime(&currentTime);
	int lastMonth = localTime->tm_mon;
	vector<Receiver> lastMonthFootfallData;
	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(lastMonth == footfallData[i].month)
		{
			lastMonthFootfallData.push_back(footfallData[i]);
		}
	}
	return lastMonthFootfallData;
}

vector<Receiver> Receiver::getPeakDailyFootfallsLastMonth(vector<Receiver> dailyFootfallLastMonthData)
{
	sort(dailyFootfallLastMonthData.begin(), dailyFootfallLastMonthData.end(), [](const Receiver& firstObj, const Receiver& secondObj)
	{
    		return firstObj.dailyCount > secondObj.dailyCount;
	});
	vector<Receiver> peakDailyFootfallsLastMonth;
	int peakCount = dailyFootfallLastMonthData[0].dailyCount;
	for(unsigned int i = 0; i < dailyFootfallLastMonthData.size(); i++)
	{
		if(peakCount == dailyFootfallLastMonthData[i].dailyCount)
		{
			peakDailyFootfallsLastMonth.push_back(dailyFootfallLastMonthData[i]);
		}
	}
	return peakDailyFootfallsLastMonth;
}

void Receiver::displayPeakDailyFootfallLastMonth(vector<Receiver> peakDailyFootfallsLastMonthData)
{
	ofstream fout("test-data/Peak Daily Footfalls Last Month.csv");
	cout<<"Date "<<"Month "<<"Year "<<"Peak Count"<<endl;
	if(fout.is_open())
	{
		fout << "Date" << "," << "Month" << "," << "Year" << "," << "PeakCount" <<"\n";
		for(unsigned int i = 0; i < peakDailyFootfallsLastMonthData.size(); i++)
		{
			cout<<peakDailyFootfallsLastMonthData[i].date<<" "<<peakDailyFootfallsLastMonthData[i].month<<" "<<peakDailyFootfallsLastMonthData[i].year<<" "<<peakDailyFootfallsLastMonthData[i].dailyCount<<endl;
			fout<<peakDailyFootfallsLastMonthData[i].date<<","<<peakDailyFootfallsLastMonthData[i].month<<","<<peakDailyFootfallsLastMonthData[i].year<<","<<peakDailyFootfallsLastMonthData[i].dailyCount<<"\n";
		}
	}
	fout.close();
}

int main()
{
	Receiver receiverObj;
	
	cout << "In receiver main" << endl;
	
	vector<Receiver> footfallData = receiverObj.readSenderData();
	
	vector<Receiver> averageFootfallsPerHourDailyResult = receiverObj.averageFootfallsPerHourDaily(footfallData);
	receiverObj.displayHourlyAverageDailyData(averageFootfallsPerHourDailyResult);
	
	vector<Receiver> averageDailyFootfallsWeeklyResult = receiverObj.averageDailyFootfallsWeekly(footfallData);
	receiverObj.displayDailyAverageWeeklyData(averageDailyFootfallsWeeklyResult);
	
	vector<Receiver> peakDailyFootfallLastMonthResult = receiverObj.peakDailyFootfallLastMonth(footfallData);
	receiverObj.displayPeakDailyFootfallLastMonth(peakDailyFootfallLastMonthResult);
	
	return 0;
}
