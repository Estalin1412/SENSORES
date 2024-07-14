//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------FuncionesParaIna219--------------------------------------------------------------------*/
void FunIniciarINA219(Adafruit_INA219 & ina219){
  // Wire2.setSCL(24);
  // Wire2.setSDA(25);

  while(!ina219.begin(&Wire2))  delay(10);
  ina219.setCalibration_32V_2A();

}

void FunObtenerDatosINA219( Adafruit_INA219 &  ina219){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");
  return;
}

void FunIniciarINA219(Adafruit_INA219 & ina219, HardwareSerial & Serialx){
  // Wire2.setSCL(24);
  // Wire2.setSDA(25);
  while(!ina219.begin(&Wire2))  delay(10);

  ina219.setCalibration_32V_2A();

}

void FunObtenerDatosINA219( Adafruit_INA219 &  ina219, HardwareSerial & Serialx){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serialx.print("Bus Voltage:   "); Serialx.print(busvoltage); Serialx.println(" V");
  Serialx.print("Shunt Voltage: "); Serialx.print(shuntvoltage); Serialx.println(" mV");
  Serialx.print("Load Voltage:  "); Serialx.print(loadvoltage); Serialx.println(" V");
  Serialx.print("Current:       "); Serialx.print(current_mA); Serialx.println(" mA");
  Serialx.print("Power:         "); Serialx.print(power_mW); Serialx.println(" mW");
  Serialx.println("");
  return;
}
//Para retornar Strings
String FunObtenerStringDatosINA219( Adafruit_INA219 &  ina219){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  String datos = "Bus Voltage: " + String(busvoltage) + " V\n";
  datos += "Shunt Voltage: " + String(shuntvoltage) + " mV\n";
  datos += "Load Voltage: " + String(loadvoltage) + " V\n";
  datos += "Current: " + String(current_mA) + " mA\n";
  datos += "Power: " + String(power_mW) + " mW\n";
  return datos;
}
/*-------------------------------------------FuncionesParaBME280-----------------------------------------------------*/
void FunIniciarBME280(Adafruit_BME280 & bme){
  while(! bme.begin(0x76, &Wire2)) delay(10);
  return;
}

void FunObtenerDatosBME280(Adafruit_BME280 & bme)
{
  bme.takeForcedMeasurement();

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();

}

void FunIniciarBME280(Adafruit_BME280 & bme, HardwareSerial &Serialx){
  while(! bme.begin(0x76, &Wire2)) delay(10);
  return;
}

void FunObtenerDatosBME280(Adafruit_BME280 & bme, HardwareSerial & Serialx)
{
  bme.takeForcedMeasurement();

  Serialx.print("Temperature = ");
  Serialx.print(bme.readTemperature());
  Serialx.println(" *C");

  Serialx.print("Pressure = ");

  Serialx.print(bme.readPressure() / 100.0F);
  Serialx.println(" hPa");

  Serialx.print("Approx. Altitude = ");
  Serialx.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serialx.println(" m");

  Serialx.print("Humidity = ");
  Serialx.print(bme.readHumidity());
  Serialx.println(" %");

  Serialx.println();

}
//Para retornar String
String FunObtenerStringDatosBME280(Adafruit_BME280 & bme)
{
  bme.takeForcedMeasurement();

  String datos ="Temperature = " + String( bme.readTemperature() )+" *C\n";
  datos += "Pressure = "+String( bme.readPressure()/ 100.0F ) + " hPa\n";
  datos += "Approx. Altitude = "+ String( bme.readAltitude( SEALEVELPRESSURE_HPA) )+" m\n";
  datos += "Humidity = "+ String( bme.readHumidity() ) +" %\n";
  return datos;
}
/*-------------------------------------------------Funciones-para-MAX3185------------------------------------------------------------------*/
void FunIniciarMAX3185(Adafruit_MAX31865 & thermo){
  thermo.begin(MAX31865_2WIRE);
}

void FunObtenerDatosMAX3185(Adafruit_MAX31865 & thermo){

  float temp = thermo.temperature(RNOMINAL, RREF);
  Serial.print("temp: ");
  Serial.println(temp);

}

