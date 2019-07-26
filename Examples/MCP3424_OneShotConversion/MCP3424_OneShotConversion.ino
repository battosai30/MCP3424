/* MCP 3424 version 1.2 example sketch OneShotConversion
Written by B@tto 
Contact : batto@hotmail.fr

In this example, one conversion per second is performed on channel 1 and 16 bits resolution. 
A new conversion has to be initiated by the user
*/


#include <Wire.h>
#include <MCP342x.h>

MCP342x MCP(6); // Declaration of MCP3424

long Voltage;

void setup(){ 

  Serial.begin(9600); // start serial for output
  MCP.begin(0);
  MCP.setConfiguration(CH1,RESOLUTION_16_BITS,ONE_SHOT_MODE,PGA_X1); // Channel 1, 16 bits resolution, one-shot mode, amplifier gain = 1

}

void loop(){

  MCP.newConversion(); // New conversion is initiated
  
  Voltage=MCP.measure(); // Measure, note that the library waits for a complete conversion
 
  Serial.print("Voltage = "); // print result
  Serial.print(Voltage);
  Serial.println(" microVolt");
  
  delay (1000);
  
}

