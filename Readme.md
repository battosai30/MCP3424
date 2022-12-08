# MCP342x Library for Arduino #

Author:  B@tto

Contact: batto@hotmail.fr

### Current version ###

1.92

## History ##

- 1.92 06/04/2022 : add some constrain in setConfiguration() to avoid out of index crashes, and add a getAddress() function to get i2c computed real address
- 1.9 27/08/2021 : changed CHANNELS to byte type in setConfiguration()
- 1.8 26/02/2019 : correction for 16-bit platform (bad bit shifting during 18-bits acquisition)
- 1.7 25/07/2019 : support on MCP3421 confirmed, changed to MCP342x. Update examples
- 1.6 19/04/2019 : Bug correction
- 1.3 26/01/2017 : Multichannel example had a bug (out of index error on Voltage[]) and code was rewritten
- 1.1 06/12/2012 : issues with detection of a finished conversion has been resolved
- 1.0 15/07/2012 : initial release 

## Description ##

MCP342x (3421/22/23/24) is a I2C 1/2/3/4 channels, 18 bits resolution ADC controlled over I2C.

It has an internal reference of 2.048V and an on-board programmable gain amplifier (PGA).

Supply : 2.7V to 5V

Resolution is programmable (12, 14, 16 or 18 bits). 

## Download, install and import ##
- Download zip
- Put the MCP3424 folder in "hardware\libraries\". 
- In the Arduino IDE, create a new sketch (or open one) and 
- Select from the menubar "Sketch->Import Library->MCP342x".
- Once the library is imported, an "#include <MCP342x.h>" line will appear at the top of your sketch. 

## Creation ##
**MCP3424(int address)** -> Create instance of MCP342x.Address is A2A1A0 (refer to datasheet). For example, if pins Adr0 and Adr1 are high, the instanciation would be "MCP342x MCP(6)" because A2=1 A1=1 A0=0 so in binary 110 and 6 in decimal.
 
## Methods ##
	
**void setConfiguration(byte channel,RESOLUTION resolution,MEASURE_MODE mode,PGA pga)** -> send the configuration byte to the MCP3424. 

Available MEASURE_MODE :
- ONE_SHOT_MODE
- CONTINUOUS_MODE

Available RESOLUTION :
- RESOLUTION_12_BITS
- RESOLUTION_14_BITS
- RESOLUTION_16_BITS
- RESOLUTION_18_BITS

Available CHANNELS :	
- CH1
- CH2
- CH3
- CH4

Available PGA :
- PGA_X1
- PGA_X2
- PGA_X4
- PGA_X8


**getConfiguration()** -> return the rax value of the configuration register.

**getRawDatas(uint8_t buffer[4])** -> fill the array passed as argument with raw result (means without conversion to mv). Mainly intended for debug.

**long measure()** -> Return the result of the lastest conversion in nanoVolt. Note that the library waits for a complete conversion.

**void newConversion()** -> in one-shot mode, initiate a new conversion

**int isConversionFinished()** -> Returns 1 if conversion is not finished, 0 if it's completed

## Examples ##

**One-Shot conversion** -> the conversion is initiated by the user

**Multichannel** -> classic use scanning all the channels

## FAQ ##
#### How can I use multiple MCP342x object ? ####
MCP342x is a class, like any class you can drive any numbers of chip you want with only 2 single pin (Adr0 and Adr1) but by setting different address for each.

#### I can't measure voltage over 2.048V, why ? ####
Because the internal reference is 2.O48V, but if you use it in differential mode, you can use it from -2.048V to +2.048V. 
Another solution is to use a voltage divider (2 x 1k resistors or example).

#### I'm not measuring voltage over 2.048V but my MCP342x seems to be saturated, why ? ####
Maybe you are using the programmable amplifier (PGA). In fact, the limit of 2.O48V is effective after it, so if your voltage multipliates by the PGA is superior to 2.048V, the ADC is saturated.

#### I get compilation errors, why ? ####
Check where you get the library : a (very) old version of mine is still given by some chinese manufacturers, and leads to errors. Simply get the last version on github.
