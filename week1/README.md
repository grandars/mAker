# ESP8266

For our first evening, we'll connect up our ESP8266 chips. To do this, you need to do the following:

1) Download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
2) Download and install NodeMCU drivers (https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers)
3) Launch it and go to **File** > **Preferences** and input the following in the **Additional Boards Manager URLs**-field: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
4) Go to **Tools** > **Boards** > **Board Manager...**
5) Find **esp8266 by ESP8266 Community** and click **Install**
6) Once installation is complete clear the code in the editor, and type in the [blink example](blink.ino) (it's easier to understand if you type it instead of copying it).
