/*---------------------------------------------------LIBRERIAS---------------------------------------------------------------------------*/
#include <Wire.h>
/*Libreria
Adafruit INA219 by adafruit
*/
#include <Adafruit_INA219.h>
/*Libreria
Adafruit BME280 Library by Adafruit
*/
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
/*Libreria
Adafruit MAX3185 Library by Adfruit
*/
#include <Adafruit_MAX31865.h>
/*
  10->CS
  11->SDI
  12->SDO
  13->CLK
  3V3->3V3
*/
/*Librerias para GPS6mv2
  TinyGPSPlusPlus by Ress
*/
#include <TinyGPSPlus.h>
//Encabezado de Funciones
#include "EncabezadoDeFuncionesOBC.h"
#include "FuncionesOBC.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

  //Funciones
  FunIniciarBME280(Sensor01Bme280, Serial1);
  FunIniciarINA219(SensorCorriente_Ina219, Serial1);
  FunIniciarMAX3185(SensorMAX3185, Serial1);
} 

void loop() {
  FunComunicacionTeensyTeensy(Serial8);
  // put your main code here, to run repeatedly:
  FunObtenerDatosBME280(Sensor01Bme280, Serial1);
  FunObtenerDatosINA219(SensorCorriente_Ina219, Serial1);
  FunObtenerDatosMAX3185(SensorMAX3185, Serial1);
  FunActivarGPS6mv2(Serial1);
  
  delay(1000);
}


