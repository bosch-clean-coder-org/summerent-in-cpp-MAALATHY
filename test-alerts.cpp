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

// Mock functions to capture the calls
bool isSendToControllerCalled = false;
bool isSendToEmailCalled = false;
BreachType capturedBreachType;

void sendToController(BreachType breachType) {
  isSendToControllerCalled = true;
  capturedBreachType = breachType;
}

void sendToEmail(BreachType breachType) {
  isSendToEmailCalled = true;
  capturedBreachType = breachType;
}

TEST_CASE("Checks and alerts the target"){
  SECTION("Sends alert to Controller if alert target is Controller"){    
    BatteryCharacter batteryChar;
    batteryChar.CoolingType = PASSIVE_COOLING;
    checkAndAlert(TO_CONTROLLER, batteryChar.CoolingType, 35.0);
    REQUIRE(isSendToControllerCalled);
    REQUIRE_FALSE(isSendToEmailCalled);
    REQUIRE(capturedBreachType == NORMAL);

    checkAndAlert(TO_CONTROLLER, batteryChar.CoolingType, 40.0);
    REQUIRE(isSendToControllerCalled);
    REQUIRE_FALSE(isSendToEmailCalled);
    REQUIRE(capturedBreachType == TOO_HIGH);

    checkAndAlert(TO_CONTROLLER, batteryChar.CoolingType, -5.0);
    REQUIRE(isSendToControllerCalled);
    REQUIRE_FALSE(isSendToEmailCalled);
    REQUIRE(capturedBreachType == TOO_LOW);
  }
}
