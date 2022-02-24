INTRODUCTION
============
This is the documentation for the QTouch SAMD10 Xplained Mini Selfcap Example.

Example description
===================
This example demonstates the basic touch application where the on-board touch sensor is measured and the touch status is indicated using LED. The touch library parameters are also displayed in the datavisualizer software when the hardware kit is connected through edbg/medbg vritual com port.

RELATED DOCUMENTS / APPLICATION NOTES
=====================================
Refer the microchip developer page link `"Generate Atmel Board User Project" <http://microchipdeveloper.com/touch:generate-atmel-board-touch-project>`_ and `"SAMD10 Xplainedmini kit user guide" <http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42387-ATSAMD10-Xplain-Mini_User-Guide.pdf>`_ for more details. 

SUPPORTED EVALUATION KIT
========================
	* `SAMD10 Xplainedmini kit <http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=ATSAMD10-XMINI>`_

INTERFACE SETTINGS
==================
	* Timer
		* Instance RTC
		* Input clock 8Mhz with prescaler 8
		* Compare match interrupt enabled 
	* CPUINIT
		* Global Interrupt Enabled
	* Digital Output Pin
		* PA09 as LED0 pin
	* Touch Buttons
		* Y5 (PA07) as button0
	* Datavisualizer port pins
		* PA10 as TXD, PA11 as RXD

RUNNING THE DEMO
================
1. Select "EXPORT PROJECT" tab and click "Download Pack" to save the .atzip file.
2. Import .atzip file into Atmel Studio 7, File->Import->Atmel Start Project.
3. Build Solution and make sure no compiler errors occur.
4. Press "Start without debugging" or use "CTRL+ALT+F5" hotkeys to run the application.
5. The LED0 turns ON when touch made on-board touch button and turns OFF when touch is removed. 
6. Open Atmel Data Visualizer software and set the config path to the folder that contains the datastreamer scripts. 
7. Open serial port connection and connect to the target. Verify the connection is made successfully and the touch status is displayed on the dashboard. 