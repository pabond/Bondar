//
//  BPVPrintDataType.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include <stdbool.h>

#include "BPVPrintDataType.h"

#define BPVPrintTypeSize(type, value) \
    do { \
        printf("Size of " #type " = %lu bytes\n", sizeof(value));\
    } while (0);

void BPVPrintDataType() {
    int intValue = 0;
    short ShortValue = 0;
    double doubleValue = 0;
    float floatValue = 0.f;
    long longValue = 0;
    long long longLongValue = 0;
    long double longDoubleValue = 0;
    const char charValue = 'c';
    bool boolValue = true;
    unsigned int unsignedIntValue = 0;
    
    BPVPrintTypeSize(int, intValue)
    BPVPrintTypeSize(short, ShortValue)
    BPVPrintTypeSize(double, doubleValue)
    BPVPrintTypeSize(float, floatValue)
    BPVPrintTypeSize(long, longValue)
    BPVPrintTypeSize(long long, longLongValue)
    BPVPrintTypeSize(long double, longDoubleValue)
    BPVPrintTypeSize(const char, charValue)
    BPVPrintTypeSize(bool, boolValue)
    BPVPrintTypeSize(unsigned int, unsignedIntValue)
}
