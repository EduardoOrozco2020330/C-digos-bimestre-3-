/*Eduardo Sebastian Orozco Colop 2020330
EB5AM*/

#include <Wire.h>
#include <SparkFun_ADXL345.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(12, 13); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
ADXL345 acelerometro_ADXL345;

const int numLeds = 10;
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int mercalli[] = {50, 60, 75, 90, 105, 120, 135, 150, 175, 190}; // Valores de magnitud para la escala Mercalli

void setup() {
  Serial.begin(9600);
  Serial.println("Uso del acelerometro ADXL345");

   mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  acelerometro_ADXL345.powerOn();
  acelerometro_ADXL345.setRangeSetting(16);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); 
  }
}

void loop() {
  int x, y, z;
  acelerometro_ADXL345.readAccel(&x, &y, &z);

  float magnitud = sqrt(x * x + y * y + z * z);

  int intensidad = 0;
  for (int i = 0; i < numLeds; i++) {
    if (magnitud < mercalli[i]) {
      intensidad = i;
      break;
    }
    
 }

  Serial.print("Intensidad Mercalli: ");
  Serial.println(intensidad);
  
  for (int i = 0; i <= intensidad; i++) {
    digitalWrite(ledPins[i], HIGH);
    if (intensidad >= 5) {
       myDFPlayer.play(1);
       delay(6000);      
    }
  }

  for (int i = intensidad + 1; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  delay(100);
}
}
