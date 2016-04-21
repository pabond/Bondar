//
//  BPVBitOutputFunctions.h
//  HWMacros
//
//  Created by Bondar Pavel on 4/19/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVBitOutputFunctions_h
#define BPVBitOutputFunctions_h

typedef enum {
    BPVBigEndianType,
    BPVLittleEndianType
} BPVEndianType;

void BPVPrintBits(uint8_t value);
void BPVBitOutputFunctions();
void BPVPrintByteBits(void *address, size_t size);


#endif /* BPVBitOutputFunctions_h */
