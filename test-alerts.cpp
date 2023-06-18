#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("classifies the Temperature Breach according to CoolingType and Temperature in Celsius"){
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35.0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40.0) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5.0) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45.0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50.0) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -5.0) == TOO_LOW);

  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40.0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45.0) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5.0) == TOO_LOW);  
}

TEST_CASE("Checks and alerts the target"){
  SECTION("Sends alert to Controller if alert target is Controller"){    
    // Redirect stdout to a stringstream for capturing the output.
    std::stringstream output;
    std::streambuf* oldBuffer = std::cout.rdbuf(output.rdbuf());
    std::cout.rdbuf(oldBuffer);    // Restore stdout.

    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(TO_CONTROLLER, batteryChar, 35.0);
    //std::string expectedOutput = "feed : 0\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // NORMAL BreachType

    checkAndAlert(TO_CONTROLLER, batteryChar, 40.0);
    //expectedOutput = "feed : 2\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_HIGH BreachType

    checkAndAlert(TO_CONTROLLER, batteryChar, -5.0);
    //expectedOutput = "feed : 1\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_LOW BreachType

    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(TO_CONTROLLER, batteryChar, 45.0);
    //expectedOutput = "feed : 0\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // NORMAL BreachType

    checkAndAlert(TO_CONTROLLER, batteryChar, 50.0);
    //expectedOutput = "feed : 2\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_HIGH BreachType

    checkAndAlert(TO_CONTROLLER, batteryChar, -5.0);
    //expectedOutput = "feed : 1\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_LOW BreachType

    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(TO_CONTROLLER, batteryChar, 40.0);
    //expectedOutput = "feed : 0\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // NORMAL BreachType

    checkAndAlert(TO_CONTROLLER, batteryChar, 45.0);
    //expectedOutput = "feed : 2\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_HIGH BreachType

    checkAndAlert(TO_CONTROLLER, batteryChar, -5.0);
    //expectedOutput = "feed : 1\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_LOW BreachType
  }

  SECTION("Sends alert via EMAIL if alert target is EMAIL"){    
    // Redirect stdout to a stringstream for capturing the output.
    std::stringstream output;
    std::streambuf* oldBuffer = std::cout.rdbuf(output.rdbuf());
    std::cout.rdbuf(oldBuffer);    // Restore stdout.

    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(TO_EMAIL, batteryChar, 35.0);
    //std::string expectedOutput = "feed : 0\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // NORMAL BreachType

    checkAndAlert(TO_EMAIL, batteryChar, 40.0);
    //expectedOutput = "feed : 2\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_HIGH BreachType

    checkAndAlert(TO_EMAIL, batteryChar, -5.0);
    //expectedOutput = "feed : 1\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_LOW BreachType

    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(TO_EMAIL, batteryChar, 45.0);
    //expectedOutput = "feed : 0\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // NORMAL BreachType

    checkAndAlert(TO_EMAIL, batteryChar, 50.0);
    //expectedOutput = "feed : 2\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_HIGH BreachType

    checkAndAlert(TO_EMAIL, batteryChar, -5.0);
    //expectedOutput = "feed : 1\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_LOW BreachType

    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(TO_EMAIL, batteryChar, 40.0);
    //expectedOutput = "feed : 0\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // NORMAL BreachType

    checkAndAlert(TO_EMAIL, batteryChar, 45.0);
    //expectedOutput = "feed : 2\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_HIGH BreachType

    checkAndAlert(TO_EMAIL, batteryChar, -5.0);
    //expectedOutput = "feed : 1\n";
    //REQUIRE_THAT(output.str(), Catch::Equals(expectedOutput));  // TOO_LOW BreachType
  }
}
