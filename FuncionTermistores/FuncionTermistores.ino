#define Resolucion 3.3/1023
#define R0 114000
#define T0 300.15
#define B 3950
float resTer1 = 0;
float Volt1 = 0;
float T_1 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(FunObtnerStirngDatoTermistor(20));
 delay(2000);
}


String FunObtnerStirngDatoTermistor(int  Termocupla1){

  int ReadADC1 = analogRead(Termocupla1);

  float T_1 = (ReadADC1*R0)/(1023-ReadADC1);  //Valor a partir de la lectura analógica con el dato convertido a digital
  //float Volt1 = 3.3*resTer1/(resTer1 + R0);      // voltaje calculado a partir del calculo de la resistencia es igual a ReadADC32*Resolucion
  T_1 =T_1/R0;
  T_1 = log(T_1);
  T_1 /= B;
  T_1 += 1.0 / T0;
  T_1 = 1.0 / T_1;
  T_1 -= 273.15;

  return String(T_1);
}