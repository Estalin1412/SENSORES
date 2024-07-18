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
  VCC->5V
*/

/*Librerias para GPS6mv2
  TinyGPSPlusPlus by Ress
*/
#include <TinyGPSPlus.h>

/*Libreria para ACS712
ACS712 by Rob Tillaart
*/
#include "ACS712.h"
/*
SD by Arduino
*/
#include <SD.h>
#include <SPI.h>
//Encabezado de Funciones
#include "EncabezadoDeFunciones.h"
//Funciones
#include "Funciones.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
