  const byte green = 5;
  const byte yellow = 4;
  const byte red = 0;

  int yellowtime = 2000;
  int greentime = 10000;
  int redtime = 5000;

void setup() {

  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
}

void loop() {
  digitalWrite(red, HIGH); 
  delay(redtime);             
  digitalWrite(yellow, HIGH);
  delay(yellowtime);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  
  
  digitalWrite(green, HIGH);
  delay(greentime);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(yellowtime);
  digitalWrite(yellow, LOW);


}
