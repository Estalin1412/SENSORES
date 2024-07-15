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

//Encabezado de Funciones
#include "EncabezadoDeFuncionesOBC.h"
//Funciones
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
  FunIniciarBME280(Sensor01Bme280);
  FunIniciarINA219(SensorCorriente_Ina219);
  FunIniciarMAX31865(SensorMAX31865);
} 

void loop() {
  String Data = "";
  //FunComunicacionTeensyTeensy(Serial8);
  // put your main code here, to run repeatedly:
  Data += FunObtenerStringDatosBME280(Sensor01Bme280)+ FunObtenerStringDatosINA219(SensorCorriente_Ina219)+FunObtenerStringDatosMAX31865(SensorMAX31865) + FunActivarGPS6mv2();
  
  Serial.println(Data);
  delay(1000);
}
/*
String FunObtenerStringDatosINA219( Adafruit_INA219 &  ina219){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  String datos = "Bus Voltage: " + String(busvoltage) + " V\n";
  datos += "Shunt Voltage: " + String(shuntvoltage) + " mV\n";
  datos += "Load Voltage: " + String(loadvoltage) + " V\n";
  datos += "Current: " + String(current_mA) + " mA\n";
  datos += "Power: " + String(power_mW) + " mW\n";
  return datos;
}

String FunObtenerStringDatosBME280(Adafruit_BME280 & bme)
{
  bme.takeForcedMeasurement();

  String datos ="Temperature = " + String( bme.readTemperature() )+" *C\n";
  datos += "Pressure = "+String( bme.readPressure()/ 100.0F ) + " hPa\n";
  datos += "Approx. Altitude = "+ String( bme.readAltitude( SEALEVELPRESSURE_HPA) )+" m\n";
  datos += "Humidity = "+ String( bme.readHumidity() ) +" %\n";
  return datos;
}

String FunObtenerStringDatosMAX3185(Adafruit_MAX31865 & thermo){

  float temp = thermo.temperature(RNOMINAL, RREF);
  String datos ="temp: ";
  datos +=  String(temp)+ "\n";
  return datos;
}
*/
/////////////////////////////////////////////////////////////////////////////////

static void printFloat(float val, bool valid, int len, int prec, String &cadena) {
  if (!valid) {
    while (len-- > 1) {
      cadena += "*";
    }
    cadena += " ";
  } else {
    cadena += String(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . y -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i) {
      cadena += " " ;
    }
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len,String & cadena) {
  char sz[32] = "*****************";
  if (valid) {
    sprintf(sz, "%ld", val);
  }
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i) {
    sz[i] = ' ';
  }
  if (len > 0) {
    sz[len - 1] = ' ';
  }
  cadena += sz;
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, String & cadena) {
  if (!d.isValid()) {
    cadena += "********** ";
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    cadena += sz;
  }

  if (!t.isValid()) {
    cadena += "******** ";
  } else {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    cadena += sz;
  }

  printInt(d.age(), d.isValid(), 5, cadena);
  smartDelay(0);
}

static void printStr(const char *str, int len, String & cadena) {
  int slen = strlen(str);
  for (int i = 0; i < len; ++i) {
    cadena += (i < slen ? str[i] : ' ');
  }
  smartDelay(0);
}
String FunActivarGPS6mv2()
{
  String cadena = "";
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5, cadena);
  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1, cadena);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6, cadena);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6, cadena);
  printInt(gps.location.age(), gps.location.isValid(), 5, cadena);
  printDateTime(gps.date, gps.time, cadena);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2,  cadena);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2, cadena);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2, cadena);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6, cadena);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9, cadena);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2, cadena);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6, cadena);

  printInt(gps.charsProcessed(), true, 6, cadena);
  printInt(gps.sentencesWithFix(), true, 10, cadena);
  printInt(gps.failedChecksum(), true, 9, cadena);
  cadena += "\n";

  smartDelay(1000);

  if ( millis() > 5000 && gps.charsProcessed() < 10 ) Serial.println(F("No GPS data received: check wiring"));
  return cadena;
}