#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "visit-case-s1b11/catch.hpp"
#include "SenderHeader.h"
#include<vector>
#include <cmath>

TEST_CASE("when footfall data containing invalid data is read by sender then it prints the valid data") 
{
    REQUIRE(fetchValidateandPrintFootfallData("test-data/samplevisit1.csv")==true);
}

