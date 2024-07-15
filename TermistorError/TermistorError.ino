#define SERIESRESISTOR 100000    
#define NOMINAL_RESISTANCE 100000  
#define NOMINAL_TEMPERATURE 25.0   
#define B_COEFFICIENT 3950   
#define THERMISTOR_PIN 15  

float readThermistor(int pin) {
  float totalResistance = 0;
  int samples = 10; // Número de muestras para promediar

  for (int i = 0; i < samples; i++) {
    int analogValue = analogRead(pin);
    float voltage = analogValue * (5.0 / 1023.0);
    float resistance = (SERIESRESISTOR * (5.0 - voltage)) / voltage;
    totalResistance += resistance;
    delay(10); // Pequeña pausa entre lecturas
  }

  float averageResistance = totalResistance / samples;

  float steinhart = averageResistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= B_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  return steinhart;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Lectura del termistor:");
}

void loop() {
  float temperature = readThermistor(THERMISTOR_PIN);
  Serial.print("Termistor en pin ");
  Serial.print(THERMISTOR_PIN);
  Serial.print(": ");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(2000);
}
