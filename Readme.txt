MCP3424 Library for Arduino
Author:  B@tto
Contact: batto@hotmail.fr

Current version
1.1

History
1.1 06/12/2012 : issues with detection of a finished conversion has been resolved
1.0 15/07/2012: initial release 

Description
MCP3424 is a I2C 4 channels, 18 bits resolution ADC controlled over I2C.
It has an internal reference of 2.048V and an on-board programmable gain amplifier (PGA).
Supply : 2.7V to 5V
Resolution is programmable (12, 14, 16 or 18 bits). 
Download, install and import

Download zip 
Put the MCP3424 folder in "hardware\libraries\". 
In the Arduino IDE, create a new sketch (or open one) and 
select from the menubar "Sketch->Import Library->MCP3424".
Once the library is imported, an "#incude <MCP3424.h>" line will appear at the top of your sketch. 

Creation
 MCP3424(int address) -> Create instance of MCP3424.Address is A2A1A0 (refer to datasheet). For example, if pins Adr0 and Adr1 are high, the instanciation would be "MCP3424 MCP(6)" because A2=1 A1=1 A0=0 so in binary 110 and 6 in decimal
 
Methods
	
void Configuration(int channel,int resolution,int mode,int mode, int PGA) -> send the configuration byte to the MCP3424. Choose channel (1,2,3 or 4), resolution (12, 14, 16 or 18), mode (1=continous mode 0=one-shot conversion), PGA (1, 2, 4 or 8)
long Measure() -> Return the result of the lastest conversion in µV. Note that the library waits for a complete conversion.
void NewConversion() -> in one-shot mode, initiate a new conversion
int IsConversionFinished() -> Returns 1 if conversion is not finished, 0 if it's completed

Example
One-Shot conversion -> the conversion is initiated by the user
Multichannel -> classic use scanning all the channels

FAQ
How can I use multiple MCP3424 object ?
MCP3424 is a class, like any class you can drive any numbers of chip you want with only 2 single pin (Adr0 and Adr1) but by setting different address for each.

I can't measure voltage over 2.048V, why ?
Because the internal reference is 2.O48V, but if you use it in differential mode, you can use it from -2.048V to +2.048V. 
Another solution is to use a voltage divider (2 x 1k resistors for example).

I'm not measuring voltage over 2.048V but my MCP3424 seems to be saturated, why ?
Maybe you are using the programmable amplifier (PGA). In fact, the limit of 2.O48V is effective after it, so if your voltage multipliates by the PGA is superior to 2.048V, the ADC is saturated.
