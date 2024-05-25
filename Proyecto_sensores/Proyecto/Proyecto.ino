#include <Servo.h>
#include <NewPing.h>

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
Servo aguja;
bool carFlag = false;
float dist1;
float dist2;


NewPing sonar[SONAR_NUM] = {   
  NewPing(11, 12, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(5, 4, MAX_DISTANCE),
};

void setup() {
  Serial.begin(9600);
  aguja.attach(9);
  aguja.write(0);
  delay(1000);
}

void loop() {

  //La aguja inicia desde la posición inicial
  aguja.write(0);

  //Se leen los sensores
  dist1 = sonar[1].ping_cm();
  dist2 = sonar[2].ping_cm();

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