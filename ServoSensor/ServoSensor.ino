#include<Stepper.h>

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int val = LOW;                  // variable for reading the pin status

#define STEPS 32

Stepper stepper(STEPS, 8, 10, 9, 11);

bool readIn(){
  bool rv = digitalRead(inputPin);
  if(Serial.available() > 0){
    while(Serial.available() > 0){
        char inByte = Serial.read();
        Serial.println(inByte);
        if(inByte == '1'){
          rv = HIGH;
        }
     }
  }
  return rv;
}

void gobble(){
  if(Serial.available() > 0){
    while(Serial.available() > 0){
      char sbyte = Serial.read();
    }
  }
}

void activate(){
  digitalWrite(ledPin, HIGH);
  stepper.step(1500);     //Turn servo about half rotation clockwise
  stepper.step(-1500);    //Turn servo about half rotation counter clockwise
  delay(600000);
  digitalWrite(ledPin, LOW);
  gobble();
}


void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
  stepper.setSpeed(1000);
}

void loop(){
  val = readIn();
  if(val == HIGH){
    activate();
    val = LOW;
  }
  delay(1000);
}

