#include <SD.h>

// Definir el pin de selección del chip de la tarjeta SD
const int chipSelect = BUILTIN_SDCARD;
File myFile;

void setup() {
  // Iniciar la comunicación serie para depuración
  Serial.begin(9600);
  // Inicializar la tarjeta SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Error inicializando la tarjeta SD.");
    return;
  } else {
    Serial.println("Tarjeta SD inicializada correctamente.");
  }

  // Abrir el archivo en modo de escritura para vaciarlo
  File myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    // Truncar el archivo para vaciarlo
    myFile.seek(0);
    myFile.truncate(0);
    myFile.close();
    Serial.println("Archivo test.txt vaciado exitosamente.");
  } else {
    Serial.println("Error al abrir el archivo test.txt.");
  }

}

void loop() {

  delay(2000);
}

void LeerArchivo(){
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
}
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
