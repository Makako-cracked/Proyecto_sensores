//Librería para trabajar con servomotores
#include <Servo.h>

//Variables para medir la distancia y trabajar con el servomotor
Servo aguja;
const unsigned int echo1 = 12;
const unsigned int trig1 = 11;

const unsigned int trig2 = 5;
const unsigned int echo2 = 4;

unsigned long duracion1;
float distancia1;
unsigned long duracion2;
float distancia2;
float dist1;
float dist2;

bool carFlag = false;

void setup() {
  //Configuración de pines de entrada, salida y control de servo
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  aguja.attach(9);
  aguja.write(0);
  delay(1000);
  Serial.begin(9600);
}

void loop() {

  //La aguja inicia desde la posición inicial
  aguja.write(0);

  //Se leen los sensores
  dist1 = distancia_entrada();
  dist2 = distancia_salida();

  //Esto es solo prueba, borrar después
  Serial.print(dist1);
  Serial.print("       ");
  Serial.println(dist2);
  
  //Caso inicial: se detecta un carro a la entrada y se abre la aguja
  if(3 < dist1 < 10){
    aguja.write(90);
    carFlag = true;
  }  

  //Caso ambos sensores detectando, el carro está pasando por la aguja
  else if (3 < dist1 < 10 && 3 < dist2 < 10 && carFlag == true)
  {
    aguja.write(90);
  }

  //Caso solo se detecta el carro con el sensor de la salida
  //espera un momento y empieza a bajar la aguja según las indicaciones del enunciado
  else if (dist1 < 10 && 3 < dist2 < 10 && carFlag == true)
  {
    aguja.write(45);
    for (int i = 45; i > 0 ; i--)
    {
      aguja.write(i);
    } 
    carFlag = false;
  }    
    
}







/***********Funciones para medir la distancia con los sensores ultrasónicos HC-SR05***********/

float distancia_entrada(){
  //Generación del pulso para medir la distancia 
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,  HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);

 // Lectura del tiempo que dura el pulso en volver al sensor
  duracion1 = pulseIn(echo1, HIGH);

  //Conversión del tiempo a distancia
  distancia1 = duracion1/29.2/2;

  //Devuelve la distancia medida
  return distancia1;  
}


float distancia_salida(){

  //Generación del pulso para medir la distancia 
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,  HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  // Lectura del tiempo que dura el pulso en volver al sensor
  duracion2 = pulseIn(echo2, HIGH);

  //Conversión del tiempo a distancia
  distancia2 = duracion2/29.2/2;

  //Devuelve la distancia medida
  return distancia2;
}




/*
Referencias:
https://projecthub.arduino.cc/Nicholas_N/distance-measurement-with-an-ultrasonic-sensor-hy-srf05-bf2923
https://www.arduino.cc/reference/es/language/functions/advanced-io/pulsein/

*/
