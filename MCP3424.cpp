/* MCP3424 library version 1.2

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

#include <MCP3424.h>

MCP3424::MCP3424(uint8_t adresse){
Wire.begin();
_adresse=1101<<3;
_adresse|=adresse;
}

MCP3424::~MCP3424(){

}


void MCP3424::Configuration(uint8_t channel,uint8_t resolution,bool mode,uint8_t PGA){
_PGA=PGA;

if(resolution!=12 && resolution!=14 && resolution!=16 && resolution!=18) {
_resolution=12;
} else _resolution=resolution;

_mode=mode;
_cfgbyte=0;
_cfgbyte=_cfgbyte<<2;
_cfgbyte|=(channel-1);
_cfgbyte=_cfgbyte<<1;
_cfgbyte|=mode;
_cfgbyte=_cfgbyte<<2;
_cfgbyte|=int((_resolution-12)/2);
_cfgbyte=_cfgbyte<<2;
_cfgbyte|=int(log(PGA)/log(2));

Wire.beginTransmission(_adresse);
Wire.write(_cfgbyte);
Wire.endTransmission();
}

void MCP3424::NewConversion(){
Wire.beginTransmission(_adresse);
Wire.write((_cfgbyte|=128));
Wire.endTransmission();
}

bool MCP3424::IsConversionFinished(){

if(_resolution!=18){
_RequestedByte = 3;    
} else _RequestedByte = 4;

Wire.requestFrom(_adresse, _RequestedByte);
_i=0;
while(Wire.available()) _Buffer[_i++]=Wire.read();

_testvariable = _Buffer[_RequestedByte-1]>>7;

return _testvariable;

}


long MCP3424::Measure(){

  _resultat=0;

while(IsConversionFinished()==1);

switch (_resolution){
  
case 12:
 _resultat = _Buffer[0];
 _resultat&=0b00001111;  
 _resultat = _resultat << 8;    
_resultat |= _Buffer[1];

if(_resultat>2048-1) {
_resultat=_resultat-4096-1;
}

 _resultat = _resultat*1000/_PGA;      
   
 break;
    
 case 14:
_resultat = _Buffer[0];
 _resultat&=0b00111111;  
_resultat = _resultat << 8;    
 _resultat |= _Buffer[1];

if(_resultat>8192-1) {
_resultat=_resultat-16384-1;
}

_resultat = _resultat*250/_PGA;  
       
 break;
    
case 16:

_resultat = _Buffer[0]; 
_resultat = _resultat << 8;    
_resultat |= _Buffer[1];

if(_resultat>32768-1) {
_resultat=_resultat-65536-1;
}

_resultat = _resultat*62.5/_PGA;   
      
 break;
  
case 18:

_resultat = _Buffer[0];
 _resultat&=0b00000011;  
  _resultat = _resultat << 8;    
  _resultat |= _Buffer[1];
 _resultat = _resultat << 8;    
 _resultat |= _Buffer[2];
 
if(_resultat>131072-1) {
_resultat=_resultat-262144-1;
}

_resultat = _resultat*15.625/_PGA; 

  break;
}
 			
return _resultat;
	

}

