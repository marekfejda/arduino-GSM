#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); 

void setup()
{
  Serial.begin(9600);
  
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); 
  updateSerial();
  
  mySerial.println("ATD+ +421944403014;"); 
  updateSerial();
  delay(20000); 
  mySerial.println("ATH"); 
  updateSerial();
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}
