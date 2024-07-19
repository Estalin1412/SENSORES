/*-------------------------------------------------Funciones-para-MAX3185------------------------------------------------------------------*/
/*@FunIniciarMAX31865
  Inicia la lectura para la conexión con tres cables
*/
void FunIniciarMAX31865(Adafruit_MAX31865 & thermo){
  //Arranca para la lectura de datos para tres cables
thermo.begin(MAX31865_3WIRE); // Use MAX31865_2WIRE or MAX31865_4WIRE; 2 cables y 4 cables respectivamente
return ;
}
/*@FunObtenerStringDatosMAX31865
  Crea una cadema; sera para la temperatura
  Se usa método del objeto para obtener temperatura tipo float y guardar
  Se cambia tipo string y se retorna en cadena
*/
String FunObtenerStringDatosMAX31865(Adafruit_MAX31865 & thermo){
String datos;
float temperature = thermo.temperature(RNOMINAL, RREF);
//7 caracteres include (.) y (,)
datos += String(temperature) + ",";// Temperatura °C

return datos;
}

/*----------------------------------FuncionesParaIna219--------------------------------------------------------------------*/
/*@FunIniciarINA219
  Espera hasta empesar comunicación en el wire2(pines 24 SCL y 25 SDA)
  Calibra para que sea de 5V
*/
void FunIniciarINA219(Adafruit_INA219 & ina219){
  // Wire2.setSCL(24);
  // Wire2.setSDA(25);

  while(!ina219.begin(&Wire2))  delay(10);
  ina219.setCalibration_32V_2A();

}

/*@FunObtenerStringDatosINA219
  Se crea variables para datos
  Se usa metodos del objeto para leer datos y gaurdar en sus respectivas variables
  Se cambia a varible string y se devuelve en una cadena
*/
String FunObtenerStringDatosINA219( Adafruit_INA219 &  ina219){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  //float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  //power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  String datos = String(loadvoltage)+ "," ;// Voltage " V\n" , 
  datos += String(current_mA) + "," ;           // Corriente" mA\n";

  //datos += "Power: " + String(power_mW) + ",";               //" mW\n";
  return datos;
}

/*-------------------------------------------FuncionesParaBME280-----------------------------------------------------*/
/*@FunIniciarBME280
  Se espera hasta que haya comunicación   
*/
void FunIniciarBME280(Adafruit_BME280 & bme){
  while(! bme.begin(0x76, &Wire2)) delay(10);
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
/*------------------------------FUNCIONES-PARA-GPS-gps6mv2--------------------------------------------*/
void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (Serial7.available()) {
      gps.encode(Serial7.read());
    }
  } while (millis() - start < ms);
}

String FunObtenerStringDatosGPS6mv2() {
  smartDelay(1000);
  String cadena = "";
  // Imprime la latitud, longitud, altitud, fecha y hora
  cadena += String(gps.location.lat(), 4) + ",";
  cadena += String(gps.location.lng(), 4) + ",";
  cadena += String(gps.altitude.meters()) + ",";
  cadena += String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + "24,";
  cadena += String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + ",";
  return cadena;
}

/*-------------------------FUNCIONES-PARA-COMUNICACION-ENTRE-TEENSYS----------------------------------*/

String FunObtenerStringDatosComunicacionTeensyTeensy(HardwareSerial &Serialx){
    if (Serialx.available() > 0){
    // Lee los datos recibidos
    String received = Serialx.readStringUntil('\n');
    
    // Imprime los datos en el monitor serie
    return received;
    }
    return "";

}
String FunObtenerComandosTeensyPlataforma( String & receivedMessage) {
  int i = 0;
  while (Serial1.available() > 0 && receivedMessage.length() < 5) {
    char receivedChar = Serial1.read();  // Lee un carácter del puerto Serial1
    receivedMessage += receivedChar;  // Agrega el carácter al mensaje
  }
  return receivedMessage;
}

/*--------------------------Funcion_para_termistores------------------------------------------------- */
String FunObtenerStringDatosTermistor(int Termocupla[]){

  String cadena = "";
  for (int i= 0; i<6; i++){
  int ReadADC1 = analogRead(Termocupla[i]);
  float T_1 = (ReadADC1*R0)/(1023-ReadADC1);  //Valor a partir de la lectura analógica con el dato convertido a digital
  //float Volt1 = 3.3*resTer1/(resTer1 + R0);      // voltaje calculado a partir del calculo de la resistencia es igual a ReadADC32*Resolucion
  T_1 =T_1/R0;
  T_1 = log(T_1);
  T_1 /= B;
  T_1 += 1.0 / T0;
  T_1 = 1.0 / T_1;
  T_1 -= 273.15;
  Termistores[i] = T_1;
  cadena += String(T_1) + ",";//Temperatura °C
  }
  return cadena;
}
/*--------------------------------FUNCIONES_PARA_GUARDADO_SDcard--------------------------------------*/
void FuncionEscribirEnSDcard(File & myFile, String messenger){
  if (!SD.begin(chipSelect)) {
  }
  
  // open the file. 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.print(messenger);
    myFile.close();
  }
}
void FuncionLeerEnSDcard(File & myFile){
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  return;
}



