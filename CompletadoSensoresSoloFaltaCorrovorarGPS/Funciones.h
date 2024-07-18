/*-------------------------------------------------Funciones-para-MAX3185------------------------------------------------------------------*/
void FunIniciarMAX31865(Adafruit_MAX31865 & thermo){
  //Arranca para la lectura de datos para tres cables
thermo.begin(MAX31865_3WIRE); // Use MAX31865_2WIRE or MAX31865_4WIRE; 2 cables y 4 cables respectivamente
return ;
}

String FunObtenerStringDatosMAX31865(Adafruit_MAX31865 & thermo){
  String datos;
  // Read the raw RTD value
//uint16_t rtd = thermo.readRTD();

// Calculate the ratio of the RTD value
//float ratio = rtd / 32768.0;

// Calculate and print the temperature
float temperature = thermo.temperature(RNOMINAL, RREF);
//7 caracteres include (.) y (,)
datos += String(temperature) + ",";// Temperatura °C

return datos;
}

/*----------------------------------FuncionesParaIna219--------------------------------------------------------------------*/
void FunIniciarINA219(Adafruit_INA219 & ina219){
  // Wire2.setSCL(24);
  // Wire2.setSDA(25);

  while(!ina219.begin(&Wire2))  delay(10);
  ina219.setCalibration_32V_2A();

}
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
static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (Serial7.available()) {
    gps.encode(Serial7.read());
    }
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec, String &cadena) {
  if (!valid) {
    cadena += ",";
  } else {
    cadena += String(val, prec)+ ",";
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len,String & cadena) {
 if (valid) {
    cadena += String(val);  // Convierte el entero a String directamente.
  } else {
    cadena += "*";  // Indica un valor inválido con un asterisco.
  }
  cadena += ",";  // Añade una coma después del número para delimitar los valores.
  smartDelay(0);  // Continúa alimentando datos GPS durante la pausa.
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, String & cadena) {
  if (!d.isValid()) {
    cadena += "****-**-**,";
  } else {
    cadena += String(d.year()) + "-" + String(d.month()) + "-" + String(d.day()) + ",";
  }

  if (!t.isValid()) {
    cadena += "**:**:**,";
  } else {
    cadena += String(t.hour()) + ":" + String(t.minute()) + ":" + String(t.second()) + ",";
  }

  // Considerando que printInt ya maneja la validación y añade una coma,
  // podemos llamar directamente a esa función sin manejo adicional aquí.
  printInt(d.age(), d.isValid(),5, cadena);

  // No es necesario llamar a smartDelay aquí ya que se debería manejar externamente
  // en el bucle principal o en otra parte del código que lo requiera.
}

static void printStr(const char *str, int len, String & cadena) {
    int slen = strlen(str);
    // Añadir el texto del string.
    for (int i = 0; i < slen; ++i) {
        cadena += str[i];
    }
    // Añadir espacios faltantes si el texto es más corto que el largo especificado.
    for (int i = slen; i < len; ++i) {
        cadena += ' ';
    }
    // Añadir una coma al final para mantener el formato CSV.
    cadena += ',';

    // No es necesario llamar a smartDelay aquí ya que se debería manejar externamente
    // en el bucle principal o en otra parte del código que lo requiera.
}
String FunObtenerStringDatosGPS6mv2() {
    String cadena = "";
r
    printFloat(gps.location.lat(), gps.location.isValid(), 11, 6, cadena);
    // Obtener la longitud y validar
    printFloat(gps.location.lng(), gps.location.isValid(), 12, 6, cadena);
    // Obtener la edad de los datos de ubicación y validar
    printInt(gps.location.age(), gps.location.isValid(), 5, cadena);
    // Obtener la fecha y hora del GPS y validar
    printDateTime(gps.date, gps.time, cadena);
    // Obtener la altitud y validar
    printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2, cadena);
    // Obtener el rumbo en grados y validar
    printFloat(gps.course.deg(), gps.course.isValid(), 7, 2, cadena);
    // Obtener la velocidad en kilómetros por hora y validar
    printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2, cadena);
    // Obtener el rumbo cardinal y validar
    printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6, cadena);

    // Calcular la distancia a Londres y validar
    unsigned long distanceKmToLondon =
        (unsigned long)TinyGPSPlus::distanceBetween(
            gps.location.lat(),
            gps.location.lng(),
            LONDON_LAT, 
            LONDON_LON) / 1000;
    printInt(distanceKmToLondon, gps.location.isValid(), 9, cadena);

    // Calcular el curso hacia Londres y validar
    double courseToLondon =
        TinyGPSPlus::courseTo(
            gps.location.lat(),
            gps.location.lng(),
            LONDON_LAT, 
            LONDON_LON);
    printFloat(courseToLondon, gps.location.isValid(), 7, 2, cadena);

    // Obtener el rumbo cardinal hacia Londres y validar
    const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);
    printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6, cadena);

    // Procesar estadísticas adicionales del GPS


    // Finalizar con un salto de línea
    cadena += "\n";

    // Espera inteligente antes de la próxima actualización
    smartDelay(1000);

    // Comprobar si se ha recibido datos GPS
    if (millis() > 5000 && gps.charsProcessed() < 10) {
        Serial.println(F("No GPS data received: check wiring"));
    }

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
/*---------------------------FuncionesParaLecturaDecomandos---------------------------*/
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