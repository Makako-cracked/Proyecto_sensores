int led = 9;
int sw = 2;
int pot;
int mapeo;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);
  Serial.begin(9600);

}

void loop() {
  
  while (digitalRead(sw) == 1){
    for (int i = 0; i < 255; i++)
    {
      analogWrite(led, i);
      delay(5);
    }
    for (int i = 255; i > 0 ; i--)
    {
      analogWrite(led, i);
      delay(5);
    }
  }

  while (digitalRead(sw) == 0){
    pot = analogRead(A4);
    mapeo = map(pot, 0, 1023, 0, 255);
    Serial.println(mapeo);
    analogWrite(led, mapeo);
    delay(10);
  }
}
