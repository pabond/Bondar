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
#pragma mark

void BPVPrintBits(uint8_t value) {
    const uint8_t bitsInByte = 8;
    printf("[");
    
    for (uint8_t iterator = 0; iterator < bitsInByte; iterator++) {
        size_t offsetBit = value >> (bitsInByte - iterator - 1);
        printf(" %lu", offsetBit & 1);
    }
    printf("]\n");
}

void BPVPrintByteBits() {

}

void BPVBitOutputFunctions() {
    BPVPrintBits(255);
}

