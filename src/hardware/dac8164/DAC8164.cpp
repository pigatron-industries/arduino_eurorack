// **********************************************************************************
// Driver definition for TI DAC7565, DAC7564, DAC8164 and DAC8564 Library
// **********************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// http://creativecommons.org/licenses/by-sa/4.0/
//
// For any explanation see DAC7565 information at
// http://www.ti.com/product/dac7565
//
// Code based on following datasheet
// http://www.ti.com/lit/gpn/dac7565 
//
// Written by Charles-Henri Hallard (http://hallard.me)
//
// History : V1.00 2015-04-14 - First release
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#include "DAC8164.h"
#include <SPI.h>

// Class Constructor
DAC8164::DAC8164(uint8_t enablePin, uint8_t syncPin, uint8_t ldacPin) : 
    enablePin(enablePin), syncPin(syncPin), ldacPin(ldacPin), 
    spiMode(20000000L, MSBFIRST, SPI_MODE0) { 
}

void DAC8164::init(void) { 
    // Sync HIGH
    if (syncPin != -1) {
        pinMode(syncPin, OUTPUT);
        digitalWrite(syncPin, HIGH);
    }

    // LDAC to low
    if (ldacPin != -1) {
        pinMode(ldacPin, OUTPUT);
        digitalWrite(ldacPin, LOW);
    }

    SPI.begin();
}

void DAC8164::write(uint32_t data) { 
    if (enablePin != -1) {
        digitalWrite(enablePin, LOW);
    }
    if (syncPin != -1) {
        digitalWrite(syncPin, LOW);
    }

    uint8_t datahigh = (uint8_t) ((data >> 16) & 0xFF); 
    uint8_t datamid  = (uint8_t) ((data >>  8) & 0xFF);
    uint8_t datalow  = (uint8_t) ((data >>  0) & 0xFF);

    SPI.beginTransaction(spiMode);
    SPI.transfer(datahigh);
    SPI.transfer(datamid);
    SPI.transfer(datalow);
    SPI.endTransaction();
  
    if (syncPin != -1) {
        digitalWrite(syncPin, HIGH);
    }
    if (enablePin != -1) {
        digitalWrite(enablePin, HIGH);
    }
}

void DAC8164::setReference(uint16_t reference) { 
    uint32_t data = DAC_MASK_PD0;
    data |= reference;
    write(data);
}

void DAC8164::writeChannel(uint8_t channel, uint16_t value)
{ 
    uint32_t data ;
    if (channel == DAC_CHANNEL_A) {
        data = DAC_SINGLE_CHANNEL_UPDATE;
    } else if (channel == DAC_CHANNEL_B) {
        data = DAC_SINGLE_CHANNEL_UPDATE | DAC_MASK_DACSEL0 ;
    } else if (channel == DAC_CHANNEL_C) {
        data = DAC_SINGLE_CHANNEL_UPDATE| DAC_MASK_DACSEL1 ;
    } else if (channel == DAC_CHANNEL_D) {
        data = DAC_SINGLE_CHANNEL_UPDATE | DAC_MASK_DACSEL1 | DAC_MASK_DACSEL0 ;
    } else if (channel == DAC_CHANNEL_ALL) {
        data = DAC_BROADCAST_UPDATE | DAC_MASK_DACSEL1 ;
    } else {
        return;
    }

    // value is 14 MSB bits (last 2 bits set to 0)
    data |= value << 2;
    write(data);
}

void DAC8164::setChannelPower(uint8_t channel, uint16_t power)
{ 
    uint32_t data = power | DAC_MASK_PD0 ;
    if (channel == DAC_CHANNEL_A) {
        data |= DAC_SINGLE_CHANNEL_UPDATE;
    } else if (channel == DAC_CHANNEL_B) {
        data |= DAC_SINGLE_CHANNEL_UPDATE | DAC_MASK_DACSEL0 ;
    } else if (channel == DAC_CHANNEL_C) {
        data |= DAC_SINGLE_CHANNEL_UPDATE| DAC_MASK_DACSEL1 ;
    } else if (channel == DAC_CHANNEL_D) {
        data |= DAC_SINGLE_CHANNEL_UPDATE | DAC_MASK_DACSEL1 | DAC_MASK_DACSEL0 ;
    } else if (channel == DAC_CHANNEL_ALL) {
        data |= DAC_BROADCAST_UPDATE | DAC_MASK_DACSEL1 ;
    }

    write(data);
}

