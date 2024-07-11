#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define direccion_lcd 0x27     
#define filas 2                
#define columnas 16 

#define sensor_hall 3

LiquidCrystal_I2C lcdEduardo(direccion_lcd, columnas, filas);

int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;
int demora = 20;

int pt;

int paso [8][4] =
{
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

bool state_sensor;

void setup() {
  lcdEduardo.init();
  lcdEduardo.backlight();
  lcdEduardo.print("Uso sensor de efecto hall");
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(sensor_hall, INPUT); 
}

void loop() {
  pt = map(analogRead(A6),7, 4000, 1, 35);
  for (int i = 0; i < 8; i++)
    {
      digitalWrite(in1, paso[i][0]);
      digitalWrite(in2, paso[i][1]);
      digitalWrite(in3, paso[i][2]);
      digitalWrite(in4, paso[i][3]);
      delay(pt);
    }
    lcdEduardo.clear();
    lcdEduardo.setCursor(0,0);
    lcdEduardo.print("Revs.xseg");

    state_sensor = digitalRead(sensor_hall);                      
  if(state_sensor == LOW)
  {
    Serial.println("El eje del motor ha pasado por el sensor");
    delay(10);
  }
}
