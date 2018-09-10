/* IQS624 Hall Sensor, for Butterfly
 
 * 06/29/2017 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 *  Library may be used freely and without limit with attribution.
 *  
 */

#include <Arduino.h>
#include <Wire.h>
#include "IQS624.h"

// Butterfly
#define myLed 13  // green led
#define intPin 30 // data ready pin

uint8_t deltaDegrees;
uint16_t wheelDegrees = 0;
uint32_t thisTime = 0, lastTime = 0;

bool newIQS624Data = false;

IQS624 IQS624(intPin);

void setup() 
{
  Serial.begin(38400);
  delay(2000);
  Serial.println("Serial enabled!");
 
  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, HIGH);  // start with leds off, since active LOW

  Wire.begin(); // set master mode 
  Wire.setClock(400000); // I2C frequency at 400 kHz  
  delay(1000);

  IQS624.I2Cscan(); // should detect IQS624 at 0x44

  bool c = IQS624.checkChipID(); 
  delay(1000); 

  if(c)
  {
  // initialize device  
  IQS624.configure();
  }
  else
  {
  Serial.println("IQS624 not responding!");
  }

  attachInterrupt(intPin, myinthandler, FALLING); // enable IQS624 interrupt

}

void loop() 
{
  
    IQS624.checkEvents();

    IQS624.waitForIqsReady();
 if(newIQS624Data == true)
 {
    newIQS624Data = false;

    thisTime = millis();
  
    IQS624.checkHallStatus();

    uint16_t wheelDegrees = IQS624.readRotation(); 
    Serial.print("Wheel rotation = "); Serial.print(wheelDegrees); Serial.println(" degrees");

    uint8_t deltaDegrees = IQS624.readRelRotation();
    Serial.print("Delta rotation = "); Serial.print(deltaDegrees); Serial.println(" degrees");
    Serial.print("Rotation rate = "); Serial.print((float)(1000*deltaDegrees)/(float)(thisTime - lastTime), 2); Serial.println(" dps");
    lastTime = millis();

    digitalWrite(myLed, LOW); delay(100); digitalWrite(myLed, HIGH);
 }
  
}


/* Useful function */

void myinthandler()
{
  newIQS624Data = true;
}







