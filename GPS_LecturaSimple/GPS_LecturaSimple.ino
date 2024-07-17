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

///////////////////////////////////////////////////////////////////////////////////////
int contarComandos(String data, char separador) {
  int contador = 1; // Iniciamos en 1 porque el último elemento no tiene un delimitador después de él.
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == separador) {
      contador++;
    }
  }
  return contador;
}


void splitString(String data, char separador, String* outputArray, int size){
  
  int i = 0;
  int endIndex = data.indexOf(separador);
  int j = 0;

  int end = data.indexOf("\n");
  while (endIndex >= 0 && endIndex <= end) {
    outputArray[j] = data.substring(i, endIndex);
    j++;
    i = endIndex + 1;
    endIndex = data.indexOf(separador, i);
    
  }

}

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
