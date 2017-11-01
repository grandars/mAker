/*
 *  Serial input can be quite difficult, and have endless posibillities to make your hair gray ;-)
 *  We will only read one single character between 1 - 9 and multiply that by 1000000 to get number to count in the while loop
 *  Even that can be cumbersome as the value you get is in HEX, so 0 = 48, 1 = 49 etc. So to get the actuall value we will make it int and subtract 48
 *  from each value so 1 = HEX value 49 - 48, 2 = HEX value 50 - 48, etc...
 *  Also remember to set serial input window to no line ending, if not, each time you press enter, you will get one or two extra characters (NL or/and CR)
 *  
 *  This code does not have any handeling of wrong input from user....
 *  
 *  There are three while loops in this code
 *  1. looping as long as Serial is available
 *  2. A simple progressbar with text
 *  3. A loop which counts the input * 100000
 *  
 *  switch is used in the progressbar, switch is similar to IF, and used her as an example of the usage
*/

char FromSerialInput;
int getNumberToCount;
long start;
long counttime;
int x = 0;
int i = 0;
float sec;

void setup() {
 Serial.begin(115200);
 Serial.println("");
 Serial.println("Ready for While and Serial input example");
 Serial.println("Type in a number 1 - 9 and hit enter");
 Serial.println("The number will be multiplied by 1000000");
 Serial.println("Typing 5 will result in counting from 0 to 5000000 (five millions)");
}

void loop() {

while(Serial.available()){
  FromSerialInput = Serial.read();
  getNumberToCount = (int(FromSerialInput)-48) * 1000000;

  Serial.println("");
  Serial.println("");
  Serial.println("I'm ready to count from 0 to " + String(getNumberToCount) );
  Serial.println("I will start after the countdown, be prepared, this is going to go fast..");
  delay(5000);
  while (i <= 3000) {
    switch (i){
      case 1000:
         Serial.println("");
         Serial.println("Ready");
         break;
      case 2000:
         Serial.println("");
         Serial.println("Steady");
         break;  
      case 3000:
         Serial.println("");
         Serial.println("Goooooo");
         break;  
      default:
         Serial.print("-");
         break;
    }
    
    i = i + 50;
    delay(50);
  }
  i = 0;
  start = millis();
  while (x <= getNumberToCount ){
    x++;
  }
  x = 0;
  counttime = millis() - start;
  sec = (float) counttime;
  
  Serial.println("Finished");
  Serial.println("I used " + String(counttime) + " milli seconds to count from 0 to " + String(getNumberToCount) );
  Serial.println("This is " + String(sec/1000) + " second, impressed?");
  }

}


