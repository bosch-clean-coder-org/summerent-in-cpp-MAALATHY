#include "typewise-alert.h"
#include <stdio.h>

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {

  private static final int temperatureLimits[2] = {
  35,   // PASSIVE_COOLING
  45,   // HI_ACTIVE_COOLING
  40    // DEFAULT_COOLING
};
  int coolingTypeIndex = coolingType.ordinal();
  int lowerLimit = 0;
  int upperLimit = temperatureLimits[coolingTypeIndex];

    return (value < lowerLimit) ? BreachType.TOO_LOW :
         (value > upperLimit) ? BreachType.TOO_HIGH :
                               BreachType.NORMAL;
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
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  const char* message;
  if(breachType == TOO_LOW){
    message = Hi, the temperature is too low;
  }
  else if(breachType == TOO_HIGH){
    message = Hi, the temperature is too high;
  }
  else{
    return;
  }
  printf("To: %s\n%s\n", recipient, message);
}
