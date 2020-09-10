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
    while (getline(file, line))
    {
        // used for breaking words
        std::stringstream str(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        std::vector<std::string> vec;
        while (getline(str, data, ',')) {
            // add all the column data
            // of a row to a vector vec
            vec.push_back(data);
        }
        dataList.push_back(vec);
     }
    file.close();
    return dataList;
}
void printdata(std::vector<std::vector<std::string>> &dataList)
{
      for (std::vector<std::string> vec : dataList)
    {
        for (std::string data : vec)
        {
            std::cout << data << ",";
        }
        std::cout << std::endl; 
     }
}
int main()
{
    // Creating an object of CSVfile reader
    CSVReader filereader("test-data/visitdata1.csv",",");
    // Get the data from CSV File
    std::vector<std::vector<std::string> > dataList = filereader.fetchData();
    // Print the content
    printdata(dataList);
    return 0;
}
