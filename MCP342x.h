/* MCP342x library version 1.8

Writed by B@tto 
Contact : batto@hotmail.fr


  MCP342x.h - ADC 18 bits i2c library for Wiring & Arduino
  Copyright (c) 2012 Yann LEFEBVRE.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef MCP342x_H
#define MCP342x_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
//#include <Math.h>

typedef enum MEASURE_MODE
{
	ONE_SHOT_MODE=0,
	CONTINUOUS_MODE
};

typedef enum RESOLUTION
{
	RESOLUTION_12_BITS=0,
	RESOLUTION_14_BITS,
	RESOLUTION_16_BITS,
	RESOLUTION_18_BITS
};

typedef enum CHANNELS
{
	CH1=0,
	CH2,
	CH3,
	CH4
};

typedef enum PGA
{
	PGA_X1=0,
	PGA_X2,
	PGA_X4,
	PGA_X8
};

const uint8_t resolutionConvert[] = {12,14,16,18};
const uint8_t PGAConvert[] = {1,2,4,8};

class MCP342x {

public:

MCP342x(uint8_t adresse);
~MCP342x();
void begin(uint8_t setMod = 1);
void setConfiguration(CHANNELS channel,RESOLUTION resolution,MEASURE_MODE mode,PGA pga);
void newConversion();
bool isConversionFinished();
int32_t measure();
void getRawDatas(uint8_t buffer[4]);
uint8_t getConfiguration();

private:

uint8_t _adresse;
RESOLUTION _resolution;
MEASURE_MODE _mode;
PGA _PGA;
int32_t _LSB;
uint8_t _buffer[4];

};

#endif
