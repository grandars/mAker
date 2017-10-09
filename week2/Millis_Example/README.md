# Millis

When writing Arduino/ESP8266 code we often use the `delay()` function for timing. This is convenient and simple, but very limiting. As the program runs, and encounters a `delay()` it will sit and do nothing until the set amount of milliseconds has expired.

When the code does nothing, it will not react to anything. Button presses will not register, sensors will not be read and outputs will not be updated. To get around this we use `millis()`.

To use `millis()`, simply pass its result to a variable like this:

```
int a;

a = millis();
```


When the board is first powered up it automatically starts counting milliseconds. This count is stored in the `
millis()` function. It will (almost) always be increasing by 1 every millisecond until the board is reset or loses power.

Consider the following example:

```
void loop() {
    digitalWrite(D6, HIGH);
    delay(1000);
    digitalWrite(D6, LOW);
    delay(1000)
}
```

It will switch the D6 pin to HIGH (3.3V) and *do nothing* for one second, then it will switch D6 to LOW, and again *do nothing* for 1000 milliseconds.

Instead we could write the same function like this:

```
int lastToggle = 0;
bool pinIsHigh = false;

void setup() {
    pinMode(D6, OUTPUT);
}

void loop() {
    if (millis() - lastToggle >= 1000 && !pinIsHigh) {
        digitalWrite(D6, HIGH);
        pinIsHigh = true;
        lastToggle = millis();
    }
    if (millis() - lastToggle >= 1000 && pinIsHigh) {
       digitalWrite(D6, LOW);
       pinIsHigh = false;
       lastToggle = millis();
    }
}
```

Yes. This is more complex. But the board will be able to be doing other things as well. In "real" programs we would not have all this inside the `loop()` function. Instead it would be its own function, and all we would do from inside `loop()` was to say which pin would do the blinking, and how fast.

To see a good example of this, wire your board like this:

![Wiring example](Millis_Example/Wiring.png)

Then take a look at [this example](Millis_Example/Millis_Example.ino) code.
