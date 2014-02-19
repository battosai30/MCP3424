/* MCP 3424 version 1.2 example sketch OneShotConversion
Written by B@tto 
Contact : batto@hotmail.fr

In this example, one conversion per second is performed on channel 1 and 16 bits resolution. 
A new conversion has to be initiated by the user
*/


#include <Wire.h>
#include <MCP3424.h>

MCP3424 MCP(6); // Declaration of MCP3424

long Voltage;

void setup(){ 

  Serial.begin(9600); // start serial for output
  MCP.Configuration(1,16,0,1); // Channel 1, 16 bits resolution, one-shot mode, amplifier gain = 1

}

void loop(){

  MCP.NewConversion(); // New conversion is initiated
  
  Voltage=MCP.Measure(); // Measure, note that the library waits for a complete conversion
 
  Serial.print("Voltage = "); // print result
  Serial.print(Voltage);
  Serial.println(" microVolt");
  
  delay (1000);
  
}

