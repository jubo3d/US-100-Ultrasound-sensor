// Distance and temperature sensing using US-100 sensor in serial mode.
// Derived from https://arduibots.wordpress.com/2014/10/12/us-100-ultrasonic-sensor-in-serial-mode/
// jubo, May 2018
 
#include <SoftwareSerial.h>;
 
const int US100_TX = 2;
const int US100_RX = 3;
 
// Start Software Serial
SoftwareSerial sensorUS100(US100_RX, US100_TX);
 
unsigned int MSByteDist = 0;
unsigned int LSByteDist = 0;
unsigned int mmDist = 0;
int temp = 0;
 
void setup() {
    Serial.begin(9600);
    sensorUS100.begin(9600);
    Serial.println("Start distance sensor");
    Serial.println("---------------------------------------------------------");
}
 
void loop() {
    sensorUS100.flush(); // Clean the serial port buffer
    sensorUS100.write(0x55); // Request distance info
 
    delay(500);
 
    if(sensorUS100.available() >= 2) // Check reception of 2 bytes
    {
        MSByteDist = sensorUS100.read(); // 
        LSByteDist  = sensorUS100.read();
        mmDist  = MSByteDist * 256 + LSByteDist; // Distance
        if((mmDist > 1) && (mmDist < 10000)) // Check if the distance is in expected range
        {
            Serial.print("Distance: ");
            Serial.print(mmDist, DEC);
            Serial.print(" mm    ");
        }
    }
 
    sensorUS100.flush(); // Clean the serial port buffer
    sensorUS100.write(0x50); // Request temperature info
 
    delay(500);
    if(sensorUS100.available() >= 1) // Check reception of 1 byte
    {
        temp = sensorUS100.read(); // Temperature
        if((temp > 1) && (temp < 130)) // Check if the distance is in expected range
        {
            temp -= 45; // Correction offset of 45º
            Serial.print("Temperature: ");
            Serial.print(temp, DEC);
            Serial.print(" ºC.");
        }
    }
    Serial.println("");
    delay(500);
}
