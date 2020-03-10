#define X_STEP_BIT         2  // Uno Digital Pin 2
#define Y_STEP_BIT         3  // Uno Digital Pin 3
#define Z_STEP_BIT         4  // Uno Digital Pin 4
#define A_STEP_BIT         12  // Uno Digital Pin 4

#define X_DIRECTION_BIT    5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT    6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT    7  // Uno Digital Pin 7
#define A_DIRECTION_BIT    13  // Uno Digital Pin 7

#define STEPPER_ENABLE     8  // Uno Digital Pin 8

#define stepsPerRevolution 130  // change this to fit the number of steps per revolution

#include "BasicStepperDriver.h"

#define RPM 50

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, stepsPerRevolution is hardwired on the driver
BasicStepperDriver stepperX(stepsPerRevolution, X_DIRECTION_BIT, X_STEP_BIT);
BasicStepperDriver stepperY(stepsPerRevolution, Y_DIRECTION_BIT, Y_STEP_BIT);
BasicStepperDriver stepperZ(stepsPerRevolution, Z_DIRECTION_BIT, Z_STEP_BIT);
BasicStepperDriver stepperA(stepsPerRevolution, A_DIRECTION_BIT, A_STEP_BIT);


String readedString =  "";

void setup() {
    Serial.begin(9600);
    pinMode(STEPPER_ENABLE, OUTPUT);
    
    stepperX.begin(RPM, MICROSTEPS);
    stepperY.begin(RPM, MICROSTEPS);
    stepperZ.begin(RPM, MICROSTEPS);
    stepperA.begin(RPM, MICROSTEPS);
    
    Serial.println("Init OK");
    
    digitalWrite(STEPPER_ENABLE, false);
}

void loop() {
    readedString =  "";
    while (Serial.available()) {
      delay(3);  //delay to allow buffer to fill
      if (Serial.available() >0) {
        char c = Serial.read();  //gets one byte from serial buffer
        readedString += c; //makes the string readString
      }
    }
    if(readedString!="")
    {
      String eje = readedString.substring(8, 9);
      String dir = readedString.substring(9,10);
      Serial.print("Eje: ");
      Serial.println(eje); // optional: repeat back what I got for debugging
      Serial.print("Direccion: ");
      Serial.println(dir);
      readedString = "";
      if(eje == "X")
      {
        Serial.println("Moviendo eje X");
        if(dir != "-") stepperX.rotate(360);
        else stepperX.rotate(-360);
        stepperX.move(stepsPerRevolution*MICROSTEPS);
        delay(1000);
      }
      else if(eje == "Y")
      {
        Serial.println("Moviendo eje Y");
        if(dir != "-") stepperY.rotate(360);
        else stepperY.rotate(-360);
        stepperY.move(stepsPerRevolution*MICROSTEPS);
        delay(1000);
      }
      else if(eje == "Z")
      {
        Serial.println("Moviendo eje Z");
        if(dir != "-") 
        {
          stepperZ.rotate(360);
          stepperZ.move(stepsPerRevolution*MICROSTEPS);
        }
        else
        {
          stepperZ.rotate(360);
          stepperZ.move(-stepsPerRevolution*MICROSTEPS);
        }        
        delay(1000);
      }
      else if(eje == "A")
      {
        Serial.println("Moviendo eje A");
        if(dir != "-") stepperA.rotate(360);
        else stepperA.rotate(-360);
        stepperA.move(stepsPerRevolution*MICROSTEPS);
        delay(1000);
      }
    }
}



/*
    stepper.rotate(360);
    stepper.move(-stepsPerRevolution*MICROSTEPS);
*/
