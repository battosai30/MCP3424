/* MCP 3424 version 1.7 example Non-blocking Multichannel sketch
Written by B@tto 
Edit: LuckyLuzz
Contact : batto@hotmail.fr

In this example, the four channel are measured and results displayed by serail connection.
*/

#include <MCP342x.h>
#include <Wire.h>
#include <Ticker.h>

MCP342x MCP_1(0x6C);     // Declaration of MCP3424 pin addr1 et addr0 are connected to +5V
MCP342x MCP_2(0x6E);     // Declaration of MCP3424 pin addr1 et addr0 are connected to +5V
long Voltage_1[4] = {1}; // Array used to store results
long Voltage_2[4] = {1}; // Array used to store results

Ticker Timer1;
bool FLAG_Timer1 = false;

void Void_Timer1()
{
  FLAG_Timer1 = true;
}

void setup()
{
  Serial.begin(115200); // start serial for output
  Wire.setClock(400000); //Set I²C Clock Speed
  Wire.begin();
  Timer1.attach_ms(300, Void_Timer1); //Set Timer for 300ms. -->One 18Bit conversion

//Conversion Time 1000/SPS = 18Bit 300ms | 16Bit 70ms  | 14Bit 20ms | 12Bit 5ms
}

void I2C_Update()
{
  static int i2c_counterread = 1;
  static bool adc_call = true;

  if (adc_call == true)
  { //Conversion Time 1000/SPS = 18Bit 300ms | 16Bit 70ms  | 14Bit 20ms | 12Bit 5ms
    MCP_1.setConfiguration(i2c_counterread, 18, 1, 1);
    MCP_2.setConfiguration(i2c_counterread, 18, 1, 1);
    adc_call = false;
    Serial.println("New conversion");
  }
  else
  {
    if ((MCP_1.isConversionFinished() == false) && (MCP_2.isConversionFinished() == false))
    {
      Voltage_1[i2c_counterread - 1] = MCP_1.measure();
      Voltage_2[i2c_counterread - 1] = MCP_2.measure();
      i2c_counterread += 1;
      adc_call = true;
      Serial.println("Read ADC Value");
    }
  }

  if (i2c_counterread >= 5)
  {
    i2c_counterread = 1;
  }

  Serial.println("--------------------------------------------------------------------------------");
  Serial.println("18 bits");

  Serial.print("ADC 1 Channel 1"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_1[0]);
  Serial.print(" : ");
  Serial.println(" Microvolt ");

  Serial.print("ADC 1 Channel 2"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_1[1]);
  Serial.print(" : ");
  Serial.print(" Microvolt ");
  Serial.println("");

  Serial.print("ADC 1 Channel 3"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_1[2]);
  Serial.print(" : ");
  Serial.print(" Microvolt ");
  Serial.println("");

  Serial.print("ADC 1 Channel 4"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_1[3]);
  Serial.print(" : ");
  Serial.print(" Microvolt ");
  Serial.println("");

  Serial.print("ADC 2 Channel 1"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_2[0]);
  Serial.print(" : ");
  Serial.println(" Microvolt ");

  Serial.print("ADC 2 Channel 2"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_2[1]);
  Serial.print(" : ");
  Serial.print(" Microvolt ");
  Serial.println("");

  Serial.print("ADC 2 Channel 3"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_2[2]);
  Serial.print(" : ");
  Serial.print(" Microvolt ");
  Serial.println("");

  Serial.print("ADC 2 Channel 4"); // print results
  Serial.print(" : ");
  Serial.print(Voltage_2[3]);
  Serial.print(" : ");
  Serial.print(" Microvolt ");
  Serial.println("");
}

void loop()
{
  if (FLAG_Timer1)
  {
    I2C_Update();
    FLAG_Timer1 = false;
  }
}
