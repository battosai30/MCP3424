/* MCP3424 library version 1.3

Writed by B@tto
Contact : batto@hotmail.fr


  MCP3424.cpp - ADC 18 bits i2c library for Wiring & Arduino
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

#include "MCP3424.h"

MCP3424::MCP3424(uint8_t adresse){

_adresse=0b1101<<3;
_adresse|=adresse;



}

MCP3424::~MCP3424(){

}

void MCP3424::begin(byte setMod){

#ifdef ENERGIA
Wire.setModule(setMod);
#endif

Wire.begin();

}

void MCP3424::configuration(uint8_t channel,uint8_t resolution,bool mode,uint8_t PGA){

if(resolution!=12 && resolution!=14 && resolution!=16 && resolution!=18) _resolution=12;
 else _resolution=resolution;

_PGA=PGA;
_mode=mode;

_cfgbyte=0;
_cfgbyte |= ((channel-1) & 0x3) << 5;
_cfgbyte |= (mode & 0x1) << 4;
_cfgbyte |= (int((_resolution-12)/2) & 0x3) << 2;
_cfgbyte |= (int(logf(PGA)/logf(2))) & 0x3;

Wire.beginTransmission(_adresse);
Wire.write(_cfgbyte);
Wire.endTransmission();

}

void MCP3424::newConversion(){

Wire.beginTransmission(_adresse);
Wire.write((_cfgbyte|=128));
Wire.endTransmission();

}

bool MCP3424::isConversionFinished(){

uint8_t _requestedByte;

if(_resolution!=18){
_requestedByte = 3;
} else _requestedByte = 4;

Wire.requestFrom(_adresse, _requestedByte);

uint8_t _i=0;

while(Wire.available()) _buffer[_i++]=Wire.read();

return (_buffer[_requestedByte-1] & 0b10000000);

}


long MCP3424::measure(){

long _resultat=0;

while(isConversionFinished()==1);

switch (_resolution){

case 12:

 _resultat = (((long)_buffer[0] & 0x0F) << 8) | ((long)_buffer[1] & 0xFF); 
 
 _resultat |= long(_buffer[0] & 0x80) << 24;

 _resultat = _resultat*1000.0/_PGA;

 break;

 case 14:
 
_resultat = (((long)_buffer[0] & 0xBF) << 8) | ((long)_buffer[1] & 0xFF); 

_resultat |= long(_buffer[0] & 0x80) << 24;

_resultat = _resultat*250/_PGA;

 break;

case 16:

_resultat = (((long)_buffer[0] & 0x7F) << 8) | ((long)_buffer[1] & 0xFF); 

 _resultat |= long(_buffer[0] & 0x80) << 24;

_resultat = _resultat*62.5/_PGA;

 break;

case 18:

_resultat = (((long)_buffer[0] & 0x01) << 16) | (((long)_buffer[1] & 0xFF) <<8) | ((long)_buffer[2] & 0xFF); 

_resultat |=((long)_buffer[0] & 0x80) << 24;

_resultat = _resultat*15.625/_PGA;

  break;
}

return _resultat;

}

