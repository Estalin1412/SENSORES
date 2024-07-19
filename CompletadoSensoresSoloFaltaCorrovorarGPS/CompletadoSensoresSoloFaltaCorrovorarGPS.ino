#include "LibreriasOBC.h"
String DatosIna219, DatosMax31865, DatosGps, DatosTermistores, DatosACS712, DatosBme280, DatosCadenaTeensySlave, DatosCadenaComandos;
/*................................................................VOID_SETUP.......................................................*/
void setup(){ 
  //Para comunicación entre teensy-plataforma pin 0 y 1 "RS232"
  Serial1.begin(4800);
  //Para comunicación (Este maestro)teensy-teensy 34 y 35 "Comunicación Serial"
  Serial8.begin(4800);
  
  //ParaGPS
  Serial7.begin(9600);
  
  //Para BME280
  Wire2.begin();
  //Para HeatingPad 1
  pinMode(2, OUTPUT);
  analogWriteResolution(12);
  //Encender HeatingPAF
  FunPWMParaHeatingPad(3.3);
  //Para ACS712
  FunIniciarACS712(SensorACS712);
  //Funciones activar
  FunIniciarBME280(Sensor01Bme280);
  FunIniciarINA219(SensorCorriente_Ina219);
  FunIniciarMAX31865(SensorMAX31865);

} 

void loop() {
  //Para reiciar la cadena                                                                                                                                                                                                        
  String Data = "";
  DatosCadenaComandos = "";
  //Para comuniaccion
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

  //LeerCadena De Comandos
  DatosCadenaComandos +=  FunObtenerComandosTeensyPlataforma(DatosCadenaComandos);
  //Ejecuta Lo Leido En La Cadena
  FunEjecutarComandos(DatosCadenaComandos);
  //Se envia cadena de comandos al teensy slave
  Serial8.println(DatosCadenaComandos);
  //Se acumula la cadena de datos segun especidficaciones Nasa
  Data += FunObtenerStringDatosMAX31865(SensorMAX31865);
  Data += FunObtenerStringDatosINA219(SensorCorriente_Ina219);
  Data += FunObtenerStringDatosBME280(Sensor01Bme280);
  Data += FunObtenerStringDatosACS712(SensorACS712);
  //Datos de BNO055
  Data += Serial8.readStringUntil('\n');
  //DatosTermistor
  Data += FunObtenerStringDatosGPS6mv2();
  Data += FunObtenerStringDatosTermistor(PinesTermistor);
  Data += ";";
  //Se envia datos a la plataforma
  Serial1.print(Data);
  //Se guarda datos en SDcard
  FuncionEscribirEnSDcard(ArchivoSDcard, Data);
  //Control de HeatingPad1
  FunControlHeatingPad(Termistores[3], Termistores[4], 2);

  /*
  DatosMax31865 = FunObtenerStringDatosMAX31865(SensorMAX31865);
  DatosIna219 = FunObtenerStringDatosINA219(SensorCorriente_Ina219);
  DatosBme280 = FunObtenerStringDatosBME280(Sensor01Bme280)+ "\n";
  DatosCadenaTeensySlave = FunObtenerStringDatosComunicacionTeensyTeensy(Serial8);
  DatosGps = FunObtenerStringDatosGPS6mv2() + "\n";
  DatosACS712 = FunObtenerStringDatosACS712(SensorACS712);
  DatosTermistores = FunObtenerStringDatosTermistor(PinesTermistor);
  */

  //Para ver por comunicaionUSB en serial con pc
}


