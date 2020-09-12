#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include<sstream>
#include <algorithm>
#include "SenderHeader.h"

std::vector<std::vector<std::string> > CSVReader::fetchActualFootfallData()
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

std::vector<int> getValidRow(std::vector<std::string>& rowvec)
{
	std::vector<int> validRow;
	for (std::string data : rowvec)
       		 {
            		if(isnumber(data)==true)
			validRow.push_back(std::stoi(data));
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
      for (std::vector<int> vec : data)
    {
        for (int rowdata : vec)
        {
            std::cout << rowdata << ",";
        }
        std::cout << std::endl; 
     }
}
bool Test::fetchValidateandPrintFootfallData(std::string filename,std::string outputname)
{	
   // Creating an object of CSVfile reader
	CSVReader filereader1(filename,",");
	//CSVReader filereader2(outputname,",");
    // Get the data from CSV File
    std::vector<std::vector<std::string>> actualdata  = filereader1.fetchActualFootfallData();
    std::vector<std::vector<int>> validData  = removeInvalidEntries(actualdata); //removes rows containing empty data or junk values(like character strings) or negative numbers
    // Print the content
    printValiddata(validData);
	fstream fin;  
        fin.open(outputname);
	//std::vector<std::vector<std::string>> output = 	filereader2.fetchActualFootfallData();
	std::vector<std::vector<int>> intoutput;
	std::string line1 = "";
    	std::string data1 = "";
	while (getline(fin, line1))
    	{
		std::stringstream str1(line1);
		std::vector<int> vec;
		while (getline(str1, data1, ','))
		{
		    vec.push_back(std::stoi(data1));
		}
		intoutput.push_back(vec);
     	}
    	fin.close();
	/*for (std::vector<std::string> vec : output)
   	{
        	std::vector<int> v;
		for (std::string rowvec : vec)
       	 	{
            	v.push_back(std::stoi(rowvec));
        	}
        	intoutput.push_back(v); 
  	}*/
    return {std::equal(validData.begin(), validData.end(), intoutput.begin())};
	
    
}

/*int main()
{
    std::cout<<Test::fetchValidateandPrintFootfallData("test-data/samplevisit1.csv")<<std::endl;
    return 0;
}*/
