# ESP8266

For our first evening, we'll connect up our ESP8266 chips. To do this, you need to do the following:

1) Download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
2) Launch it and go to **File** > **Preferences** and input the following in the **Additional Boards Manager URLs**-field: `http://arduino.esp8266.com/stable/package_esp8266com_index.json
3) Go to **Tools** > **Boards** > **Board Manager...**
4) Find **esp8266 by ESP8266 Community** and click **Install**
5) Once installation is complete clear the code in the editor, and type in the [blink example](week1/blink.ino) (it's easier to understand if you type it instead of copying it).