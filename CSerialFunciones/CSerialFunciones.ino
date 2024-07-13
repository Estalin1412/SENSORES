
void FunComunicacionTeensy(HardwareSerial &Serialx);

void setup() {
  Serial.begin(4800);      // Inicializa la comunicación serie para el monitor serie
  Serial8.begin(4800);   // Inicializa Serial1 para recibir datos a 115200 baudios
  Serial.printf("Soy el receptor:");
}

void loop() {

  FunComunicacionTeensy(Serial8);
}
void FunComunicacionTeensy(HardwareSerial &Serialx){
    if (Serialx.available() > 0) {
    // Lee los datos recibidos
    String received = Serialx.readStringUntil('\n');
    
    // Imprime los datos en el monitor serie
    Serial.print("Received: ");
    Serial.println(received);
  }
}
