/*
Cayenne Light Switch Example

This sketch shows how to set up a Light Switch with Cayenne.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Light Switch Widget.
2. Select a virtual channel number for the widget.
3. Set the VIRTUAL_CHANNEL value below to virtual channel you selected.
4. Attach the negative leg of an LED to ground and the other leg to the selected digital pin.
   Schematic:
   [Ground] -- [LED] -- [Resistor] -- [Digital Pin]
5. Set the ACTUATOR_PIN value below to the pin number you used when connecting your LED.
6. Set the Cayenne authentication info to match the authentication info from the Dashboard.
7. Compile and upload this sketch.
8. Once the Arduino connects to the Dashboard you can use the widget button to turn the LED on and off.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTEthernet.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "c81e3360-9c84-11ea-a67f-15e30d90bbf4";
char password[] = "5ea1f9a036461d25e55ad4139aa32782a1364d3c";
char clientID[] = "1a691c60-c5da-11ea-93bf-d33a96695544";

#define VIRTUAL_CHANNEL 0
#define ACTUATOR_PIN 2 // Do not use digital pins 0 or 1 since those conflict with the use of Serial.

void setup()
{
  Serial.begin(9600);
  pinMode(ACTUATOR_PIN, OUTPUT);
  Cayenne.begin(username, password, clientID);
}

void loop()
{
  Cayenne.loop();
}

// This function is called when data is sent from Cayenne.
CAYENNE_IN(VIRTUAL_CHANNEL)
{
  int value = getValue.asInt();
  CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNEL, ACTUATOR_PIN, value);
  // Write the value received to the digital pin.
  digitalWrite(ACTUATOR_PIN, value);
}

// This function is called at intervals to send data to Cayenne and keep the device online.
// Will create a temporary green widget on Channel 0, make it permanent by clicking on '+'. 
CAYENNE_OUT(0)
{
  CAYENNE_LOG("Send data for Virtual Channel 0");
  // This command writes the device's uptime in seconds to the Virtual Channel. 
  Cayenne.virtualWrite(0, millis() / 1000);
}
