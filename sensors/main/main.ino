#include <Wire.h>
#include <SPI.h>

#include "accelerometer.h"
#include "altimeter.h"
#include "gps.h"
#include "gyroscope.h"

//Function definitions
void read_all_sensors();
void print_all_sensors();

void setup() {
  Wire.begin(0x60);        // Join i2c bus
  Wire.begin(0x6A);        // Join i2c bus
  Wire.begin(0x6B);        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  //Create sensors
  const int num_sensors = 5;
  
  accelerometer* myAccelerometer = new accelerometer(0x60);
  altimeter* myAltimeter = new altimeter(0x6A);
  gps* myGps = new gps(0x6B);
  gyroscope* myGyroscope = new gyroscope(0x60);
  thermometer* myThermometer = new thermometer(0x6A);
  base_sensor* mySensors[num_sensors] = {myAccelerometer, myAltimeter, myGps, myGyroscope, myThermometer};
}

void loop() {
  read_all_sensors();
  print_all_sensors();
}

void read_all_sensors() {
  for(int i = 0; i < num_sensors; i++) {
    mySensors[i].read_sensor_value();
  }
}

void print_all_sensors() {
  //prints a single string containing all sensor values
  //to be decoded by python script

  //expect precision issues to # of digits
  //python script currently expects 2 digits per datum
  
  for (int i=0; i<num_sensors; i++){
    Serial.print(mySensors[i].values.val1.name);
    Serial.print(mySensors[i].values.val1.value);
    Serial.print(mySensors[i].values.val2.name);
    Serial.print(mySensors[i].values.val2.value);
    Serial.print(mySensors[i].values.val3.name);
    Serial.print(mySensors[i].values.val3.value);
  }//so far, Accelerometer, GPS and Gyroscope have this implementation

  Serial.print("Lat:");
  Serial.print(myGps.get_latitude());
  Serial.print("Lng:");
  Serial.print(myGps.get_longitude());
  
  Serial.print("Cur:");
  Serial.print(rand() % 90 + 10);
  Serial.print("Pwr:");
  Serial.print(rand() % 90 + 10);
  Serial.print("Vlt:");
  Serial.print(rand() % 90 + 10);
  
  Cartesian_Coordinates GyCoordinates = myGyroscope.get_sensor_coordinates();
  Serial.print("GyX:");
  Serial.print(GyCoordinates.x);
  Serial.print("GyY:");
  Serial.print(GyCoordinates.y);
  Serial.print("GyZ:");
  Serial.print(GyCoordinates.z);
  
  Serial.print("Alt:");
  Serial.print(myAltimeter.get_sensor_value());
  Serial.print("Tem:");
  Serial.print(myThermometer.get_sensor_value()); 
  
  Cartesian_Coordinates AcCoordinates = myAccelerometer.get_sensor_coordinates();
  Serial.print("AcX:");
  Serial.print(AcCoordinates.x);
  Serial.print("AcY:");
  Serial.print(AcCoordinates.y);
  Serial.print("AcZ:");
  Serial.print(AcCoordinates.z);

}
