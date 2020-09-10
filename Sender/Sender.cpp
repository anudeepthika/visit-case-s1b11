#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include<sstream>
#include <algorithm>

class CSVReader
{
    std::string fileName;
    std::string delimeter;
public:
    CSVReader(const std::string& filename, const std::string& delim = ",") : fileName(filename), delimeter(delim) { }
    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string>> fetchData();
};
std::vector<std::vector<std::string> > CSVReader::fetchData()
{
    //std::ifstream file(fileName);
    std::fstream file;
    std::vector<std::vector<std::string> > dataList;
    std::string line = "";
   // std::string temp = "";
    std::string data = "";
    // Iterate through each line and split the content using delimeter
    file.open(fileName);
    while (getline(file, line))
    {

        // read an entire row and
        // store it in a string variable 'line'
        

        // used for breaking words
        std::stringstream str(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        std::vector<std::string> vec;
        while (getline(str, data, ',')) {

            // add all the column data
            // of a row to a vector
            vec.push_back(data);
        }
        dataList.push_back(vec);
     }
    file.close();
    return dataList;
}
int main()
{
    // Creating an object of CSVWriter
    CSVReader filereader("test-data/visitdata1.csv",",");
    // Get the data from CSV File
    std::vector<std::vector<std::string> > dataList = filereader.fetchData();
    // Print the content of row by row on screen
    for (std::vector<std::string> vec : dataList)
    {
        for (std::string data : vec)
        {
            std::cout << data << ",";
        }
        std::cout << std::endl;
    }
    return 0;
}
