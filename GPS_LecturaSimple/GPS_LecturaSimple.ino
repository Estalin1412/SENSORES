void setup() {
  // Iniciar el puerto serial USB para la depuración
  Serial.begin(115200);
  // Esperar a que se inicie el puerto serial
  while (!Serial) {
    delay(10);
  }
  
  // Iniciar la comunicación Serial1 a 9600 bps para el GPS
  Serial7.begin(9600);
}

void loop() {
  // Leer datos del GPS
  if (Serial7.available()) {
    String line = Serial7.readStringUntil('\n');
    // Imprimir la línea leída en el puerto serial de depuración
    Serial.println(line);
  }
}
