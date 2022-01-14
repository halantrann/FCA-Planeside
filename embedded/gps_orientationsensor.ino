#include <Wire.h>
#include <Adafruit_Sensor.h> // http://librarymanager/All#Adafruit_Unified_Sensor
#include <Adafruit_BNO055.h> // http://librarymanager/All#Adafruit_BNO055
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void) 
{
  Serial.begin(9600);
  
  // initialize sensor
  if(!bno.begin()){
    
    // communicate if BNO055 is not identified
    Serial.print("BNO055 cannot be detected!");
    while(1);
    delay(1000);
    
  }
    
  bno.setExtCrystalUse(true);
  
}

void loop(void)
{
  
  // new sensor event 
  sensors_event_t event; 
  bno.getEvent(&event);

  // PITCH, HEADING, & ROLL VALUES
  Serial.print("Pitch: ");
  Serial.print(event.orientation.x);
  Serial.print(", Heading: ");
  Serial.print(event.orientation.y);
  Serial.print(", Roll: ");
  Serial.print(event.orientation.z);

  Serial.print("x_accel: ");
  Serial.print(event.acceleration.x);
  Serial.print(", y_accel: ");
  Serial.print(event.acceleration.y);
  Serial.print(", z_accel: ");
  Serial.print(event.acceleration.z);

  // TEMPERATURE
  int8_t temp = bno.getTemp();

  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");
  
  delay(100);
  
}
