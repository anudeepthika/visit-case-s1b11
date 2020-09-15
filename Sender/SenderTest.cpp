#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "SenderHeader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

TEST_CASE("when footfall data containing all valid data is read by sender then it prints all the valid data") 
{
     Sender::fetchValidateandPrintFootfallData("test-data/visitdata1.csv");
     std::ifstream fin1("OutputSenderTestData/visitdataouttest1.txt"); //testing data which has the output that is to be obtained
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); //visitdataout1.csv is the file to which sender writes
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testData == obtainedData);    
}

TEST_CASE("when footfall data containing some invalid data is read by sender then it prints the valid data only and removes invalid data") 
{
     Sender::fetchValidateandPrintFootfallData("test-data/visitdata2.csv");
     std::ifstream fin1("OutputSenderTestData/visitdataouttest1.txt");
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt");
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testData == obtainedData);    
}

TEST_CASE("when footfall data containing large number of more invalid data is read by sender then it prints No valid data to console") 
{
     Sender::fetchValidateandPrintFootfallData("test-data/invalidvisitdata1.csv");
     /*std::ifstream fin1("OutputSenderTestData/nodata.txt");
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();*/
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt");
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(obtainedData == "No valid data");    
}

TEST_CASE("when a non-existing footfall data csv file is read by sender then it prints file doesn't exist to console") 
{
     Sender::fetchValidateandPrintFootfallData("test-data/xyz.csv");
     /*std::ifstream fin1("OutputSenderTestData/nodata.txt");
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();*/
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt");
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(obtainedData == "file doesn't exist");    
}
TEST_CASE("reconcile") 
{
     Sender::fetchValidateReconcileandPrintFootfallData("test-data/visitdata2.csv","test-data/manuallog2.csv");
     
    std::ifstream fin1("OutputSenderTestData/reconciletest.txt");
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt");
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testData == obtainedData);    
}
