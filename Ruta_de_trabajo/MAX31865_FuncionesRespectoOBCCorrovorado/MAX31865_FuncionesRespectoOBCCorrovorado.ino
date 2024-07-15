#include <Adafruit_MAX31865.h>

// Define pins for software SPI: CS, DI, DO, CLK
#define CS_PIN 10
#define DI_PIN 11
#define DO_PIN 12
#define CLK_PIN 13

// Create an instance of the Adafruit_MAX31865 class
Adafruit_MAX31865 termometro = Adafruit_MAX31865(CS_PIN, DI_PIN, DO_PIN, CLK_PIN);

// Constants for the sensor
#define RREF 430.0 // Reference resistor value for PT100
#define RNOMINAL 100.0 // Nominal resistance at 0 degrees Celsius for PT100

void FunInicirMAX31865(Adafruit_MAX31865 & thermo);
String FunObtenerStringDatos(Adafruit_MAX31865 & thermo);



void setup() {
// Start serial communication
Serial.begin(115200);
Serial.println("Adafruit MAX31865 PT100 Sensor Test!");
FunInicirMAX31865(termometro);
}

void loop() {

String data = FunObtenerStringDatos(termometro);
Serial.println(data);
delay(1000);
}
void FunInicirMAX31865(Adafruit_MAX31865 & thermo){
  //Initialize the MAX31865 and set the wire configuration
thermo.begin(MAX31865_3WIRE); // Use MAX31865_2WIRE or MAX31865_4WIRE 2 cables y 4 cables respectivamente
return ;
}

String FunObtenerStringDatos(Adafruit_MAX31865 & thermo){
  String datos;
  // Read the raw RTD value
uint16_t rtd = thermo.readRTD();

// Print the RTD value
datos += "RTD value: "+ String(rtd)+"\n";

// Calculate the ratio of the RTD value
float ratio = rtd / 32768.0;

// Print the ratio and resistance
datos += "Ratio = " + String(ratio, 8) + "Resistance = "+ String(RREF * ratio, 8)+ "\n";

// Calculate and print the temperature
float temperature = thermo.temperature(RNOMINAL, RREF);
datos += "Temperature = " + String(temperature) +"\n";

return datos;
}