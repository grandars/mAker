/* This example will use PWM to fade a LED up and down in an endless loop
 * PWM (Puls Width Modulation) "emulate" voltage control, in this case between 0 and 3,3v
 * The range is from 0 (0v) to 255 (3,3v) 
 * PWM is usfull for dimming lights, controlling speed of motors (DC) and controlling servos 
*/

// Define the pin used for LED
#define ledpin D3

// General counter
int i = 0;

// Fade speed, lower value is faster fade speed
int fadespeed = 10;

// Fade Step, low value = smooth fade
int fadestep = 1;

// We start with going from zero and up
boolean up = true;

void setup() {
  // Prepare ledpin (D3) for out signal
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // Check if we need to go up or down
  // We need to check for equal OR greater
  // If we step by 3, the last legal value will be 255, and the next value would have been 258
  // If we had used if ( i == 256 ), this would have been an endless loop.
  if ( i >= 256 ) {
    up = false;
  } else if ( i <= 0 ) {
    up = true;
  }

  if ( up == true ){
    i++; // i++ is the same as i = i + 1
    i = i + fadestep;
  } else {
    i--; // i-- is the same as i = i - 1
    i = i - fadestep;
  }
  delay(fadespeed);
  analogWrite(ledpin, i);
}

