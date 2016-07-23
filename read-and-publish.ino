#include <math.h>

int tempsensor = A0; 

void setup() {
  pinMode(tempsensor,INPUT);
  Particle.function("temp", getTemp);
}

int convertTemp(int i) {
  float voltage =  i * (3300 / 1024);
  int temperatureC = floor((voltage - 500) / 100);
  return temperatureC;
}

int getTemp(String command) {
  int celcius = convertTemp(analogRead(tempsensor));
  return celcius;
}

void loop() {

  String strTemp = String(getTemp(""));

  Particle.publish("temperature", strTemp, 60, PRIVATE);
  delay(20 * 1000);
}
