/*
  This example will blink the onboard LED on for one second, off for one.
*/


// The setup() function is ran once when the board is powered on

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // LED_BUILTIN is a hardcoded pin on the board
}

// The loop() function will run forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // The LED turns ON when the voltage on the pin goes LOW
  delay(1000);                      // Wait for 1000 milliseconds
  digitalWrite(LED_BUILTIN, HIGH);  // When the pin goes HIGH, the LED turns off
  delay(1000);                      // Wait for one second
}									// This closes the loop() function, and it starts over