#include <EEPROM.h>

#define RELAY_PIN 7
#define RELAY_ADDR 0

byte relayVal = 0;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.begin(115200); // open serial
  
  relayVal = EEPROM.read(RELAY_ADDR);
  relayVal = relayVal & 0x01; // mask with 0x01 so that it only has 0 or 1
  
  if (relayVal) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Start with relay on...");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Start with relay off...");
  }
}

void loop()
{
  int cmd;

  while (Serial.available() > 0) {
    cmd = Serial.read();
    
    switch (cmd) {
    case '1':
      relayVal = 1;
      digitalWrite(RELAY_PIN, HIGH);
      EEPROM.write(RELAY_ADDR, relayVal);
      Serial.println("Relay on");
      break;
      
    case '0':
      relayVal = 0;
      digitalWrite(RELAY_PIN, LOW);
      EEPROM.write(RELAY_ADDR, relayVal);
      Serial.println("Relay off");      
      break;
      
    case 's':
      Serial.println(relayVal);
      break;
      
    default:
      if (cmd != '\n')
        Serial.println("HELP: type 1 for relay on / 0 for relay off / s for status");
      break;
    }
  }
}
