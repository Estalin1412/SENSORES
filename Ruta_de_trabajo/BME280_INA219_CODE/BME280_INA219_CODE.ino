#include <Wire.h>
#include <Adafruit_INA219.h>
#include <BME280.h>
#include <BME280I2C.h>

// Crear instancias de los sensores
Adafruit_INA219 ina219;
BME280I2C bme; // Default : forced mode, standby time = 1000 ms
               // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
      // Espera a que se abra la consola serie (para placas como Leonardo)
      delay(1);
  }

  Serial.println("Inicializando el sensor INA219...");

  // Configurar los pines alternativos para Wire1
  Wire1.setSDA(25); // Configurar el pin 25 como SDA
  Wire1.setSCL(24); // Configurar el pin 24 como SCL
  Wire1.begin();

  // Inicializa el sensor INA219 usando Wire1
  while (ina219.begin(&Wire1)) {
    Serial.println("No se encuentra el sensor INA219.");
    delay(10);
    
  }

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

void loop(void) {
  // Lectura del sensor INA219
  float shuntVoltage_mV = 0;
  float busVoltage_V = 0;
  float current_mA = 0;
  float power_mW = 0;
  float loadVoltage_V = 0;

  ObtenerDatosINA219( shuntVoltage_mV, busVoltage_V, current_mA, power_mW, loadVoltage_V);
  // Imprimir resultados del sensor INA219
  Serial.print("Bus Voltage:   "); Serial.print(busVoltage_V); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntVoltage_mV); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadVoltage_V); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  // Lectura del sensor BME280
  float temp(NAN), hum(NAN), pres(NAN);
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  ObtenerDatosBME280(temp, hum, pres, tempUnit, presUnit);

  // Imprimir resultados del sensor BME280
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
  Serial.print("\t\tHumidity: ");
  Serial.print(hum);
  Serial.print("% RH");
  Serial.print("\t\tPressure: ");
  Serial.print(pres);
  Serial.println(" Pa");

  // Esperar 2 segundos antes de la siguiente lectura
  delay(2000);
}


void ObtenerDatosINA219(  float & shuntVoltage_mV,  float & busVoltage_V,  float & current_mA,  float & power_mW,  float & loadVoltage_V)
{
  shuntVoltage_mV = ina219.getShuntVoltage_mV();
  busVoltage_V = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000);
  return;
}

void ObtenerDatosBME280(float & temp, float & hum, float & pres,BME280::TempUnit & tempUnit, BME280::PresUnit & presUnit)
{
  bme.read(pres, temp, hum, tempUnit, presUnit);
  return;
}
