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

BPVEndianType BPVEdiannes();

#pragma mark -
#pragma mark Public method implementation


void BPVPrintBits(uint8_t value) {
    const uint8_t bitsInByte = 8;
    printf("[");
    
    for (uint8_t iterator = 0; iterator < bitsInByte; iterator++) {
        size_t offsetBit = value >> (bitsInByte - iterator - 1);
        printf(" %lu", offsetBit & 1);
    }
    printf("]\n");
    
}

void BPVPrintByteBits(void *address, size_t size) {
    uint8_t *value = (unsigned char *)address;
    
}

void BPVBitOutputFunctions() {
    BPVPrintBits(7);
}

#pragma mark -
#pragma mark Privat method implementation

BPVEndianType BPVEdiannes() {
    uint16_t chackNuber = 7;
    return (((char *)&chackNuber)[0]) ? BPVBigEndianType : BPVLittleEndianType;
}
