/////////////////////////////////////////FUNCIONES////////////////////////////////////////////////////////////////

/*@FunIniciarBME280
  Se espera hasta que haya comunicación   
*/
void FunIniciarBME280(Adafruit_BME280 & bme){
  while(! bme.begin(0x76, &Wire)) delay(10);
  return;
}
String FunObtenerStringDatosBME280(Adafruit_BME280 & bme)
{
  bme.takeForcedMeasurement();

  String datos = String( bme.readTemperature() ) + ",";//Temperatura "°C"
  datos += String( bme.readHumidity() ) + ",";           //Humedad " %"
  datos += String( bme.readPressure()/ 100.0F ) + ",";   //Presión " hPa"
  return datos;
}
//----------------------------------------------Funcion Para Detectar Comandos--------------------------------------
void FunEjecutarComandos(String comando) {
  if (comando == "15xFF") {
    // Lógica para apagar todo
  } else if (comando == "E5x12") {
    // Lógica para encender todo
  } else if (comando == "F5x01") {
    // Lógica para encender el motor DC
  } else if (comando == "E5x02") {
    // Lógica para apagar el motor DC
  }else if (comando == "B5x05") {
    // Lógica para encender el calentador del segundo compartimiento
    FunPWMParaHeatingPad(3.3, pinHeadtingPad);
  } else if (comando == "A5x06") {
    // Lógica para apagar el calentador del segundo compartimiento
    FunPWMParaHeatingPad(0, pinHeadtingPad);
  } else if (comando == "55x0B") {
    // Lógica para encender todos los actuadores
  } else if (comando == "45x0C") {
    // Lógica para apagar todos los actuadores
  }else if (comando == "35x0D") {
    // Lógica para mover el nanosatélite a la derecha
  } else if (comando == "25x0E") {

    // Lógica para mover el nanosatélite a la izquierda
  } else if (comando == "15x0F") {

    // Lógica para mover el nanosatélite al frente
  } else if (comando == "F5x11") {

    // Lógica para mover el nanosatélite hacia atrás
  }
  else {
    //No reconoceComandos 
  }
}
/*----------------------------------------Control de heatingPad-------------------------*/
void FunPWMParaHeatingPad(float valorVoltage, int pinHP){
  int voltage = (valorVoltage/3.3) * 4095;
  analogWrite(pinHP, voltage);
}

void FunControlHeatingPad(float temp4 , float temp5, int fetPin){
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
/*-----------------------------------------------Funciones para termistores-----------------*/
String FunObtenerStringDatosTermistor(int Termocupla[]){
  String cadena = "";
  for (int i= 0; i < 3; i++){
  int ReadADC1 = analogRead(Termocupla[i]);
  float T_1 = (ReadADC1*R0)/(1023-ReadADC1);  //Valor a partir de la lectura analógica con el dato convertido a digital
  //float Volt1 = 3.3*resTer1/(resTer1 + R0);      // voltaje calculado a partir del calculo de la resistencia es igual a ReadADC32*Resolucion
  T_1 =T_1/R0;
  T_1 = log(T_1);
  T_1 /= B;
  T_1 += 1.0 / T0;
  T_1 = 1.0 / T_1;
  T_1 -= 273.15;
  temperaturas[i] = T_1;
  cadena += String(T_1) + ",";//Temperatura °C
  }
  return cadena;
}
//-------------------------------------Pines analogicos-------------------------------------
void FunIniciarM102(){
  pinMode(pinAN1, INPUT);
  pinMode(pinAN2, INPUT);
  pinMode(pinAN3, INPUT);
  pinMode(pinAN4, INPUT);
  pinMode(pinAN5, INPUT);
  pinMode(pwmW1, OUTPUT);
  pinMode(pwmW2, OUTPUT);
  pinMode(pwmW3, OUTPUT);
  pinMode(pwmW4, OUTPUT);
  FunPWMParaHeatingPad(3.3, pwmW1);
  FunPWMParaHeatingPad(3.3, pwmW2);
  FunPWMParaHeatingPad(3.3, pwmW3);
  FunPWMParaHeatingPad(3.3, pwmW4);
}
String FunObtenerStringDatosM102(int pinLectura){
  int valorADC = analogRead(pinLectura); // Leer el valor ADC del pin
  float voltage = (valorADC * 3.3) /4095.0; // Convertir el valor ADC a voltaje
  String cadena = String(voltage) + ",";
  return cadena;
}