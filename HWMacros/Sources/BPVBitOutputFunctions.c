//
//  BPVBitOutputFunctions.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/19/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVBitOutputFunctions.h"

void BPVPrintBits(uint8_t value) {
    const uint8_t bitsInByte = 8;
    printf("|");
    
    for (uint8_t iterator; iterator < bitsInByte; iterator++) {
        printf("");
    }
}