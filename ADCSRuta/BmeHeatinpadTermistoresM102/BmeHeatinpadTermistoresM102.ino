/*Uso
BME280,BNO055;
*/
#include <Wire.h>
/*Libreria
Adafruit BME280 Library by Adafruit
*/
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
/*
  Adafruit BNO055 by Adafruit
*/
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
/*
SD by Arduino, SparkFun
*/
#include <SD.h>
#include "EncabezadoDeFunciones.h"
#include "Funciones.h"
/////////////////////////////////////////////VOID SETUP////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Para comunicación teensy teensy
  Serial1.begin(4800);
  //Para iniciar BME280
  FunIniciarBME280(SensorBme280);
  //Para heating pad
  pinMode(pinHeadtingPad, OUTPUT);
  analogWriteResolution(12);
  //Para encender hetingPad
  FunPWMParaHeatingPad(3.3, pinHeadtingPad);
  //Para Iniciar 
  FunIniciarM102();
}


void loop() {
  // put your main code here, to run repeatedly:
  data = "";
  dataComandos = "";
  //Recivir comandos de teemsy maestro
  if(Serial1.available() > 0)
    dataComandos += Serial1.readStringUntil('\0');
  FunEjecutarComandos(dataComandos);
  //Obtener datos
  data += FunObtenerStringDatosBME280(SensorBme280);
  data += FunObtenerStringDatosTermistor(pinesTermistores);
  data += FunObtenerStringDatosM102(pinAN1);
  data += FunObtenerStringDatosM102(pinAN2);
  data += FunObtenerStringDatosM102(pinAN3);
  data += FunObtenerStringDatosM102(pinAN4);
  data += FunObtenerStringDatosM102(pinAN5);
  Serial1.println(data);
}
/////////////////////////////////////////FUNCIONES////////////////////////////////////////////////////////////////
