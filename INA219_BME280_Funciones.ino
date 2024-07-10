#include <Wire.h>
/*Libreria
Adafruit INA219 by adafruit
*/
#include <Adafruit_INA219.h>
/*
  BME280 by Tyler Glenn
*/
#include <BME280.h>
#include <BME280I2C.h>


/*Definimos objetos*/
Adafruit_INA219 SensorCorriente_Ina219;
BME280I2C SensorTemperatura_BME280;

void FunIniciarINA219(Adafruit_INA219 & ina219);
void FunObtenerDatosINA219( Adafruit_INA219 &  ina219);
void FunIniciarBME280(BME280I2C & bme);
void FunObtenerDatosBME280(BME280I2C & bme);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  Serial.println("Init Serial...");
  while(!Serial) delay(10);

  FunIniciarBME280(SensorTemperatura_BME280);
  FunIniciarINA219(SensorCorriente_Ina219);
} 

void loop() {
  // put your main code here, to run repeatedly:
  FunObtenerDatosBME280(SensorTemperatura_BME280);
  FunObtenerDatosINA219(SensorCorriente_Ina219);
  delay(2000);
}

/*----------------------------------FuncionesParaIna219--------------------------------------------------------------------*/
void FunIniciarINA219(Adafruit_INA219 & ina219){
  Wire2.begin();
  // Wire2.setSCL(24);
  // Wire2.setSDA(25);

  while(!ina219.begin(&Wire2))  delay(10);
  
  Serial.println("INA219 conect succefull!!");

  ina219.setCalibration_32V_2A();

}

void FunObtenerDatosINA219( Adafruit_INA219 &  ina219){
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
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");
  return;
}

/*-------------------------------------------FuncionesParaBME280-----------------------------------------------------*/
void FunIniciarBME280(BME280I2C & bme){
    Serial.println("Inicializando el sensor BME280...");

  // Inicializar el sensor BME280 usando Wire
  Wire.begin();
  while(!bme.begin())
  {
    Serial.println("No se encuentra el sensor BME280!");
    delay(1000);
  }

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Sensor BME280 encontrado! Éxito.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Sensor BMP280 encontrado! No hay humedad disponible.");
       break;
     default:
       Serial.println("¡Sensor desconocido encontrado! Error!");
  }

  Serial.println("Sensores inicializados. Comenzando lecturas...");
}

void FunObtenerDatosBME280(BME280I2C & bme)
{
  float temp(NAN), hum(NAN), pres(NAN);
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(pres, temp, hum, tempUnit, presUnit);
  
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
  Serial.print("\t\tHumidity: ");
  Serial.print(hum);
  Serial.print("% RH");
  Serial.print("\t\tPressure: ");
  Serial.print(pres);
  Serial.println(" Pa");
  return;
}



