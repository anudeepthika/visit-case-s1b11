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
    std::vector<std::vector<std::string>> fetchActualFootfallData();
};

namespace Sender
{
void fetchValidateandPrintFootfallData(std::string);
}
