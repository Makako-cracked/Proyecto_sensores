//Se definen las siguientes variables

int led = 9; //Pin donde se conecta el led
int sw = 2;  //Pin donde se conecta el switch
int pot;     //Almacena el valor leído en el potenciómetro
int mapeo;   //Almacena el valor que se escribirá analógicamente en el led

//Configuración de los pines como entradas o salidas
void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);
}

void loop() {
  //Mientras se detecte que el switch está encendido (uno lógico), se realizará la secuencia automática 
  while (digitalRead(sw) == 1){
    //Ciclo de encendido
    for (int i = 0; i < 255; i++)
    {
      analogWrite(led, i); 
      delay(5);
    }
    //Ciclo de apagado
    for (int i = 255; i > 0 ; i--)
    {
      analogWrite(led, i);
      delay(5);
    }
  }
  //Mientras se detecte que el switch está encendido (uno lógico), se realizará la secuencia manual
  //para esto, se debe de variar el potenciómetro 
  while (digitalRead(sw) == 0){
    //Lectura del potenciómetro
    pot = analogRead(A4);
    //Conversión de a un valor dentro del rango permitido para las escrituras analógicas
    mapeo = map(pot, 0, 1023, 0, 255); 
    //Escritura analógica en el led del valor anterior
    analogWrite(led, mapeo);
    delay(10);
  }
}
