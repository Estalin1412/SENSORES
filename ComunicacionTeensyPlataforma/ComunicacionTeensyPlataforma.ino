
String cadenaComandos;
void setup() {
  Serial.begin(115200);  // Inicia el Serial para depuración por el puerto USB
  Serial1.begin(4800);  // Inicia Serial1 para recibir datos de la otra Teensy
}
void loop(){
  cadenaComandos = "";
  cadenaComandos += FunObtenerComandosTeensyPlataforma(cadenaComandos);
  delay(1000);  
}

String FunObtenerComandosTeensyPlataforma( String & receivedMessage) {
  while (Serial1.available() > 0 && receivedMessage.length() < 5) {
    char receivedChar = Serial1.read();  // Lee un carácter del puerto Serial1
    receivedMessage += receivedChar;  // Agrega el carácter al mensaje
  }
  return receivedMessage;
}
