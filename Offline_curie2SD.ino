#include <SD.h>
File myFile;

#include <Wire.h>
#include "RTClib.h"

#include "CurieIMU.h"

int ax, ay, az;         // accelerometer values
int gx, gy, gz;         // gyrometer values

const int ledPin = 13;      // activity LED pin
boolean blinkState = false; // state of the LED

int calibrateOffsets = 1; // int to determine whether calibration takes place or not

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  //Serial.begin(9600); // initialize Serial communication
  //while (!Serial);    // wait for the serial port to open

  // initialize device
  //Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // verify connection
  //Serial.println("Testing device connections...");
  //TODO: Add status log
  if (CurieIMU.begin()) {
    //Serial.println("CurieIMU connection successful");
  } else {
    //Serial.println("CurieIMU connection failed");
  }

  // use the code below to calibrate accel/gyro offset values
  if (calibrateOffsets == 1) {
    /**
    Serial.println("Internal sensor offsets BEFORE calibration...");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
    Serial.print("\t"); // -76
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
    Serial.print("\t"); // -235
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
    Serial.print("\t"); // 168
    Serial.print(CurieIMU.getGyroOffset(X_AXIS));
    Serial.print("\t"); // 0
    Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
    Serial.print("\t"); // 0
    Serial.println(CurieIMU.getGyroOffset(Z_AXIS));
    **/
    // To manually configure offset compensation values,
    // use the following methods instead of the autoCalibrate...() methods below
    //CurieIMU.setAccelerometerOffset(X_AXIS,495.3);
    //CurieIMU.setAccelerometerOffset(Y_AXIS,-15.6);
    //CurieIMU.setAccelerometerOffset(Z_AXIS,491.4);
    //CurieIMU.setGyroOffset(X_AXIS,7.869);
    //CurieIMU.setGyroOffset(Y_AXIS,-0.061);
    //CurieIMU.setGyroOffset(Z_AXIS,15.494);

    //Serial.println("About to calibrate. Make sure your board is stable and upright");
    //delay(5000);

    // The board must be resting in a horizontal position for
    // the following calibration procedure to work correctly!
    //Serial.print("Starting Gyroscope calibration and enabling offset compensation...");
    CurieIMU.autoCalibrateGyroOffset();
    //Serial.println(" Done");

    //Serial.print("Starting Acceleration calibration and enabling offset compensation...");
    CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
    CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
    CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
    //Serial.println(" Done");

   /** 
    Serial.println("Internal sensor offsets AFTER calibration...");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
    Serial.print("\t"); // -76
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
    Serial.print("\t"); // -2359
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
    Serial.print("\t"); // 1688
    Serial.print(CurieIMU.getGyroOffset(X_AXIS));
    Serial.print("\t"); // 0
    Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
    Serial.print("\t"); // 0
    Serial.println(CurieIMU.getGyroOffset(Z_AXIS));
    **/
  }
  
  // configure Arduino LED for activity indicator
  pinMode(ledPin, OUTPUT);

  //Specify the pin for SD card
  pinMode(10, OUTPUT);

  
  if (!SD.begin(10)) {
   // Serial.println("initialization failed!");
    return;
  }

  
  //Set the default time for clock
  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
  }
   else{
    Serial.println("RTC is on");
       // following line sets the RTC to the date & time this sketch was compiled
      // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
   }

  
}

void loop() {

  
  // Read raw accel/gyro measurements from device
  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  // display tab-separated accel/gyro x/y/z values
  /** 
  Serial.print("a/g:\t");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.print(az);
  Serial.print("\t");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.println(gz);
  **/
  
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(ledPin, blinkState);
   //digitalWrite(ledPin, true);

   //Get time and display time
    DateTime time = rtc.now();
    
    Serial.print(time.year(), DEC);
    Serial.print('/');
    Serial.print(time.month(), DEC);
    Serial.print('/');
    Serial.print(time.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[time.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(time.hour(), DEC);
    Serial.print(':');
    Serial.print(time.minute(), DEC);
    Serial.print(':');
    Serial.print(time.second(), DEC);
    Serial.println();
    
 //Write data
 // nothing happens after setup
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("170212.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    //Serial.print("Writing to test.txt...");
    String accel_result=String(ax)+","+String(ay)+","+String(az)+","+String(gx)+","+String(gy)+","+String(gz);
    String curt_time= String(print2digits(time.hour()))+ ","+ String(print2digits(time.minute()))+ ","+ String(print2digits(time.second()))+","
                    +","+ String(time.day())+","+ String(time.month())+","+ String(time.year());
    String result=curt_time+","+accel_result;
          
    myFile.println(result);
   // myFile.println(ax+","+ay+","+az+","+gx+","+gy+","+gz);
   
  // close the file:
    myFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    //Serial.println("error opening test.txt");
  }
  
}



int print2digits(int number)
{
    int result=0;

    if (number >= 0 && number < 10) {      
    }
    else{
      result=number;
      }    
    return result;
}
