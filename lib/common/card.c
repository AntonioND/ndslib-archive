//////////////////////////////////////////////////////////////////////
//
// card.cpp -- DS Memory card access functions
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

#include <NDS/card.h>
#include <NDS/DMA.h>

//////////////////////////////////////////////////////////////////////

void cardWriteCommand(uint8 * command) {
  int index;
	CARD_CR1H = CARD_CR1_ENABLE | CARD_CR1_IRQ;
  for (index = 0; index < 8; index++) {
    CARD_COMMAND[7-index] = command[index];
  }
}

//////////////////////////////////////////////////////////////////////

void cardPolledTransfer(uint32 flags, uint32 * destination, uint32 length, uint8 * command) {
  cardWriteCommand(command);

  CARD_CR2 = flags;
  uint32 * target = destination + length;
  do {
    // Read data if available
    if (CARD_CR2 & CARD_DATA_READY) {
      if (destination < target) *destination = CARD_DATA_RD;
      destination++;
    }
  } while (CARD_CR2 & CARD_BUSY);
}
 
//////////////////////////////////////////////////////////////////////

void cardStartTransfer(uint8 * command, uint32 * destination, int channel, uint32 flags) {
  //ASSERT((channel >= 0) && (channel < 4))
  cardWriteCommand(command);
  
  // Set up a DMA channel to transfer a word every time the card makes one
  DMA_SRC(channel) = (uint32)&CARD_DATA_RD;
  DMA_DEST(channel) = (uint32)destination;
  DMA_COUNT(channel) = 0x0001;
  DMA_CR(channel) = DMA_ENABLE | DMA_START_CARD | DMA_32_BIT | DMA_REPEAT | DMA_SRC_FIX;

  CARD_CR2 = flags;
}

//////////////////////////////////////////////////////////////////////

uint32 cardWriteAndRead(uint8 * command, uint32 flags) { 
  cardWriteCommand(command);
  CARD_CR2 = flags | CARD_ACTIVATE | CARD_nRESET | 0x07000000;
  while (!(CARD_CR2 & CARD_DATA_READY)) ;
  return CARD_DATA;
}

//////////////////////////////////////////////////////////////////////

void cardRead00(uint32 address, uint32 * destination, uint32 length, uint32 flags) {
  uint8 command[8];
  command[7] = 0;
  command[6] = address >> 24;
  command[5] = address >> 16;
  command[4] = address >> 8;
  command[3] = address;
  command[2] = 0;
  command[1] = 0;
  command[0] = 0;
  cardPolledTransfer(flags, destination, length, command);
}

//////////////////////////////////////////////////////////////////////

void cardReadHeader(uint8 * header) {
  cardRead00(0, (uint32 *)header, 512, 0x093F1FFF);
}

//////////////////////////////////////////////////////////////////////

int cardReadID(uint32 flags) {
  uint8 command[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90};
  return cardWriteAndRead(command, flags);
}

//////////////////////////////////////////////////////////////////////

#define EepromWaitBusy()	while (CARD_CR1 & /*BUSY*/0x80);

void cardReadEeprom(uint32 address, uint8 *data, uint32 length, uint32 addrtype) {
	CARD_CR1 = /*E*/0x8000 | /*SEL*/0x2000 | /*MODE*/0x40;
	CARD_EEPDATA = 0x03 | ((addrtype == 1) ? address>>8<<3 : 0); EepromWaitBusy();
	if (addrtype > 1) { CARD_EEPDATA = address >> 8; EepromWaitBusy(); }
	CARD_EEPDATA = address & 0xFF; EepromWaitBusy();
	while (length > 0)
	{
		CARD_EEPDATA = 0; EepromWaitBusy();
		*data++ = CARD_EEPDATA;
	}
	CARD_CR1 = /*MODE*/0x40;
}

//////////////////////////////////////////////////////////////////////

// NOTE: does not work for small EEPROMs
void cardWriteEeprom(uint32 address, uint8 *data, uint32 length, uint32 addrtype) {
	uint32 address_end = address + length;
	int i;
	while (address < address_end)
	{
		// set WEL (Write Enable Latch)
		CARD_CR1 = /*E*/0x8000 | /*SEL*/0x2000 | /*MODE*/0x40;
		CARD_EEPDATA = 0x06; EepromWaitBusy();
		CARD_CR1 = /*MODE*/0x40;

		// program maximum of 32 bytes
		CARD_CR1 = /*E*/0x8000 | /*SEL*/0x2000 | /*MODE*/0x40;
		CARD_EEPDATA = 0x02 | ((addrtype == 1) ? address>>8<<3 : 0); EepromWaitBusy();
		if (addrtype > 1) { CARD_EEPDATA = address >> 8; EepromWaitBusy(); }
		CARD_EEPDATA = address & 0xFF; EepromWaitBusy();
		for (i=0; address<address_end && i<32; i++, address++) { CARD_EEPDATA = *data++; EepromWaitBusy(); }
		CARD_CR1 = /*MODE*/0x40;

		// wait programming to finish
		CARD_CR1 = /*E*/0x8000 | /*SEL*/0x2000 | /*MODE*/0x40;
		CARD_EEPDATA = 0x05; EepromWaitBusy();
		do { CARD_EEPDATA = 0; EepromWaitBusy(); } while (CARD_EEPDATA & 0x01);	// WIP (Write In Progress) ?
		CARD_CR1 = /*MODE*/0x40;
	}
}

//////////////////////////////////////////////////////////////////////