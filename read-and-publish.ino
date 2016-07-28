#include <math.h>

int tempsensor = A0; 

void setup() {
  pinMode(tempsensor,INPUT);
  Particle.function("temp", getTemp);
}

int convertTemp(int i) {
  float voltage =  i * (3300.0 / 1024.0);
  int temperatureC = ceil((voltage - 500.0) / 100.0);
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
