#include "LibreriasOBC.h"

int PinesTermistor[] = {15 , 16, 17, 18, 19, 20};

float Termistores[6] = {0};
/*................................................................VOID_SETUP.......................................................*/
void setup(){ 
  // put your setup code here, to run once:
  Serial.begin(4800);
  
  //Para comunicación entre teensy-plataforma pin 0 y 1
  Serial1.begin(4800);
  Serial.println("Init Serial...");
  
  //Para comunicación (Este maestro)teensy-teensy 34 y 35
  Serial8.begin(4800);
  
  //ParaGPS
  Serial7.begin(4800);
  
  //Para BME280
  Wire2.begin();
  //Para HeatingPad
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
  /*
  //FunComunicacionTeensyTeensy(Serial8);
  // put your main code here, to run repeatedly:
  Data += FunObtenerStringDatosMAX31865(SensorMAX31865) + "\n" + 
  FunObtenerStringDatosINA219(SensorCorriente_Ina219)+ "\n" +
  FunObtenerStringDatosBME280(Sensor01Bme280)+ "\n" +
  FunObtenerStringDatosGPS6mv2() + "\n";
  Data += FunObtenerStringDatosACS712(SensorACS712);
  Data += FunObtnerStirngDatoTermistor(15) + FunObtnerStirngDatoTermistor(16) + FunObtnerStirngDatoTermistor(17) + FunObtnerStirngDatoTermistor(18) + FunObtnerStirngDatoTermistor(19) + FunObtnerStirngDatoTermistor(20);
  Serial1.print(Data);
  FuncionEscribirEnSDcard(Archivo, Data);
  FuncionLeerEnSDcard(Archivo);
  */
  Data += FunObtenerStringDatosGPS6mv2();
  funPWMParaHeatinPad(3.3);
  Data +=  FunObtnerStirngDatoTermistor(PinesTermistor);
  Serial.println(Data);
}
