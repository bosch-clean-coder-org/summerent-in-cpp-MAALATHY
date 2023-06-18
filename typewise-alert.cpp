#include "typewise-alert.h"
#include <stdio.h>

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {

const int temperatureLimits[3] = {
  35,   // PASSIVE_COOLING
  45,   // HI_ACTIVE_COOLING
  40    // DEFAULT_COOLING
};
  int coolingTypeIndex = coolingType;
  int lowerLimit = 0;
  int upperLimit = temperatureLimits[coolingTypeIndex];

    return (temperatureInC < lowerLimit) ? TOO_LOW :
         (temperatureInC > upperLimit) ? TOO_HIGH :
                               NORMAL;
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  if(alertTarget == TO_CONTROLLER){
    sendToController(breachType);
  }
  else{
    sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  sendValuesToController(header, breachType);
}

void sendValuesToController(unsigned short header, BreachType breachType) {
  printf("%x\n", header);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  const char* message;
  if(breachType == TOO_LOW){
    message = "Hi, the temperature is too low";
  }
  else if(breachType == TOO_HIGH){
    message = "Hi, the temperature is too high";
  }
  else{
    return;
  }
  printf("To: %s\n%s\n", recepient, message);
}
