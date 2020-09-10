#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include<sstream>
#include <algorithm>
#include "Sender.h"

std::vector<std::vector<std::string> > CSVReader::fetchData()
{
    std::fstream file;
    std::vector<std::vector<std::string> > dataList;
    std::string line = "";
    std::string data = "";
    // Iterate through each line and split the content using delimeter
    file.open(fileName);
    getline(file,line);
    std::cout<<line<<std::endl;
    while (getline(file, line))
    {
        // used for breaking words
        std::stringstream str(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        std::vector<std::string> vec;
        while (getline(str, data, ','))
        {
            // add all the column data
            // of a row to a vector vec
            vec.push_back(data);
        }
        dataList.push_back(vec);
     }
    file.close();
    return dataList;
}

bool isnumber(std::string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;    
}

std::vector<int> getrow(std::vector<std::string>& rowvec)
{
	std::vector<int> row;
	for (std::string data : rowvec)
       		 {
            		if(isnumber(data)==true)
			row.push_back(stoi(data));
        	 }
	return row;
}


std::vector<std::vector<int>> removeinvalidentries(std::vector<std::vector<std::string>>& actualdata)
{
	std::vector<std::vector<int>> validdata;
	for(std::vector<std::string> vec:actualdata)
	{
		std::vector<int> rowvector = getrow(vec);
	if(rowvector.size()==8)
		validdata.push_back(rowvector);
	}
	return validdata;
}

void printdata(std::vector<std::vector<int>> &data)
{
      for (std::vector<int> vec : data)
    {
        for (int rowdata : vec)
        {
            std::cout << rowdata << ",";
        }
        std::cout << std::endl; 
     }
}
int main()
{
    // Creating an object of CSVfile reader
    CSVReader filereader("test-data/visitdata1.csv",",");
    // Get the data from CSV File
    std::vector<std::vector<std::string>> actualdata  = filereader.fetchData();
    std::vector<std::vector<int>> validData  = removeinvalidentries(actualdata); //removes rows containing empty data or junk values(like character strings) or negative numbers
    // Print the content
    
    printdata(validData);
    return 0;
}
