# ESP8266

For our first evening, we'll connect up our ESP8266 chips. To do this, you need to do the following:

1) Download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
2) Download and install NodeMCU drivers
  * [Windows](https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers)
  * [Mac](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) - If you have a Mac running macOS High Sierra, you need to allow the driver to run after installation. Go to **System Preferences** > **Security & Privacy** and click **Allow**
3) Launch Arduino and go to **File** > **Preferences** and input the following in the **Additional Boards Manager URLs**-field: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
4) Go to **Tools** > **Boards** > **Board Manager...**
5) Find **esp8266 by ESP8266 Community** and click **Install**
6) Once installation is complete clear the code in the editor, and type in the [blink example](blink.ino) (it's easier to understand if you type it instead of copying it).
7) Setup the Arduino IDE for your board by going to **Tools** > **Board...** and select **NodeMCU 1.0 (ESP-12E Module)**
8) Plug the board to your PCs USB ports
9) Check under **Tools** > **Port** that you have *either* **COM3** (or any COM-port except COM1) or **/dev/cu.SLAB_USBtoUART** and select it
10) Hold down the **FLASH**-button on the board and click **Upload**
11) Things *should* work
