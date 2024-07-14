
#include <SD.h>
#include <SPI.h>

File Archivo;
const int chipSelect = BUILTIN_SDCARD;//Buidsl
void FuncionLeerEnSDcard(File & myFile);
void FuncionEscribirEnSDcard(File & myFile, String messenger);

void setup()
{
 //UNCOMMENT THESE TWO LINES FOR TEENSY AUDIO BOARD:
 //SPI.setMOSI(7);  // Audio shield has MOSI on pin 7
 //SPI.setSCK(14);  // Audio shield has SCK on pin 14
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  String mensaje = "qessssssssss";
  FuncionEscribirEnSDcard(Archivo, mensaje);
  FuncionLeerEnSDcard(Archivo);

}

void loop()
{
	// nothing happens after setup
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
void FuncionLeerEnSDcard(File & myFile){
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
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

