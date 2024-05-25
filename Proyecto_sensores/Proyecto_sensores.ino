#include <Servo.h>

const int trig1 = 2;
const int echo1 = 3;   

int tiempo1;
int distancia1;
int trig2 = 4;
int echo2 = 5;
float tiempo2;
float distancia2;

int ledVerde = 8;
int ledRojo = 7;
int servoPin = 9;

Servo servo;
int servoPosInicial = 0;
int servoPosAbierta = 90;
int servoPosIntermedia = 45;

enum Estado {
  INICIAL, 
  DETECTANDO_OBJETO1, 
  CERRANDO
};

Estado estadoActual = INICIAL;

void setup() {
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  digitalWrite(echo1, LOW);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  servo.attach(servoPin);
  servo.write(servoPosInicial);
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledVerde, LOW);
  Serial.println("Estado: Reposo - LED Rojo encendido, LED Verde apagado, Servo en posición inicial");
}

void loop() {
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  tiempo1 = pulseIn(echo1, HIGH);
  distancia1 = tiempo1/59;

  Serial.print("Distancia: ");
  Serial.print(distancia1);
  Serial.print(" cm");
  delay(100);

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,  HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  // Lectura del tiempo que dura el pulso en volver al sensor
  tiempo2 = pulseIn(echo2, HIGH);
  //uSerial.println(duracion2);
  //Conversión del tiempo a distancia
  distancia2 = tiempo2/59;

  Serial.print("     ");
  Serial.print("Distancia2: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  delay(100);

 unsigned long tiempoInicio = 0;

  switch (estadoActual) {
    case INICIAL:
     digitalWrite(ledRojo, HIGH);
        digitalWrite(ledVerde, LOW);
        if (distancia1 < 10) { // Distancia de deteccion
          servo.write(servoPosAbierta);
          digitalWrite(ledRojo, LOW);
          digitalWrite(ledVerde, HIGH);
          Serial.println("Estado: Abierto - LED Verde encendido, LED Rojo apagado, Servo abierto");
          estadoActual = DETECTANDO_OBJETO1;
          tiempoInicio = millis(); // Tiempo de inicio
        }
        break;

    case DETECTANDO_OBJETO1:
        if (distancia2 < 10 && distancia1 > 10 ) { // Ha pasado 20 segundos o detecta objeto en el sensor 2
          Serial.println("Estado: Cerrando - LED Verde apagado, LED Rojo encendido, Cerrando servo");
          estadoActual = CERRANDO;
          tiempoInicio = 0;
        }
        break;

    case CERRANDO:
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);

        // Movimiento del servo de 90 a 45 grados rápidamente
        servo.write(45);
          

        // Movimiento del servo de 45 a 0 grados lentamente
        for (int pos = servoPosIntermedia; pos >= servoPosInicial; pos--) {
          servo.write(pos);
          delay(30); // Ajuste de velocidad
        }

        servo.write(servoPosInicial);
        Serial.println("Estado: Reposo - LED Rojo encendido, LED Verde apagado, Servo en posición inicial");
        estadoActual = INICIAL; 
        break;
  }

  delay(100);
}
