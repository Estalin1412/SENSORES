/*--------------------------------------------------------------------VARIABLES------------------------------------------------------------*/
//Para MAX31865
#define CS_PIN 10
#define DI_PIN 11
#define DO_PIN 12
#define CLK_PIN 13

#define RREF 430.0 // Reference resistor value for PT100
#define RNOMINAL 100.0 // Nominal resistance at 0 degrees Celsius for PT100

//Para BME280
#define SEALEVELPRESSURE_HPA ( 1013.25)
//Para GPS
static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
/*Definimos objetos*/
//Objeto de INA219
Adafruit_INA219 SensorCorriente_Ina219;

//Objeto de INA219
Adafruit_BME280 Sensor01Bme280;

//Objeto de MAX31865
Adafruit_MAX31865 SensorMAX31865 = Adafruit_MAX31865(CS_PIN, DI_PIN, DO_PIN, CLK_PIN);

//Objeto de GPS
TinyGPSPlus gps;
//Objeto ACS712
ACS712  SensorACS712(23, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

/*-----------------------------------------PROTOTIPOS DE FUNCIONES-------------------------------------------------------------------------*/
//Prototipos de INA219
/*
Verificación de conexion; se usa wire2
Calibra datos para 5V
*/
void FunObtenerDatosINA219( Adafruit_INA219 &  ina219);

void FunIniciarINA219(Adafruit_INA219 & ina219, HardwareSerial &);
void FunObtenerDatosINA219( Adafruit_INA219 &  ina219, HardwareSerial &);

String FunObtenerStringDatosINA219( Adafruit_INA219 &  ina219);
//Prototipos de BME280
void FunIniciarBME280(Adafruit_BME280 & bme);
void FunObtenerDatosBME280(Adafruit_BME280 & bme);

void FunIniciarBME280(Adafruit_BME280 & bme, HardwareSerial &);
void FunObtenerDatosBME280(Adafruit_BME280 & bme, HardwareSerial &);

String FunObtenerStringDatosBME280(Adafruit_BME280 & bme);
//Prototipos de MAX3185
void FunIniciarMAX31865(Adafruit_MAX31865 & thermo);
String FunObtenerStringDatosMAX31865(Adafruit_MAX31865 & thermo);
//Prototipos de GPS
String FunObtenerStringDatosGPS6mv2();
static void smartDelay(unsigned long ms);

static void printStr(const char *str, int len, HardwareSerial &);
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, HardwareSerial &);
static void printFloat(float val, bool valid, int len, int prec, HardwareSerial &);
static void printInt(unsigned long val, bool valid, int len, HardwareSerial &);
//Prototipos comunicacion entre teensy
void FunComunicacionTeensyTeensy(HardwareSerial &Serialx);
void FunComunicacionTeensyTeensy(HardwareSerial &Serialx, HardwareSerial & Serialy);
//Prototipos para corriente
void FunIniciarACS712(ACS712 & ACS);
String FunObtenerStringDatosACS712( ACS712 & ACS);