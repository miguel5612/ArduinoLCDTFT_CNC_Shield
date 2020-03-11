#define X_STEP_BIT         2  // Uno Digital Pin 2
#define Y_STEP_BIT         3  // Uno Digital Pin 3
#define Z_STEP_BIT         4  // Uno Digital Pin 4
#define A_STEP_BIT         12  // Uno Digital Pin 4

#define X_DIRECTION_BIT    5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT    6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT    7  // Uno Digital Pin 7
#define A_DIRECTION_BIT    13  // Uno Digital Pin 7

//Conexiones en CNC Shield:
/*
 *  Spindle enable -> StepA
 *  Spingle dir -> DirA
 *  
 *  Endstops 
 *  X, Y, Z, Hold (A)
 *  Conexiones seriales -> TX RX (Pantalla) GND - GND - Vin Vin..
 */


#define limitX 9
#define limitY 10
#define limitZ 11
#define limitA A1

#define STEPPER_ENABLE     8  // Uno Digital Pin 8
#define time_delay 500

#define stepsPerRevolution 400  // change this to fit the number of steps per revolution

#include "A4988.h"

#define RPM 100

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, stepsPerRevolution is hardwired on the driver
A4988 stepperX(stepsPerRevolution, X_DIRECTION_BIT, X_STEP_BIT);
A4988 stepperY(stepsPerRevolution, Y_DIRECTION_BIT, Y_STEP_BIT);
A4988 stepperZ(stepsPerRevolution, Z_DIRECTION_BIT, Z_STEP_BIT);
A4988 stepperA(stepsPerRevolution, A_DIRECTION_BIT, A_STEP_BIT);


String readedString =  "";

void setup() {
    Serial.begin(9600);
    pinMode(STEPPER_ENABLE, OUTPUT);
    
    pinMode(limitX, INPUT_PULLUP);
    pinMode(limitY, INPUT_PULLUP);
    pinMode(limitZ, INPUT_PULLUP);
    pinMode(limitA, INPUT_PULLUP);
    
    stepperX.begin(RPM, MICROSTEPS);
    stepperY.begin(RPM, MICROSTEPS);
    stepperZ.begin(RPM, MICROSTEPS);
    stepperA.begin(RPM, MICROSTEPS);
    
    Serial.println("Init OK");
    
    digitalWrite(STEPPER_ENABLE, false);
}

void loop() {
    //Serial.print("Limit X: "); Serial.println(digitalRead(limitX));
    //Serial.print("Limit Y: "); Serial.println(digitalRead(limitY));
    //Serial.print("Limit Z: "); Serial.println(digitalRead(limitZ));
    //Serial.print("Limit A: "); Serial.println(digitalRead(limitA));
    readedString =  ""; int len = 0;
    while (Serial.available() || len <= 14) {
      delay(3);  //delay to allow buffer to fill
      if (Serial.available() >0) {
        char c = Serial.read();  //gets one byte from serial buffer
        readedString += c; //makes the string readString
        len ++;
        if(c == "0") break;
      }
    }
    if(readedString!="")
    {
      Serial.println(readedString);
      String eje = readedString.substring(8, 9);
      String dir = readedString.substring(9,10);
      if(readedString.indexOf("X") > 0) eje = "X";
      if(readedString.indexOf("Y") > 0) eje = "Y";
      if(readedString.indexOf("Z") > 0) eje = "Z";
      if(readedString.indexOf("A") > 0) eje = "A";

      if(readedString.indexOf("-") > 0) dir = "-";
      else dir = "+";
      
      
      Serial.println(readedString);
      Serial.print("Eje: ");
      Serial.println(eje); // optional: repeat back what I got for debugging
      Serial.print("Direccion: ");
      Serial.println(dir);
      readedString = "";
      if(eje == "X" & digitalRead(limitX))
      {
        Serial.println("Moviendo eje X");
        if(dir != "-") stepperX.rotate(360);
        else stepperX.rotate(-360);
        //stepperX.move(stepsPerRevolution*MICROSTEPS);
        delay(time_delay);
      }
      else if(eje == "Y" & digitalRead(limitY))
      {
        Serial.println("Moviendo eje Y");
        if(dir != "-") stepperY.rotate(360);
        else stepperY.rotate(-360);
        //stepperY.move(stepsPerRevolution*MICROSTEPS);
        delay(time_delay);
      }
      else if(eje == "Z" & digitalRead(limitZ))
      {
        Serial.println("Moviendo eje Z");
        if(dir != "-") stepperZ.rotate(360);
        else stepperZ.rotate(360);      
        delay(time_delay);
      }
      else if(eje == "A" & digitalRead(limitA))
      {
        Serial.println("Moviendo eje A");
        if(dir != "-") stepperA.rotate(180);
        else stepperA.rotate(-180);
        //stepperA.move(stepsPerRevolution*MICROSTEPS);
        delay(time_delay);
      }
    }
}



/*
    stepper.rotate(360);
    stepper.move(-stepsPerRevolution*MICROSTEPS);
*/
