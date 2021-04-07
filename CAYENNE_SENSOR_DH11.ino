
/* POR GUSTAVO JARRO CALLIZAYA*/

/* PRACTICA: LECTURA DE DATOS DE UN SENSOR DH11 A TRAVEZ SE CAYENNE*/

/* SE USA EL SENSOR DH11 DE TEMPERATURA Y HUMEDAD PARA LEER LOS DATOS ATMOSFERICOS Y MOSTRARLOS EN LA INTERFAZ DE LA PAGINA WEB DE CAYENNE
MEDIANTE WIDGETS UNO PARA CADA UNO*/
//#define CAYENNE_PRINT Serial   // Comment this out to disable prints and save space
#include <CayenneTemperature.h>
#include <CayenneMQTTEthernet.h>   // Change this to use a different communication device. See Communications examples.

#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE DHT11
#define INTERVALO 2000

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "c81e3360-9c84-11ea-a67f-15e30d90bbf4";
char password[] = "5ea1f9a036461d25e55ad4139aa32782a1364d3c";
char clientID[] = "388f6ec0-214b-11eb-8779-7d56e82df461";

#define SENSOR_PIN 0
#define VIRTUAL_CHANNEL 0

// Thermistor thermistor(SENSOR_PIN, resistance);

DHT_Unified dht(DHTPIN, DHTTYPE);
sensors_event_t event;

void setup()
{
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID);
  dht.begin();
  sensor_t sensor;
}

void loop()
{
  Cayenne.loop();


}

// This function is called at intervals to send sensor data to Cayenne.
CAYENNE_OUT(VIRTUAL_CHANNEL)
{

  dht.temperature().getEvent(&event);

  // This command writes the temperature in Celsius to the Virtual Channel.
  Cayenne.celsiusWrite(VIRTUAL_CHANNEL, event.temperature);


  // To send the temperature in Fahrenheit or Kelvin use the corresponding code below.
  //Cayenne.fahrenheitWrite(VIRTUAL_CHANNEL, thermistor.getFahrenheit());
  //Cayenne.kelvinWrite(VIRTUAL_CHANNEL, thermistor.getKelvin());
}

CAYENNE_OUT(1)
{

  dht.humidity().getEvent(&event);
  // This command writes the temperature in Celsius to the Virtual Channel.


  Cayenne.virtualWrite(1, event.relative_humidity, "analog_sensor", "null");

  // To send the temperature in Fahrenheit or Kelvin use the corresponding code below.
  //Cayenne.fahrenheitWrite(VIRTUAL_CHANNEL, thermistor.getFahrenheit());
  //Cayenne.kelvinWrite(VIRTUAL_CHANNEL, thermistor.getKelvin());
}
