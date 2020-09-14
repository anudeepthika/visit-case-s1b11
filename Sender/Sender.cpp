#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include<sstream>
#include <algorithm>
#include "SenderHeader.h"

std::vector<std::vector<std::string>> CSVReader::fetchActualFootfallData()
{
    std::fstream file;
    std::vector<std::vector<std::string>> footfallData;
    std::string line = "";
    std::string data = "";
    // Iterate through each line and split the content using delimeter
    file.open(fileName);
    getline(file,line);
    //std::cout<<line<<std::endl;
    while (getline(file, line))
    {
        // used for breaking words
        std::stringstream str(line);

        // read every column data of a row and store it in a string variable, 'data'
        std::vector<std::string> footfallEntry; //one footfall data
        while (getline(str, data, ','))
        {
            // add all the column data
            // of a row to a vector vec
            footfallEntry.push_back(data);
        }
        footfallData.push_back(footfallEntry);
     }
    file.close();
    return footfallData;
}

bool isnumber(std::string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
	if (isdigit(s[i]) == false)
		return false;

    return true;    
}

std::vector<int> getValidRow(std::vector<std::string>& rowvec)
{
	std::vector<int> validRow;
	for (std::string data : rowvec)
       		 {
            		if(isnumber(data)==true)
			validRow.push_back(stoi(data));
        	 }
	return validRow;
}


std::vector<std::vector<int>> removeInvalidEntries(std::vector<std::vector<std::string>>& actualdata)
{
	std::vector<std::vector<int>> validdata;
	for(std::vector<std::string> vec:actualdata)
	{
		std::vector<int> ValidRow = getValidRow(vec);
	if(ValidRow.size()==8)
		validdata.push_back(ValidRow);
	}
	return validdata;
}

void printValiddata(std::vector<std::vector<int>> &data)
{
    std::ofstream fout;
	fout.open("OutputSenderTestData/visitdataout1.txt");
	std::cout<<"id,hour,minute,second,day,date,month,year"<<std::endl;
	fout << "id" << "," << "hour" << "," << "minute" << "," << "second" << "," << "day" << "," << "date" <<"," << "month" <<"," << "year" <<"\n";
      for (std::vector<int> vec : data)
    {
        for (int rowdata : vec)
        {
            std::cout << rowdata << ",";
		fout << rowdata << ",";
        }
	      fout<<"\n";
        std::cout << std::endl; 
     }
	fout.close();
}
void Test::fetchValidateandPrintFootfallData(std::string filename)
{	
   // Creating an object of CSVfile reader
	CSVReader filereader(filename,",");
    // Get the data from CSV File
    std::vector<std::vector<std::string>> actualdata  = filereader.fetchActualFootfallData();
    std::vector<std::vector<int>> validData  = removeInvalidEntries(actualdata); //removes rows containing empty data or junk values(like character strings) or negative numbers
    // Print the content
    // data is now only non-negative integer because person id, date time are non negative integers
	int halfofFetchedEntriesfromSensorData = actualdata.size()/2;
	int totalValidEntries = validData.size();
	if(totalValidEntries < halfofFetchedEntriesfromSensorData)
	{
		std::ofstream fout;
		fout.open("OutputSenderTestData/visitdataout1.txt");
		std::cout<<"No valid data"<<std::endl;
		fout<<"\n";
		fout.close();
	}
	else
    		printValiddata(validData);
}
/*int main()
{
    Test::fetchValidateandPrintFootfallData("test-data/visitdata2.csv");
    return 0;
}*/
