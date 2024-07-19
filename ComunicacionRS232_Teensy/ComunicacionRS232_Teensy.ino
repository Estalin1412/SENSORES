
// Definición de comandos en formato hexadecimal
const uint8_t shutdownSystem[] = {0x15, 0xFF};
const uint8_t ignitionSystem[] = {0xE5, 0x12};
const uint8_t dcMotorOff[] = {0xF5, 0x01};
const uint8_t dcMotorOn[] = {0xE5, 0x02};
const uint8_t heatingPad1Off[] = {0xD5, 0x03};
const uint8_t heatingPad1On[] = {0xC5, 0x04};
const uint8_t heatingPad2On[] = {0xB5, 0x05};
const uint8_t heatingPad2Off[] = {0xA5, 0x06};
const uint8_t allActuatorsOn[] = {0x55, 0x0B};
const uint8_t allActuatorsOff[] = {0x45, 0x0C};

// Función para comparar comandos


// Función para ejecutar comandos
void executeCommand(const uint8_t* command) {
  if (command[0] == 0x15 && command[1] == 0xFF) {
    Serial.println("Apagando todo el sistema");
  } else if (command[0] == 0xE5 && command[1] == 0x12) {
    Serial.println("Encendiendo todo el sistema");
  } else if (command[0] == 0xF5 && command[1] == 0x01) {
    Serial.println("Apagando motor DC");
  } else if (command[0] == 0xE5 && command[1] == 0x02) {
    Serial.println("Encendiendo motor DC");
  } else if (command[0] == 0xD5 && command[1] == 0x03) {
    Serial.println("Apagando calentador del primer compartimento");
  } else if (command[0] == 0xC5 && command[1] == 0x04) {
    Serial.println("Encendiendo calentador del primer compartimento");
  } else if (command[0] == 0xB5 && command[1] == 0x05) {
    Serial.println("Encendiendo calentador del segundo compartimento");
  } else if (command[0] == 0xA5 && command[1] == 0x06) {
    Serial.println("Apagando calentador del segundo compartimento");
  } else if (command[0] == 0x55 && command[1] == 0x0B) {
    Serial.println("Encendiendo todos los actuadores");
  } else if (command[0] == 0x45 && command[1] == 0x0C) {
    Serial.println("Apagando todos los actuadores");
  } else {
    Serial.println("Comando no reconocido");
  }
}

void setup() {
  Serial.begin(115200); // Serial para depuración
  Serial1.begin(4800);  // Serial1 para comunicación RS232
}

void loop() {
  static uint8_t receivedCommand[2] = {0, 0};
  static size_t bytesRead = 0;

  // Leer datos del puerto Serial1
  while (Serial1.available() > 0) {
    receivedCommand[bytesRead] = Serial1.read();
    bytesRead++;

    // Si se han leído 2 bytes, ejecutar el comando
    if (bytesRead == 2) {
      executeCommand(receivedCommand);
      bytesRead = 0; // Resetear el contador de bytes leídos
    }
  }
  
  // Pequeño retraso para evitar el desbordamiento del buffer
  delay(10);
}
