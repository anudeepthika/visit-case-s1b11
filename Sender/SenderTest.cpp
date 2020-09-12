#define CATCH_CONFIG_RUNNER  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "SenderHeader.h"
#include<vector>
#include <cmath>

TEST_CASE("when footfall data containing invalid data is read by sender then it prints the valid data") 
{
    auto b = Test::fetchValidateandPrintFootfallData("test-data/samplevisit1.csv");
    REQUIRE(b==true);
}

