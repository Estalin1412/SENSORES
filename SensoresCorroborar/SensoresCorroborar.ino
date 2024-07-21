#include "LibreriasOBC.h"
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
  /*
  FunIniciarACS712(SensorACS712);
  //Funciones activar
  FunIniciarBME280(Sensor01Bme280);
  FunIniciarINA219(SensorCorriente_Ina219);
  FunIniciarMAX31865(SensorMAX31865);
  */
} 

void loop() {
  //Para reiniciar la cadena                                                                                                                                                                                                        
  String Data = "";
  static uint8_t DatosBytesCommand[2] = {0, 0};
  static size_t bytesRead = 0;
  DatosCadenaComandos = "";
  //Para comuniaccion
  unsigned long start = millis();

  while (millis() - start < 250) {
    // Lectura de comandos desde la plataforma
    if (Serial1.available() > 0 && bytesRead <2) {
      DatosBytesCommand[bytesRead] = Serial1.read();
      bytesRead++;
      if (bytesRead == 2) {
        FunEjecutarComandos(DatosBytesCommand);
        bytesRead = 0; // Resetear el contador de bytes leídos
      }
    }

    // Lectura de datos desde el GPS
    if (Serial7.available() > 0) {
      gps.encode(Serial7.read());
    }
  }
  if (Serial8.available() > 0) {
    DatosCadenaComandos += String(DatosBytesCommand[0]) + String(DatosBytesCommand[1]);
    //Se envia Cadena de comandos a teensy slave
    Serial8.println(DatosCadenaComandos);
    //Se ontiene datos de teensy slave
    DatosCadenaTeensySlave = Serial8.readStringUntil('\n');
  }  

  //Ejecuta Lo Leido En La Cadena
  //Se acumula la cadena de datos segun especidficaciones Nasa
  Data += FunObtenerStringDatosMAX31865(SensorMAX31865);
  Data += FunObtenerStringDatosINA219(SensorCorriente_Ina219);
  Data += FunObtenerStringDatosBME280(Sensor01Bme280);
  Data += FunObtenerStringDatosACS712(SensorACS712);
  //Datos de BNO055
  Data += DatosCadenaTeensySlave;
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

  /*Otra forma de optener data
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