void FunIniciarMAX3185(Adafruit_MAX31865 & thermo, HardwareSerial & Serialx){
  thermo.begin(MAX31865_2WIRE);
}

void FunObtenerDatosMAX3185(Adafruit_MAX31865 & thermo, HardwareSerial & Serialx){

  float temp = thermo.temperature(RNOMINAL, RREF);
  Serialx.print("temp: ");
  Serialx.println(temp);

}
//Para retornar String
String FunObtenerStringDatosMAX3185(Adafruit_MAX31865 & thermo){

  float temp = thermo.temperature(RNOMINAL, RREF);
  String datos ="temp: ";
  datos +=  String(temp);
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

static void printFloat(float val, bool valid, int len, int prec) {
  if (!valid) {
    while (len-- > 1) {
      Serial.print('*');
    }
    Serial.print(' ');
  } else {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . y -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i) {
      Serial.print(' ');
    }
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len) {
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
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t) {
  if (!d.isValid()) {
    Serial.print(F("********** "));
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }

  if (!t.isValid()) {
    Serial.print(F("******** "));
  } else {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len) {
  int slen = strlen(str);
  for (int i = 0; i < len; ++i) {
    Serial.print(i < slen ? str[i] : ' ');
  }
  smartDelay(0);
}
void FunActivarGPS6mv2()
{
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.println();

  smartDelay(1000);

  if ( millis() > 5000 && gps.charsProcessed() < 10 ) Serial.println(F("No GPS data received: check wiring"));
  

}


//Para Cualquier Serial

static void printFloat(float val, bool valid, int len, int prec, HardwareSerial & Serialx) {
  if (!valid) {
    while (len-- > 1) {
      Serialx.print('*');
    }
    Serialx.print(' ');
  } else {
    Serialx.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . y -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i) {
      Serialx.print(' ');
    }
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len, HardwareSerial &Serialx) {
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
  Serialx.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t, HardwareSerial & Serialx) {
  if (!d.isValid()) {
    Serialx.print(F("********** "));
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serialx.print(sz);
  }

  if (!t.isValid()) {
    Serialx.print(F("******** "));
  } else {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serialx.print(sz);
  }

  printInt(d.age(), d.isValid(), 5, Serialx);
  smartDelay(0);
}

static void printStr(const char *str, int len, HardwareSerial & Serialx) {
  int slen = strlen(str);
  for (int i = 0; i < len; ++i) {
    Serialx.print(i < slen ? str[i] : ' ');
  }
  smartDelay(0);
}
void FunActivarGPS6mv2(HardwareSerial & Serialx)
{
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5, Serialx);
  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1, Serialx);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6, Serialx);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6, Serialx);
  printInt(gps.location.age(), gps.location.isValid(), 5, Serialx);
  printDateTime(gps.date, gps.time, Serialx);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2,  Serialx);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2, Serialx);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2, Serialx);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6, Serialx);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9, Serialx);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2, Serialx);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6, Serialx);

  printInt(gps.charsProcessed(), true, 6, Serialx);
  printInt(gps.sentencesWithFix(), true, 10, Serialx);
  printInt(gps.failedChecksum(), true, 9, Serialx);
  Serialx.println();

  smartDelay(1000);

  if ( millis() > 5000 && gps.charsProcessed() < 10 ) Serial.println(F("No GPS data received: check wiring"));
  
}

/*-------------------------FUNCIONES-PARA-COMUNICACION-ENTRE-TEENSYS----------------------------------*/
void FunComunicacionTeensyTeensy(HardwareSerial &Serialx){
    if (Serialx.available() > 0) {
    // Lee los datos recibidos
    String received = Serialx.readStringUntil('\n');
    
    // Imprime los datos en el monitor serie
    Serial.print("Received: ");
    Serial.println(received);
  }
}

void FunComunicacionTeensyTeensy(HardwareSerial &Serialx, HardwareSerial & Serialy){
    if (Serialx.available() > 0) {
    // Lee los datos recibidos
    String received = Serialx.readStringUntil('\n');
    
    // Imprime los datos en el monitor serie
    Serialy.print("Received: ");
    Serialy.println(received);
  }
}
