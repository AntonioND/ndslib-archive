//////////////////////////////////////////////////////////////////////
//
// audio.cpp -- Audio control for the ARM7
//
// version 0.1, February 14, 2005
//
//  Copyright (C) 2005 Michael Noland (joat) and Jason Rogers (dovoto)
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any
//  damages arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any
//  purpose, including commercial applications, and to alter it and
//  redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you
//     must not claim that you wrote the original software. If you use
//     this software in a product, an acknowledgment in the product
//     documentation would be appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and
//     must not be misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source
//     distribution.
//
// Changelog:
//   0.1: First version
//
//////////////////////////////////////////////////////////////////////

#include <NDS/ARM7/audio.h>
#include <NDS/ARM7/serial.h>
#include <NDS/ARM7/bios.h>

#define PM_AMP_OFFSET     2

//based on neimods code code
u8 MIC_ReadData(void)
{
  u16 result, result2;
  
  while(SERIAL_CR & SERIAL_BUSY)
    swiDelay(1);
 
  SERIAL_CR = SERIAL_ENABLE | SPI_DEVICE_TOUCH | SPI_BAUDRATE_2Mhz | SPI_CONTINUOUS;
  SERIAL_DATA = 0xEC;  // Touchscreen command format for AUX
  
  while(SERIAL_CR & SERIAL_BUSY)
    swiDelay(1);

  SERIAL_DATA = 0x00;

  while(SERIAL_CR & SERIAL_BUSY)
    swiDelay(1);

  result = SERIAL_DATA;
  SERIAL_CR = SERIAL_ENABLE | SPI_DEVICE_TOUCH | SPI_BAUDRATE_2Mhz;
  SERIAL_DATA = 0x00; 

  while(SERIAL_CR & SERIAL_BUSY)
    swiDelay(1);

  result2 = SERIAL_DATA;

  return (((result & 0x7F) << 1) | ((result2>>7)&1));
}
void MIC_On(void)
{
  while(SERIAL_CR & SERIAL_BUSY)
  swiDelay(1);

  SERIAL_CR = SERIAL_ENABLE | SPI_DEVICE_POWER | SPI_BAUDRATE_1Mhz | SPI_CONTINUOUS;
  SERIAL_DATA = PM_AMP_OFFSET;

  while(SERIAL_CR & SERIAL_BUSY)
    swiDelay(1);

  SERIAL_CR = SERIAL_ENABLE | SPI_DEVICE_POWER | SPI_BAUDRATE_1Mhz;
  SERIAL_DATA = 1;
}
void MIC_Off(void)
{
  while(SERIAL_CR & SERIAL_BUSY)
  swiDelay(1);

  SERIAL_CR = SERIAL_ENABLE | SPI_DEVICE_POWER | SPI_BAUDRATE_1Mhz | SPI_CONTINUOUS;
  SERIAL_DATA = PM_AMP_OFFSET;

  while(SERIAL_CR & SERIAL_BUSY)
    swiDelay(1);

  SERIAL_CR = SERIAL_ENABLE | SPI_DEVICE_POWER | SPI_BAUDRATE_1Mhz;
  SERIAL_DATA = 0;
}



