/*
Cayenne Photoresistor Example

This sketch shows how to send Photoresistor Sensor data to the Cayenne Dashboard.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Attach a photoresistor to an analog pin on your Arduino.
   Make sure to use an analog pin, not a digital pin.
   Schematic:
   [Ground] -- [10k-resistor] -- | -- [Photoresistor] -- [5V]
                                 |
                            Analog Pin
2. Set the SENSOR_PIN value below to the pin number you used when connecting the sensor.
3. Set the VIRTUAL_CHANNEL value below to a free virtual channel (or the virtual channel of a Photoresistor Sensor widget you have added) in the Dashboard.
4. Set the Cayenne authentication info to match the authentication info from the Dashboard.
5. Compile and upload this sketch.
6. Once the Arduino connects to the Dashboard it should automatically create a temporary display widget (or update the Photoresistor Sensor widget you have added) with data.
   To make a temporary widget permanent click the plus sign on the widget.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTEthernet.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "c81e3360-9c84-11ea-a67f-15e30d90bbf4";
char password[] = "5ea1f9a036461d25e55ad4139aa32782a1364d3c";
char clientID[] = "1a691c60-c5da-11ea-93bf-d33a96695544";

#define SENSOR_PIN 7
#define VIRTUAL_CHANNEL 0

void setup()
{
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID);
}

void loop()
{
  Cayenne.loop();
}

// This function is called at intervals to send sensor data to Cayenne.
CAYENNE_OUT(VIRTUAL_CHANNEL)
{
  Cayenne.virtualWrite(VIRTUAL_CHANNEL, analogRead(SENSOR_PIN), "analog_sensor", "null");
}
