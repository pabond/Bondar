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

#define BPVPrintTypeSize(type) \
    do { \
        type value; \
        printf("Size of " #type " = %lu bytes\n", sizeof(value));\
    } while (0)

void BPVPrintDataType() {
    BPVPrintTypeSize(int);
    BPVPrintTypeSize(short);
    BPVPrintTypeSize(double);
    BPVPrintTypeSize(float);
    BPVPrintTypeSize(long);
    BPVPrintTypeSize(long long);
    BPVPrintTypeSize(long double);
    BPVPrintTypeSize(const char);
    BPVPrintTypeSize(bool);
    BPVPrintTypeSize(unsigned int);
    BPVPrintTypeSize(uint8_t);
}
