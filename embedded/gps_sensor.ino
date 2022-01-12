#include <Wire.h>
#include <SparkFun_Ublox_Arduino_Library.h> // http://librarymanager/All#SparkFun_Ublox_GPS
#include <SoftwareSerial.h> 

#define GPSTX A4 // output 
#define GPSRX A5 // input 
#define GPSBaud 9600 // baud rate for gps
#define Serial_Monitor_Baud 115200 // baud rate for serial monitor

SoftwareSerial GPSserial(GPSRX, GPSTX);  

// GPS object
SFE_UBLOX_GPS myGPS; 

void setup(){

  Serial.begin(115200);

  // waiting for Serial to connect
  while(!Serial) yield(); 

  Wire.begin();

  // in the case that GPS fails to initialize
  if (myGPS.begin() == false) {
    Serial.println("No GPS detected.");
    while(1)
    delay(1000);      
  }

  myGPS.setI2COutput(COM_TYPE_UBX); 
  myGPS.saveConfiguration(); 

  Serial.begin(Serial_Monitor_Baud);
  GPSserial.begin(GPSBaud); 

}

void loop() {

    if (myGPS.begin() == true) {

      /*long latitude = myGPS.getLatitude();
      latitude = latitude / 10000000;
      Serial.println("Latitude: ");
      Serial.print(latitude);

      long longitude = myGPS.getLongitude();
      longitude = longitude / 10000000;
      Serial.println("Longitude: ");
      Serial.print(longitude);*/

      long latDeg = myGPS.getLatitude();
      latDeg = latDeg / 10000000;
      Serial.print("{ latDeg:"); Serial.print(latDeg); Serial.print(", ");

      long lonDeg = myGPS.getLongitude();
      lonDeg = lonDeg / 10000000;  
      Serial.print("lonDeg: "); Serial.print(lonDeg); Serial.print(" }");

      long altitude = myGPS.getAltitude();
      Serial.println("Altitude: ");
      Serial.print(altitude);

      long speed = myGPS.getGroundSpeed();
      Serial.println("Speed (mm/s): ");
      Serial.print(speed);

      long time = myGPS.getTimeValid();
      Serial.println("Time: ");
      Serial.print(time);   

      while (GPSserial.available() > 0)
      Serial.write(GPSserial.read());

    }
}
