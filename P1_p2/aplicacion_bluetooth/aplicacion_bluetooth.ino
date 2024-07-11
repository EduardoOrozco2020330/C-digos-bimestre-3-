#include <SoftwareSerial.h>
SoftwareSerial BT1(10,11);

void setup() {
  Serial.begin(9600);
  Serial.println("Conectado");
  BT1.begin(38400);
}

void loop() {
  if(BT1.available()) {
    Serial.write(BT1.read()); 
  }

  if(Serial.available()){
    BT1.write(Serial.read());
  }
}