/*---------------------------------FUNCIONES_PARA_ACS712--------------------------------------------*/
void FunIniciarACS712(ACS712 & ACS){
  ACS.autoMidPoint();
}
String FunObtenerStringDatosACS712( ACS712 & ACS){
  String cadena = String(ACS.mA_DC(),1);//Corriente A
  return cadena;
}

/*------------------------ParaFuncionesPWm_HetingPad_1--------------------------------------------------------*/
void FunPWMParaHeatingPad(float valorVoltage){
  int voltage = (valorVoltage/3.3) * 4095;
  analogWrite(2, voltage);
  delay(2000);
}
//Para controlarHetingpad1
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
/*---------------------------Funciones Para Lectura De comandos---------------------------*/
void FunProcesarComandos(String comandos) {
  if(comandos == "" ) return; 
  int cantidadComandos = contarComandos(comandos, ',');
  String comandosSeparados[cantidadComandos];
  
  splitString(comandos, ',', comandosSeparados, cantidadComandos);

  for (int i = 0; i < cantidadComandos; i++) {
    FunEjecutarComandos(comandosSeparados[i]);
  }
}

int contarComandos(String data, char separador) {
  int contador = 1; // Iniciamos en 1 porque el último elemento no tiene un delimitador después de él.
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == separador) {
      contador++;
    }
  }
  return contador;
}

void splitString(String data, char separador, String* outputArray, int size) {
  int i = 0;
  int endIndex = data.indexOf(separador);
  int j = 0;

  while (endIndex >= 0) {
    outputArray[j] = data.substring(i, endIndex);
    j++;
    i = endIndex + 1;
    endIndex = data.indexOf(separador, i);
  }
  // Asegurarse de añadir la última parte del string
  outputArray[j] = data.substring(i);
}

void FunEjecutarComandos(String comando) {
  if (comando == "15xFF") {
    // Lógica para apagar todo
  }/* else if (comando == "E5x12") {
    Serial.println("Ignition System: Turn everything on");
    // Lógica para encender todo
  } else if (comando == "F5x01") {
    Serial.println("DC Motor Off: Start the motor inside the system");
    // Lógica para encender el motor DC
  } else if (comando == "E5x02") {
    Serial.println("DC Motor On: Shutting down the motor inside the system");
    // Lógica para apagar el motor DC
  }*/ else if (comando == "D5x03") {
    //ApagarHeatingpad1
    FunPWMParaHeatingPad(0);
  } else if (comando == "C5x04") {
    //Encender HeatingPad1
    FunPWMParaHeatingPad(3.3);
  }/* else if (comando == "B5x05") {
    Serial.println("Heating Pad 2 Power on: Switch on the heater of the second compartment");
    // Lógica para encender el calentador del segundo compartimiento
  } else if (comando == "A5x06") {
    Serial.println("Heating Pad 2 Power off: Shutdown of the second compartment heater");
    // Lógica para apagar el calentador del segundo compartimiento
  } else if (comando == "55x0B") {
    Serial.println("All actuators on (Heater and Motor): Turn on all payload actuators");
    // Lógica para encender todos los actuadores
  } else if (comando == "45x0C") {
    Serial.println("All actuators off (Heater and Motor): Turn off all payload actuators");
    // Lógica para apagar todos los actuadores
  }else if (comando == "35x0D") {
    Serial.println("Turn Right: Moves the nanosatellite to the right");
    // Lógica para mover el nanosatélite a la derecha
  } else if (comando == "25x0E") {
    Serial.println("Turn Left: Moves the nanosatellite to the left");
    // Lógica para mover el nanosatélite a la izquierda
  } else if (comando == "15x0F") {
    Serial.println("Turn Front: Moves the nanosatellite to the front");
    // Lógica para mover el nanosatélite al frente
  } else if (comando == "F5x11") {
    Serial.println("Turn Back: Moves the nanosatellite to the back");
    // Lógica para mover el nanosatélite hacia atrás
  }
  */else {
    //No reconoceComandos 
  }
}

//////////////////////////////////////////////////////////
//FUNCIONES CUALQUIERA
void FuncionCorregirCaracter(String & cadena, int tam){
  int i = tam - cadena.length();
  int j = 0;
  while (j < i)
  {
    cadena += " ";
    j++;
  }
}