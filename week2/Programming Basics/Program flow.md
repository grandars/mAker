# Program flow

All essays have a beginning, a middle and an end. Arduino programs have a `setup()` and a `loop()`. When the program starts, it will run `setup()` once, and then `loop()` until someone unplugs it.

## The Setup

```
void setup() {
    pinMode(D6, OUTPUT);
    pinMOde(A0, INPUT);
    
    Serial.begin(115200);
}
```

Above is a typical `setup()` function. It tells the board to prepare D6 for output (going HIGH or LOW), and A0 (the only analog pin) to prepare to detect the input voltage. It also uses the built-in `Serial`-library to open a serial connection back to the PC at 115200 baud (that's the typing speed of the connection). More on serial connections later.

## The Loop

Once the `setup()` function is complete, the board will execute the `loop()` function. This will continue for as long as the board has power. (Or until the code crashes or hangs)

## The Exceptions

It is common to do some things before the `setup()` function. Any value declared outside the function will become global. This is very useful if you want a variable to be used both in the `setup()`, `loop()` and any other functions you create.

It is also common practice to do any library linking outside, and before the `setup()` function. We're going to include some libraries later.

Lastly, compiler definitions are also outside, and before any other functions. These are nothing more than shortcuts for typing. If you find that you use the same value over and over throughout your code, you should `define` it. Then there is only one place to change it, if that's needed.

# Example

A typical program layout for Arduino would look something like this:

```
#include <library.h> 
#define LEDPIN D6

int blinkCount = 0;

void setup() {
    pinMode(LEDPIN, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    digitalWrite(LEDPIN, HIGH);
    blinkCount = blinkCount + 1;
    
    Serial.print("Led has blinked: ");
    Serial.print(blinkCount);
    Serial.println(" times");
    
    delay(1000);
    digitalWrite(LEDPIN, LOW);
    delay(1000);
}
```
