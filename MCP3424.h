/* MCP3424 library version 1.2

Writed by B@tto 
Contact : batto@hotmail.fr


  MCP3424.h - ADC 18 bits i2c library for Wiring & Arduino
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


#ifndef MCP3424_H
#define MCP3424_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <Math.h>

class MCP3424 {

public:

MCP3424(uint8_t adresse);
~MCP3424();
void Configuration(uint8_t channel,uint8_t resolution,bool mode,uint8_t PGA);
void NewConversion();
bool IsConversionFinished();
long Measure();

private:

uint8_t _adresse;
long _resultat;
uint8_t _resolution;
bool _mode;
uint8_t _i;
uint8_t _testvariable;
uint8_t _cfgbyte;
uint8_t _PGA;
uint8_t _RequestedByte;
uint8_t _Buffer[4];

};

#endif
