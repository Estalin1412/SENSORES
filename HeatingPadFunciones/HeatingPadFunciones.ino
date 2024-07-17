String  diccionario[] = {
//EncenderSistema
"15xFF",
"E5x12",
//EncenderMotores
"F5x01",
"E5x02",
//EncenderHeatingPad1
"D5x03",
"C5x04",
//EncenderHeatingPad2
"B5x05",
"A5x06",
//EncenderActuadoresMotores
"55x0B",
"45x0C",
//Turn rigth 
"35x0D", 
//Turn Left 
"25x0E", 
//Turn Front 
"15x0F",
//Turn Back  
"F5x11" 
};

String cadena[] =
{
//EncenderSistema
"15xF",
//EncenderMotores
"F5x01",
//EncenderHeatingPad1
"D5x03",
//EncenderHeatingPad2
"B5x05",
//EncenderActuadoresMotores
"55x0B",
//Turn rigth 
"35x0D", 
}; 

class ControlHeatingPad{
  int Estado = 4095;
  private:
  public:
    ControlHeatingPad( String cadena[]){
        if(cadena[2] == diccionario[4]){ 
          Estado = 0;
        }
        else{
          Estado = 4095;
        }
    }
  ~ControlHeatingPad(){}
    int getEstado() {
      return Estado;
    }
};



void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  analogWriteResolution(12); // 12 bits de resolución para una mejor precisión
}

void loop() {
  // Ejemplo de ajuste de frecuencia
  float valorDeVoltajeQueQuiero = 3.3;
  int voltage = (valorDeVoltajeQueQuiero/3.3) * 4096;
  ControlHeatingPad InOutHeating(cadena);
  analogWrite(2, InOutHeating.getEstado());
  Serial.println(diccionario[4]);
  delay(2000);
}

void funPWMParaHeatinPad(float valorVoltage){
  int voltage = (valorVoltage/3.3) * 4095;
  analogWrite(2, voltage);
  delay(2000);
}

