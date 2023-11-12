#include <SoftwareSerial.h>
#include <RCSwitch.h>

SoftwareSerial gsmSerial(3, 2);
RCSwitch mySwitch = RCSwitch();

String responseData; 
int led_pin = 13;

void setup() {

  pinMode(13, OUTPUT);

  responseData.reserve(200);

  mySwitch.enableTransmit(10);
  mySwitch.setProtocol(8);
  mySwitch.setRepeatTransmit(5);

  Serial.begin(9600);
  gsmSerial.begin(9600);
  delay(2000);
}

void loop() {
  while(gsmSerial.available()) {
//    digitalWrite(led_pin, HIGH);
    responseData = gsmSerial.readStringUntil('\n');
    Serial.println(responseData);
    parse();
//    delay(10);
//    digitalWrite(led_pin, LOW);
  }
}

void parse() {
  if (responseData.indexOf("CLIP:") > 0) {
    delay(1000);
    gsmSerial.write("ATH\r");
    for (int i = 0; i < 5; i++) {
      mySwitch.send("1000001011000001100000111011100000001110011111100111");
      delay(1000);
    }
  }
}
