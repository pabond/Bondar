//
//  BPVMacrosTask.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVMacrosTask.h"

BPVPrintTypeValue(int, i)
BPVPrintTypeValue(float, f)
BPVPrintTypeValue(short, i)
BPVPrintTypeValue(long, ld)
BPVPrintTypeValue(double, f)
BPVPrintTypeValue(char, c)

void BPVPrintTypeUsingMacros() {
    int intValue = 5;
    float floatValue = 33.3f;
    short shortValue = 3;
    long longValue = 55;
    double doubleValue = 55.33;
    const char charValue = '@';
    
    BPVOutput_int(intValue);
    BPVOutput_float(floatValue);
    BPVOutput_short(shortValue);
    BPVOutput_long(longValue);
    BPVOutput_double(doubleValue);
    BPVOutput_char(charValue);
    
    BPVPrintTypeWithMacros(int, intValue);
    BPVPrintTypeWithMacros(float, floatValue);
    BPVPrintTypeWithMacros(char, charValue);
    BPVPrintTypeWithMacros(double, doubleValue);
    BPVPrintTypeWithMacros(short, shortValue);
    BPVPrintTypeWithMacros(long, longValue);
}
