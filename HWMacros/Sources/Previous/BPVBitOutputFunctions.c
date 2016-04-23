//
//  BPVBitOutputFunctions.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/19/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVBitOutputFunctions.h"

#pragma mark -
#pragma mark Privat method declaration

static
void BPVPrintBits(uint8_t value);

static
BPVEndianType BPVEdianness();

static
void BPVPrintBytesWithSize(void *address, size_t size);

static
void BPVPrintBytesWithSizeAndEndianness(void *address, size_t size, BPVEndianType);

#pragma mark -
#pragma mark Public method implementation

extern
void BPVBitOutputFunctions() {
    int intValue = 567;
    float floatValue = 543.6f;
    
    BPVPrintBits(7);
    BPVPrintBytesWithSize(&intValue, sizeof(intValue));
    BPVPrintBytesWithSizeAndEndianness(&floatValue, sizeof(floatValue), BPVLittleEndianType);
}

#pragma mark -
#pragma mark Privat method implementation

BPVEndianType BPVEdianness() {
    uint16_t value = 1;
    
    return (((char *)&value)[0]) ? BPVBigEndianType : BPVLittleEndianType;
}

void BPVPrintBytesWithSizeAndEndianness(void *address, size_t size, BPVEndianType endianness) {
    printf("\n");
    for (size_t iterator = 0; iterator < size; iterator++) {
        uint8_t index = (endianness == BPVBigEndianType) ? iterator : size - iterator - 1;
        BPVPrintBits(((uint8_t *)address)[index]);
    }
    
    printf("\n");
}

void BPVPrintBits(uint8_t value) {
    const uint8_t bitsInByte = 8;
    printf("[");
    for (uint8_t iterator = 0; iterator < bitsInByte; iterator++) {
        size_t offsetBit = value >> (bitsInByte - iterator - 1);
        printf(" %lu", offsetBit & 1);
    }
    
    printf("]\n");
}

void BPVPrintBytesWithSize(void *address, size_t size) {
    BPVEndianType endianness = BPVEdianness();
    BPVPrintBytesWithSizeAndEndianness(address, size, endianness);
}
