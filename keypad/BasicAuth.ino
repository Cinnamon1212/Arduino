#include <Keypad.h>
char passcode[8] = {'8','8','8','8','8','8','8','8'};
char userPasscode[8];
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'B'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
int LEDPin = 10, i;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}

int checkPasscode(){
  for(i = 0; i < 8; i ++){
    if(passcode[i] != userPasscode[i]){
      Serial.println("here 1");
      return 1;  
    }
  
  }
  Serial.println("here 2");
  return 0;
}
  
void loop(){
  for(i = 0; i < 8; i++){
    while(!userPasscode[i]){
      userPasscode[i] = keypad.getKey();
      if(userPasscode[i]){
        Serial.println(userPasscode[i]);
      }
    }
  }
  if(checkPasscode() == 0){
    digitalWrite(LEDPin, HIGH);
    delay(5000);
    digitalWrite(LEDPin, LOW);
  }
}

