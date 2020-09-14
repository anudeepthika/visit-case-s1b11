#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "SenderHeader.h"#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

TEST_CASE("when footfall data containing invalid data is read by sender then it prints the valid data") 
{
     Test::fetchValidateandPrintFootfallData("test-data/visitdata1.csv");
     std::ifstream fin1("OutputSenderTestData/visitdataouttest1.csv");
    std::string testDataBuffer((istreambuf_iterator<char>(fin1)), istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.csv");
    std::string obtainedDataBuffer((istreambuf_iterator<char>(fin2)), istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testDataBuffer == obtainedDataBuffer);
    
}

