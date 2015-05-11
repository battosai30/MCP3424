/* MCP 3424 version 1.2 example sketch Multichannel
Written by B@tto 
Contact : batto@hotmail.fr

In this example, the four channel are measured and results displayed by serail connection.
*/

#include <MCP3424.h>
#include <Wire.h>

MCP3424 MCP(6); // Declaration of MCP3424 pin addr1 et addr0 are connected to +5V

long Voltage[4]; // Array used to store results

void setup() {

  Serial.begin(9600);  // start serial for output

}

void loop(){

  for(int i=1;i<=4;i++){

    MCP.Configuration(i,18,1,8); // MCP3424 is configured to channel i with 18 bits resolution, continous mode and gain defined to 8 

    Voltage[i-1]=MCP.Measure(); // Measure is stocked in array Voltage, note that the library will wait for a completed conversion that takes around 200 ms@18bits

    Serial.print("Channel "); // print results
    Serial.print(i);
    Serial.print(" : ");  
    Serial.print(Voltage[i-1]);
    Serial.println(" microVolt");

  }
  
  delay(500);
}

