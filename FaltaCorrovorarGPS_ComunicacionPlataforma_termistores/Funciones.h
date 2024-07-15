/*-------------------------------------------------Funciones-para-MAX3185------------------------------------------------------------------*/
void FunIniciarMAX31865(Adafruit_MAX31865 & thermo){
  //Initialize the MAX31865 and set the wire configuration
thermo.begin(MAX31865_3WIRE); // Use MAX31865_2WIRE or MAX31865_4WIRE 2 cables y 4 cables respectivamente
return ;
}
String FunObtenerStringDatosMAX31865(Adafruit_MAX31865 & thermo){
  String datos;
  // Read the raw RTD value
uint16_t rtd = thermo.readRTD();

// Calculate the ratio of the RTD value
float ratio = rtd / 32768.0;

// Calculate and print the temperature
float temperature = thermo.temperature(RNOMINAL, RREF);
//7 caracteres include (.) y (,)
datos += "Temperature: " + String(temperature) + ",";// °C

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
  
  String datos ="Load Voltage: " + String(loadvoltage)+ "," ;//" V\n" , 
  datos += "Current: " + String(current_mA) + "," ;           //" mA\n";

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

  String datos ="Temperature = " + String( bme.readTemperature() ) + ",";//"°C"
  datos += "Humidity = " + String( bme.readHumidity() ) + ",";           //" %"
  datos += "Pressure = " + String( bme.readPressure()/ 100.0F ) + ",";   // " hPa"
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
    while (len-- > 1) {
      cadena += "*";
    }
    cadena += " ";
  } else {
    cadena += String(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . y -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i) {
      cadena += " " ;
    }
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len,String & cadena) {
  char sz[32] = "*****************";
  if (valid) {
    sprintf(sz, "%ld", val);
  }
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i) {
    sz[i] = ' ';
  }
  if (len > 0) {
    sz[len - 1] = ' ';
  }
  cadena += sz;
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, String & cadena) {
  if (!d.isValid()) {
    cadena += "********** ";
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    cadena += sz;
  }

  if (!t.isValid()) {
    cadena += "******** ";
  } else {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    cadena += sz;
  }

  printInt(d.age(), d.isValid(), 5, cadena);
  smartDelay(0);
}

static void printStr(const char *str, int len, String & cadena) {
  int slen = strlen(str);
  for (int i = 0; i < len; ++i) {
    cadena += (i < slen ? str[i] : ' ');
  }
  smartDelay(0);
}
String FunObtenerStringDatosGPS6mv2()
{
  String cadena = "";
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5, cadena);
  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1, cadena);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6, cadena);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6, cadena);
  printInt(gps.location.age(), gps.location.isValid(), 5, cadena);
  printDateTime(gps.date, gps.time, cadena);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2,  cadena);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2, cadena);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2, cadena);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6, cadena);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9, cadena);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2, cadena);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6, cadena);

  printInt(gps.charsProcessed(), true, 6, cadena);
  printInt(gps.sentencesWithFix(), true, 10, cadena);
  printInt(gps.failedChecksum(), true, 9, cadena);
  cadena += "\n";

  smartDelay(1000);

  if ( millis() > 5000 && gps.charsProcessed() < 10 ) Serial.println(F("No GPS data received: check wiring"));
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


/*---------------------------------FUNCIONES_PARA_ACS712--------------------------------------------*/
void FunIniciarACS712(ACS712 & ACS){
  ACS.autoMidPoint();
}
String FunObtenerStringDatosACS712( ACS712 & ACS){
  String cadena = String(ACS.mA_DC(),1);
  return cadena;
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