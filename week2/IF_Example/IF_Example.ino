/*
Simple IF, ELSE IF, ELSE example.
We make a counter that counts from 0 - 5000, and loop 5000 times before the main loop continues, and the counter starts from 0 again
As you can see it is very important to use indents in loops and IF to be able to read the code
*/

// Define the pins used for red and greed LED
#define yellowled D3
#define greenled D4
#define redled D5

// Declare general counter
int i;

// Declare counter to cont number of main loops
int x = 1;

void setup() {
  Serial.begin(115200);
  // Prepare led pins (D3, D4, D5) for out signal
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(yellowled, OUTPUT);

  // Set all led pins to low
  digitalWrite(redled, LOW);
  digitalWrite(greenled, LOW);
  digitalWrite(yellowled, LOW); 
}

// Start the main loop, runs forever
void loop() {

// The "for" line below contain three steps, devided by ;
// 1 set variable i to 0
// 2 do the for loop while i is less or equal to 5000
// 3 for each loop, increase i with 1
// It will loop until i = 5000
for (i=0;i<=5000;i++){
  // if i is greater than 1000 and less than 2000, the first line will kick inn and green is set to high, and the rest to low
  if ( i >= 1000 and i < 2000 ){
    // It is no problem with IFs within IFs but try to limit it to max three, or it is very easy to get lost in the code.
    // Let us make some IFs to check if the green led pin is already high, and the rest is low so that we only set green to high if it is low, and the rest low if they are high
    if ( digitalRead(greenled) == LOW ){
      digitalWrite(greenled, HIGH);
    }
     if ( digitalRead(yellowled) == HIGH ){
      digitalWrite(yellowled, LOW);
    }   
     if ( digitalRead(redled) == HIGH ){
      digitalWrite(redled, LOW);
    }  
  // if first statement is false, it will see if i is greater than 2000 and less than 3000, if true, yellow is set to high, and the rest to low
  } else if ( i >= 2000 and i < 3000 ){
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);
    digitalWrite(yellowled, HIGH);
  // if first and second statement is false, it will see if i is greater than 3000 and less than 4000, if true, all is set to high
  } else if ( i >= 3000 and i < 4000 ){
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, HIGH);
    digitalWrite(yellowled, HIGH);
  // if all statements above is false, red is set to high, and the rest to low
  // this willl ocure 
  } else {
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
    digitalWrite(yellowled, LOW ); 
  }
  // Take a small break since counting from 0 - 5000 is done faster than the blink of the eye
  delay(3);
  
}
Serial.println("");
Serial.println("The FOR loop is done, continue with the next main loop where i = 0 again");
Serial.println("This is loop number " + String(x) + " for the main loop");
Serial.println("");

// Increase the main loop counter by one
x++;
delay(1000);




// End of loop, start over
}




