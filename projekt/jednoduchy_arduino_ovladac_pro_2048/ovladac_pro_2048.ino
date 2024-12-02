#include <BleCombo.h>
unsigned long previousMillis = 0;
const long interval = 200;

void setup() {
  // put your setup code here, to run once:
Keyboard.begin();
}

void loop() {
Serial.begin(115200); 
unsigned long currentMillis = millis();
  int right = digitalRead(12);
  int left = digitalRead(13);
  int up = digitalRead(18);
  int down = digitalRead(23);
  int save = digitalRead(19);
  if(Keyboard.isConnected() != true) {
    Serial.print(".");
    }

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;
    if(right == 1){
      Keyboard.write(KEY_RIGHT_ARROW);
      Serial.print("R\n");
      }
    if(left == 1){
      Keyboard.write(KEY_LEFT_ARROW);
      Serial.print("L\n");
      }
    if(up == 1){
      Keyboard.write(KEY_UP_ARROW);
      Serial.print("U\n");
      }
    if(down == 1){
      Keyboard.write(KEY_DOWN_ARROW);
      Serial.print("D\n");
      }
     if(save == 1){
      Keyboard.print("s");
      Serial.print("S\n");
      }
    }
    }
