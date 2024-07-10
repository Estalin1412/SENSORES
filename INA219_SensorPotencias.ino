/*Librerias 
  Mismo arduino
*/
#include <Wire.h>

/*Librerias para INA219
 Adafruit INA219 by adafruit

*/
#include <Adafruit_INA219.h>


#define PinIna219SCL 24
#define PinIna219SDA 25

/*Crear Objeto ina219 para las mediciones*/
Adafruit_INA219 Sensor01_ina219;
void FunIniciarINA219(Adafruit_INA219 &);
void FunObtenerDatosINA219(Adafruit_INA219 &);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while(!Serial) delay(10);
  
  Serial.println("Serial Init...");
  FunIniciarINA219(Sensor01_ina219);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  FunObtenerDatosINA219(Sensor01_ina219);
  delay(2000);
}

void FunIniciarINA219(Adafruit_INA219 & ina219){
  Wire2.setSCL(24);
  Wire2.setSDA(25);

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

