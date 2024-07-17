#include <math.h>

#define T4 18
#define T5 19
#define T6 20

float R2 = 100000;

float A = -2.533236945E-3;
float B = 6.227902728E-4;
float C = -8.513794896E-7;

int fetPin = 2;

float termistor(int RawADC) {
  
  long resistencia;  
  
  float temp;

  resistencia = R2*1/((1024/RawADC)-1);
  
  temp = log(resistencia);
  
  temp = 1 / (A + (B * temp) + (C * temp * temp * temp));
  
  temp = temp - 273.15;              

  return temp;
  
}

void setup() {
  
  Serial.begin(9600);
  pinMode(fetPin,OUTPUT);
  
}

void loop() {
  
  float temp;
  float temp4;
  float temp5;
  float temp6;
  
  temp4 = termistor(analogRead(T4));
  
  Serial.print("Temperatura lado derecho: ");

  Serial.print(temp4,1);
  
  temp5 = termistor(analogRead(T5));
  
  Serial.print("Temperatura lado izquierdo: ");

  Serial.print(temp5,1);
  
  temp6 = termistor(analogRead(T6));
  
  Serial.print("Temperatura en el HP: ");

  Serial.print(temp6,1);
  
  Serial.println();

  
  delay(500);
  
}

FunControlHeatingPad(float temp4 , float temp5, int fetPin){
  float temp = (temp4+temp5)/2;

  if(temp<15){
    analogWrite(fetPin,4095);
  }
  else if(temp>=15 && temp<20){
    analogWrite(fetPin,1360);
  }
  else {
    analogWrite(fetPin,0);
  }
}
