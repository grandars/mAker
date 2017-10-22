
#define ledPin       D7
#define interruptPin D1

// Volatile is used since interrput will be handled in ISR (Interrupt Service Routines)
// To make sure variables are shared correctly between ISR function and the main loop, we need to declare them as volatile
// only ledstate and interruptCounter are shared between main loop and ISR, and need to be volatile
// For Arduino, handling variables with interrupts, is the only time volatie is needed
// If you want more information regarding volatie, Google it ;-)
volatile int interruptCounter = 0;
volatile int ledstate = LOW;

// Pressing a button can cause strange behavior, due to mechanical/electrical issues, and the facts that the code runs extremely fast.
// So we will handle the button press, to be sure it is only pressed once within a very short timeframe.
// This is critical for a robust code, when using buttons.
// We will use millis() to test if the button change state within a few milli seconds, which in almost all cases is not
// anything that should be possible.
unsigned long lastdebounce = 0;

// We are not using button in this example, so we need very high debouncedelay to get time to get the wires back.
// If using push button, try with value around 50/100ms
unsigned long debouncedelay = 3000;

// numOfInterrupts is used in the main loop and does not need to be volatile
int numOfInterrupts = 0;

void setup() {
  // Start serial, for output to Serial monitor (or any program that can read/write serial communication for example putty)
  // Remember to set the baudrate (communication speed) for ESP8266 this is 115200
  Serial.begin(115200);
  // Print a emptyline with lineshift
  // Serial.print will print each new value on the same line.
  // Serial.println will print new line (carriage return and newline) after the value.
  Serial.println("");
  // Print "welcome text"
  Serial.println("Ready for mAker Interrupt example");

  // Prepare pin for output mode (3,3v).
  pinMode(ledPin, OUTPUT);

  // We start with Pin HIGH. This way it will go LOW when button is pressed down, and HIGH again when you release it
  // Interrupt will listne for the pin to go from LOW to HIGH
  pinMode(interruptPin, INPUT_PULLUP);

  // attachInterrupt(digitalPinToInterrupt(which pin to monitor), function to run, RISE, FALLING or CHANGE)
  // In this example we will toggle a led when the pin state changes from LOW to HIGH ie rising
  // This will result in in a button that will not trigger when you push it down, but when you release it.
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, RISING);
}

// This is the function that will be trigged by RISING
void handleInterrupt() {
  // If any new interrupt is happening within time of debouncedelay, we ignore it
  if ( millis() - lastdebounce >= debouncedelay ){ // Comment out this line to see the problem if we dont handle this
    // add 1 to interruptCounter. This will cause the IF in the mainloop to trigger
    interruptCounter++;
    // set the ledstate to the NOT LIKE current state ie if it is LOW (0) set it to HIGH (1) and vice versa
    ledstate = !ledstate;
    // Reset the lastdebounce to current time
  lastdebounce = millis();           // Comment out this line to see the problem if we dont handle this
  }                                  // Comment out this line to see the problem if we dont handle this
}

void loop() {
  // In the handleInterrupt function interruptCounter has been increased by 1, and IF below will trigger
  if(interruptCounter > 0){
    // We now set interruptCounter to 0 again
    interruptCounter--;
    // Add 1 to numOfInterrupts, to keep track of how many interrupts has occurred.
    numOfInterrupts++;

    // Write HIGH or LOW to the LED pin
    digitalWrite(ledPin, ledstate);

    // Print info to serial monitor
    Serial.print("An interrupt has occurred. Total: ");
    Serial.println(numOfInterrupts);
  }
}

