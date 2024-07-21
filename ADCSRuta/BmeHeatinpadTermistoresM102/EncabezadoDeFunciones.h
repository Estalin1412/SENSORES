-/*---------------------------------------------Variables------------------------------------------------------*/
//Objeto de BME280
Adafruit_BME280 SensorBme280;

#define SEALEVELPRESSURE_HPA ( 1013.25)
//Para heting pad 
#define pinHeadtingPad 5
//Para termistorse
#define Resolucion 3.3/1023
#define R0 114000
#define T0 300.15
#define B 3950
int   pinesTermistores[3] = {20,21,22};
float temperaturas[3];
//Para M102
#define pinAN1 15
#define pinAN2 14
#define pinAN3 23
#define pinAN4 40
#define pinAN5 41

#define pwmW1 6
#define pwmW2 37
#define pwmW3 36
#define pwmW4 33
/*------------------------------------------Encabezado de funciones---------------------------------------------*/
//Para BME280
void FunIniciarBME280(Adafruit_BME280 & bme);
void FunEjecutarComandos(String comando); 
//FuncionActivarPWM
void FunPWMParaHeatingPad(float valorVoltage, int pinHP);
//Objeto para BNO055
String data, dataComandos;