/*gsmSerial.write("AT\r");// because of SIM800L autobounding mode
  gsmSerial.println("AT");// because of SIM800L autobounding mode
 */

#include <SoftwareSerial.h>

const int output_pin = 13;
bool output_pin_status = 0;

SoftwareSerial gsmSerial(3, 2);

String responseData;
String senderNumber;

void setup() {
  responseData.reserve(200);
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, LOW);
  Serial.begin(9600);
  gsmSerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  gsmSerial.println("AT");
  delay(500);
  gsmSerial.println("AT+CLIP=1");
  delay(500);
  gsmSerial.println("AT+CSQ");
  delay(500);
}

void loop() {
  if (gsmSerial.available() > 0) {
    responseData = gsmSerial.readStringUntil('\n');
    Serial.println(responseData);
    parse();
    delay(1000);
  }
}

void parse() {
  if (responseData.indexOf("CLIP:") > 0) {
    senderNumber = responseData.substring(responseData.indexOf("+CLIP: ") + 8, responseData.indexOf("+CLIP: ") + 21); //PARSE CALLER ID
    Serial.print("Caller number   :");
    Serial.println(senderNumber);
    output_pin_status = !output_pin_status;
    digitalWrite(output_pin, output_pin_status);
    Serial.print("Ledioda je: ");
    Serial.println(output_pin_status);
    delay(500);
    gsmSerial.write("ATH\r");  // ZRUS HOVOR
  }
}
