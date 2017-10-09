/*
Example of using millis to get two LEDs blink at different interval and on time
We are not using any delays, so the code will run at full speed all the time.
The error handeling will use delay, but when input is error free, that will not be used.
*/

// Define the pins used for red and greed LED
#define redled D3
#define greenled D4

// Set the time between each blink
// Interval for Red is 0,5 second
// Interval for Green is 2 seconds
int redinterval = 500;
int greeninterval = 2000;

// For how long do you want the LED to stay on
// Must always be less or equal to interval.....
// Red will stay on for 0,5 second
// Green will stay on for 1 second
int redtime = 500;
int greentime = 1000;

// Declare variable to hold current millis
int redgetmillis;
int greengetmillis;

// Declare variabel to hold the status of each LED
boolean redon = false;
boolean greenon = false;

void setup() {
  // Define the pinmode to give output 3,3v when set to HIGH
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);

  // Be sure both are in status LOW
  digitalWrite(redled, LOW);
  digitalWrite(greenled, LOW);

  // initialize the millis counter
  redgetmillis = millis();
  greengetmillis = millis();
}

void loop() {
  // For the fun of it, lets first make an simple error handeling for blink time set longer than the interval...
  // Let the LED blink fast in an endless loop if blink time is higher than the interval
  // In this example code must be fixed and uploaded again, to correct the problem.
  // If other input is used during runtime, like serial input or a potentiometer, the code would continue when timing has been adjusted
  // Perhaps I will make an example later, how to adjust the interval and blink time, during runtime.....
  while (redinterval < redtime){
   digitalWrite(redled, HIGH);
   delay(100);
   digitalWrite(redled, LOW);
   delay(100);
  }
  while (greeninterval < greentime){
   digitalWrite(greenled, HIGH);
   delay(100);
   digitalWrite(greenled, LOW);
   delay(100);
  }

  // First we handle the red LED
  // Check if red is going to be set HIGH
  // Check if current millis ( millis() ) - redgetmillis is higher than the interval and that the red LED is off
  if ( (millis() - redgetmillis) > redinterval and redon == false ) {
    digitalWrite(redled, HIGH);
    // Let the code know red is set to HIGH
    redon = true;
  }
  // Check if red is going to be set LOW
  // Check if current millis ( millis() ) - redgetmillis + redtime is higher than the interval and that the red LED is on
  if ( (millis() - redgetmillis) > (redinterval + redtime) and redon == true ) {
    digitalWrite(redled, LOW);
    redon = false;
    // We now know the on/off has been done for the red LED, and we can reset the counter, to start over again
    redgetmillis = millis();
  }

  // Then we handle the green LED
  // Same as for the red one
  if ( (millis() - greengetmillis) > greeninterval and greenon == false ) {
    digitalWrite(greenled, HIGH);
    greenon = true;
  }
  if ( (millis() - greengetmillis) > (greeninterval + greentime) and greenon == true ) {
    digitalWrite(greenled, LOW);
    greenon = false;
    greengetmillis = millis();
  }

// End of loop, start over
}

