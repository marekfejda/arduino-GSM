#include <SoftwareSerial.h>
SoftwareSerial sim800(3, 2);

void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  Serial.println("Initializing SIM800L...");
  sim800.println("AT+CSQ");
}

void loop() {
  delay(500);
  while (sim800.available()) {
    Serial.write(sim800.read());
    if (sim800.read() == "OK") {
      Serial.println("HOVNOOOOOO");
    }
  }


  while (Serial.available()) {
    sim800.write(Serial.read());
  }
}
