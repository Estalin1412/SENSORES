#include <TinyGPSPlus.h>

// Define la instancia de TinyGPS++ y el puerto serial para GPS
TinyGPSPlus gps;  // Usando Serial1, revisa el pin correcto de RX para tu Teensy

void setup() {
  // Inicia el puerto serial para el depurador
  Serial.begin(115200);
  // Inicia el puerto serial para GPS
  Serial7.begin(9600);
}

void loop() {
  // Llama a smartDelay que maneja la recepción de datos de GPS
  smartDelay(1000);
  
  // Si tenemos una nueva sentencia NMEA válida de GPS  if (gps.location.isUpdated()) {
  printGPSData();

}

// Función para imprimir los datos del GPS
String printGPSData() {
  smartDelay(1000);
  String cadena = "";
  // Imprime la latitud, longitud, altitud, fecha y hora
  cadena += String(gps.location.lat(), 6) + ",";
  cadena += String(gps.location.lng(), 6) + ",";
  cadena += String(gps.altitude.meters(),0) + ",";
  cadena += String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year()) + ",";
  cadena += String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + ",";
  return cadena;
}

// Función para permitir la actualización de datos del GPS sin bloqueo
void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (Serial7.available()) {
      gps.encode(Serial7.read());
    }
  } while (millis() - start < ms);
}
