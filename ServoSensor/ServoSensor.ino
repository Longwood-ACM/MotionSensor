/*void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
}
*/
/*
 * PIR sensor tester
 */

#include<Stepper.h>

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = LOW;                  // variable for reading the pin status
int lastTenMinutes = 0;         // Whether or not the sensor has gone off in the past ten minutes

#define STEPS 32

Stepper stepper(STEPS, 8, 10, 9, 11);
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
  stepper.setSpeed(1000);
}
 
void loop(){
	if(lastTenMinutes % 600 == 0){
		lastTenMinutes = 0;
		val = digitalRead(inputPin);// read input value
		if(Serial.available() > 0 && val == LOW){
			while(Serial.available() > 0){
				char inByte = Serial.read();
				if(inByte == '1'){
					val = HIGH;
				}
			}
		}

		if (val == HIGH) {            // check if the input is HIGH
			digitalWrite(ledPin, HIGH);  // turn LED ON
			if (pirState == LOW){
				// we have just turned on
				stepper.step(1500);     //Turn servo about half rotation clockwise
				stepper.step(-1500);    //Turn servo about half rotation counter clockwise
				Serial.println("Motion detected!");
				// We only want to print on the output change, not state
				pirState = HIGH;
			}
		} else {
			digitalWrite(ledPin, LOW); // turn LED OFF
			if (pirState == HIGH){
				// we have just turned of
				Serial.println("Motion ended!");
				// We only want to print on the output change, not state
				pirState = LOW;
			}
		}
	}
	val = LOW;
	delay(1000);
	lastTenMinutes += 1;
}
