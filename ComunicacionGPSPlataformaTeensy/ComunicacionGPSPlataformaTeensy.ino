#include "LibreriasOBC.h"

String DatosIna219, DatosMax31865, DatosGps, DatosTermistores, DatosACS712, DatosBme280, DatosCadenaTeensySlave, DatosCadenaComandos;

void setup() { 
  Serial.begin(4800);
  Serial1.begin(4800);  // Comunicación con la plataforma
  Serial8.begin(4800);  // Comunicación entre Teensy
  Serial7.begin(9600);  // Comunicación con GPS
  
  Wire2.begin();  // Comunicación I2C para BME280
  
  // Configuración de pin para HeatingPad y resolución PWM
  pinMode(2, OUTPUT);
  analogWriteResolution(12);
  
  // Encender HeatingPad al máximo (3.3V)
  FunPWMParaHeatingPad(3.3);
  
}

void loop() {
  DatosCadenaComandos = "cas", DatosCadenaTeensySlave = "";
  unsigned long start = millis();

  while (millis() - start < 250) {
    // Lectura de comandos desde la plataforma
    if (Serial1.available() > 0 && DatosCadenaComandos.length() <5) {
      char cad = Serial1.read();
      DatosCadenaComandos += cad;  // Envío de comandos a la otra Teensy
    }

    // Lectura de datos desde el GPS
    if (Serial7.available() > 0) {
      gps.encode(Serial7.read());
    }
  }
    if (Serial8.available() > 0) {
      Serial8.println(DatosCadenaComandos);
      DatosCadenaTeensySlave = Serial8.readStringUntil('\n');
    }
  // Lectura de datos de sensores
  String Data = "";
  Data += DatosCadenaTeensySlave;
  
  Data += FunDatosGPS6mv2();
 
  Data += ";";
  
  FunEjecutarComandos(DatosCadenaComandos);  
  Serial.println(Data);
}


String FunDatosGPS6mv2() {
  String cadena = "";
  // Imprime la latitud, longitud, altitud, fecha y hora
  cadena += String(gps.location.lat(), 4) + ",";
  cadena += String(gps.location.lng(), 4) + ",";
  cadena += String(gps.altitude.meters()) + ",";
  cadena += String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + "24,";
  cadena += String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + ",";
  return cadena;
}
