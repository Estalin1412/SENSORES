#include "LibreriasOBC.h"
String DatosIna219, DatosMax31865, DatosGps, DatosTermistores, DatosACS712, DatosBme280, DatosCadenaTeensySlave, DatosCadenaComandos;
/*................................................................VOID_SETUP.......................................................*/
void setup(){ 
  // put your setup code here, to run once:
  Serial.begin(4800);
  //Para comunicación entre teensy-plataforma pin 0 y 1
  Serial1.begin(4800);
  //Para comunicación (Este maestro)teensy-teensy 34 y 35
  Serial8.begin(4800);
  
  //ParaGPS
  Serial7.begin(9600);
  
  //Para BME280
  Wire2.begin();
  //Para HeatingPad 1
  pinMode(2, OUTPUT);
  analogWriteResolution(12);
  /*
  //Para ACS712
  FunIniciarACS712(SensorACS712);
  //Funciones
  FunIniciarBME280(Sensor01Bme280);
  FunIniciarINA219(SensorCorriente_Ina219);
  FunIniciarMAX31865(SensorMAX31865);
  */
} 

void loop() {
  String Data = "";
  DatosCadenaComandos = "";
  /*
  DatosCadenaComandos +=  FunObtenerStringDatosComunicacionTeensyTeensy(Serial1);
  FunProcesarComandos(DatosCadenaComandos);
  Serial8.print(DatosCadenaComandos);
  
  //FunComunicacionTeensyTeensy(Serial8);
  //Cadena de datos segun especidficaciones Nasa
  Data += FunObtenerStringDatosMAX31865(SensorMAX31865);
  Data += FunObtenerStringDatosINA219(SensorCorriente_Ina219);
  Data += FunObtenerStringDatosBME280(Sensor01Bme280);
  Data += FunObtenerStringDatosACS712(SensorACS712);
  //Datos de BNO055
  Data += FunObtenerStringDatosComunicacionTeensyTeensy(Serial8);
  //DatosTermistor
  Data += FunObtenerStringDatosGPS6mv2();
  Data += FunObtenerStringDatosTermistor(PinesTermistor);
  Data += ";";
  Serial1.print(Data);
  FuncionEscribirEnSDcard(ArchivoSDcard, Data);
  FunControlHeatingPad(Termistores[3], Termistores[4], 2);
  */



  /*
  DatosMax31865 = FunObtenerStringDatosMAX31865(SensorMAX31865);
  DatosIna219 = FunObtenerStringDatosINA219(SensorCorriente_Ina219);
  DatosBme280 = FunObtenerStringDatosBME280(Sensor01Bme280)+ "\n";
  DatosGps = FunObtenerStringDatosGPS6mv2() + "\n";
  DatosACS712 = FunObtenerStringDatosACS712(SensorACS712);
  DatosTermistores = FunObtenerStringDatosTermistor(PinesTermistor);
  DatosCadenaTeensySlave = FunObtenerStringDatosComunicacionTeensyTeensy(Serial8);
  */
  Data += FunObtenerStringDatosGPS6mv2();
  Serial.println(Data);
  delay(2000);
}


