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
//Objeto de archivo en SDcard
File Archivo;
const int chipSelect = BUILTIN_SDCARD;
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);
/*-----------------------------------------PROTOTIPOS DE FUNCIONES-------------------------------------------------------------------------*/
//Prototipos de INA219
/*
Verificación de conexion; se usa wire2
Calibra datos para 5V
*/
void FunObtenerDatosINA219( Adafruit_INA219 &  ina219);

String FunObtenerStringDatosINA219( Adafruit_INA219 &  ina219);
//Prototipos de BME280
void FunIniciarBME280(Adafruit_BME280 & bme);

String FunObtenerStringDatosBME280(Adafruit_BME280 & bme);
//Prototipos de MAX3185
void FunIniciarMAX31865(Adafruit_MAX31865 & thermo);
String FunObtenerStringDatosMAX31865(Adafruit_MAX31865 & thermo);
//Prototipos de GPS
String FunObtenerStringDatosGPS6mv2();
static void smartDelay(unsigned long ms);

static void printStr(const char *str, int len, String &);
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, String &);
static void printFloat(float val, bool valid, int len, int prec, String &);
static void printInt(unsigned long val, bool valid, int len, String &);
//Prototipos comunicacion entre teensy
String FunObtenerStringDatosComunicacionTeensyTeensy(HardwareSerial &Serialx);
//Prototipos para corriente
void FunIniciarACS712(ACS712 & ACS);
String FunObtenerStringDatosACS712( ACS712 & ACS);
//FUNCIONE CREADAS PARA FACILITAR OPERACIONES
void FuncionCorregirCaracter(String & cadena, int tam);
// Para  guardar en SDcard
void FuncionLeerEnSDcard(File & myFile);
void FuncionEscribirEnSDcard(File & myFile, String messenger);