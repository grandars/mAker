#include <Servo.h>
Servo myservo;

const byte green = 5;
const byte yellow = 4;
const byte red = 0;
  
// Show only green
int Step1 = 5000;

// Show only yellow
int Step2 = 2000;

// Show Only Red
int Step3 = 5000;

// Show Red and Yellow
int Step4 = 2000;

boolean Step1Trigg;
boolean Step2Trigg;
boolean Step3Trigg;
boolean Step4Trigg;

int Step;
int LastStep1Time;

int Step1Start;
int Step1Stop;
int Step2Start;
int Step2Stop;
int Step3Start;
int Step3Stop;
int Step4Start;
int Step4Stop;
int pos;

unsigned long CheckMillis;
unsigned long CheckMillisServo;
int currstatus = 1;

const byte interruptPin = 14;
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;

volatile byte servostatus = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Initializing Traffic Lights");
  delay(1000);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  myservo.attach(15);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);

  CheckMillis = millis();
  CheckMillisServo = millis();
}

void handleInterrupt() {
  interruptCounter++;
}

void startservo(int pos) {
   myservo.write(pos);
   Serial.println(pos);
}


void loop() {

if ( millis() - CheckMillisServo >= 5000 ){

  if (servostatus == 0) {
    startservo(0);
    servostatus = 1;
  } else {
    startservo(180);
    servostatus = 0;
  }
  
  CheckMillisServo = millis();
}


if(interruptCounter>0){
  interruptCounter--;
  numberOfInterrupts++;
      
  Serial.print("An interrupt has occurred. Total: ");
  Serial.println(numberOfInterrupts);
}



Step1Start = CheckMillis;
Step1Stop = CheckMillis + Step1;
if (millis() >= Step1Start and millis() < Step1Stop ) { Step1Trigg = true; Step = 1; } else {Step1Trigg = false;}

Step2Start = CheckMillis + Step1;
Step2Stop = CheckMillis + Step1  + Step2;
if (millis() >= Step2Start and millis() < Step2Stop ) { Step2Trigg = true; Step = 2; } else {Step2Trigg = false;}

Step3Start = CheckMillis + Step1 + Step2;
Step3Stop = CheckMillis + Step1 + Step2 + Step3;
if (millis() >= Step3Start and millis() < Step3Stop ) { Step3Trigg = true; Step = 3; } else {Step3Trigg = false;}

Step4Start = CheckMillis + Step1 + Step2 + Step3;
Step4Stop = CheckMillis + Step1 + Step2 + Step3 + Step4;
if (millis() >= Step4Start and millis() < Step4Stop ) { Step4Trigg = true; Step = 4; } else {Step4Trigg = false;}

  // Start Step 1 - Show Green
  if ( Step1Trigg == true )  {
    if (digitalRead(green) == LOW) {
      Serial.println("Green On");
      digitalWrite(green, HIGH);
    }
  } else if ( Step1Trigg == false )  {
    if (digitalRead(green) == HIGH) { 
      Serial.println("Green Off");
      digitalWrite(green, LOW);
    }
  }

  // Start Step 2/4 - Show Yellow
  if ( Step2Trigg == true or Step4Trigg == true )  {
    if (digitalRead(yellow) == LOW) {
      Serial.println("Yellow On");
      digitalWrite(yellow, HIGH);
    }
  } else if ( Step2Trigg != true )  {
    if (digitalRead(yellow) == HIGH) { 
      Serial.println("Yellow Off");
      digitalWrite(yellow, LOW);
    }
  } else if (Step4Trigg != true )  {
    if (digitalRead(yellow) == HIGH) { 
      Serial.println("Yellow Off");
      digitalWrite(yellow, LOW);
    }
  }

  // Start Step 3/4 - Show Red
  if ( Step3Trigg == true or Step4Trigg == true )  {
    if (digitalRead(red) == LOW) {
      Serial.println("Red On");
      digitalWrite(red, HIGH);
    }
  } else if ( Step3Trigg != true )  {
    if (digitalRead(red) == HIGH) { 
      Serial.println("Red Off");
      digitalWrite(red, LOW);
    }
  } else if ( Step4Trigg != true )  {
    if (digitalRead(red) == HIGH) { 
      Serial.println("Red Off");
      digitalWrite(red, LOW);
    }
  }
  
  // Reset and start over
  if ( (millis() - CheckMillis) >= ( Step1 + Step2 + Step3 + Step4 ) ) {
    Serial.println("Reset");
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    CheckMillis = millis();
  }

}
