/*--------------------------------------------------------------------VARIABLES------------------------------------------------------------*/
//Para BME280
#define SEALEVELPRESSURE_HPA ( 1013.25)
//Para INA219
#define RREF 430.0
#define RNOMINAL 100.0
//Para GPS
static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
/*Definimos objetos*/
//Objeto de INA219
Adafruit_INA219 SensorCorriente_Ina219;

//Objeto de INA219
Adafruit_BME280 Sensor01Bme280;

//Objeto de ina219
Adafruit_MAX31865 SensorMAX3185 = Adafruit_MAX31865(10);

//Objeto de GPS
TinyGPSPlus gps;
/*-----------------------------------------PROTOTIPOS DE FUNCIONES-------------------------------------------------------------------------*/
//Prototipos de INA219
void FunIniciarINA219(Adafruit_INA219 & ina219);
/*
Verificación de conexion; se usa wire2
Calibra datos para 5V
*/
void FunObtenerDatosINA219( Adafruit_INA219 &  ina219);

void FunIniciarINA219(Adafruit_INA219 & ina219, HardwareSerial &);
void FunObtenerDatosINA219( Adafruit_INA219 &  ina219, HardwareSerial &);
//Prototipos de BME280
void FunIniciarBME280(Adafruit_BME280 & bme);
void FunObtenerDatosBME280(Adafruit_BME280 & bme);

void FunIniciarBME280(Adafruit_BME280 & bme, HardwareSerial &);
void FunObtenerDatosBME280(Adafruit_BME280 & bme, HardwareSerial &);
//Prototipos de MAX3185
void FunIniciarMAX3185(Adafruit_MAX31865 & thermo);
void FunObtenerDatosMAX3185(Adafruit_MAX31865 & thermo);

void FunIniciarMAX3185(Adafruit_MAX31865 & thermo, HardwareSerial &);
void FunObtenerDatosMAX3185(Adafruit_MAX31865 & thermo, HardwareSerial &);
//Prototipos de GPS
static void printStr(const char *str, int len);
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t);
static void printFloat(float val, bool valid, int len, int prec);
static void printInt(unsigned long val, bool valid, int len);
static void smartDelay(unsigned long ms);

static void printStr(const char *str, int len, HardwareSerial &);
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, HardwareSerial &);
static void printFloat(float val, bool valid, int len, int prec, HardwareSerial &);
static void printInt(unsigned long val, bool valid, int len, HardwareSerial &);
//Prototipos comunicacion entre teensy
void FunComunicacionTeensyTeensy(HardwareSerial &Serialx);
void FunComunicacionTeensyTeensy(HardwareSerial &Serialx, HardwareSerial & Serialy);