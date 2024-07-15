/*Libreria para ACS712
ACS712 by Rob Tillaart
*/
#include "ACS712.h"


ACS712  ACS(23, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

void FunIniciarACS712(ACS712 & ACS);
String FunObtenerStringDatosACS712( ACS712 & ACS, String & cadena);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  FunIniciarACS712(ACS);
}


void loop()
{
  String Corriente = "";
  FunObtenerStringDatosACS712(ACS, Corriente);
  Serial.println(Corriente);
  delay(1000);
}

void FunIniciarACS712(ACS712 & ACS){
  ACS.autoMidPoint();
}
String FunObtenerStringDatosACS712( ACS712 & ACS, String & cadena){
  cadena += String(ACS.mA_DC(),1);
  return cadena;
}
//  -- END OF FILE --
