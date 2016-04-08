//
//  main.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVRangeOfNumber.h"

#include "BPVPrintDataType.h"

#include "BPVPlusMinusOne.h"

#include "BPVMathFunctions.h"

#include "BPVDevideCode.h"


int main(int argc, const char * argv[]) {
    
    printf("%u\n", BPVRangeOfNumber(57, -250));
    
    long long longLongNumber = 44;
    long longNumber = 43;
    int intNumber = - 4;
    float floatNumber = 3.5f;
    short shortNumbe = 3;
    double doubleNumber = 2.55;
    char charType = 'a';
    unsigned int unsignedIntNumber = 35;
    
    printf("%lld, %ld, %i, %f, %f, %c, %i, %u\n",
           longLongNumber, longNumber, intNumber, floatNumber, doubleNumber, charType, shortNumbe, unsignedIntNumber);
    
    BPVPrintFloat(3 * 3 / 4 % 7 + 4 * 3 - 1.5 + 65);
    
    BPVPrintInt(5);
    BPVPrintChar('&');
    BPVPrintFloat(3.55f);
    BPVPrintString("Hello, World");
    
    BPVPrintInt(BPVDecrement(5));
    BPVPrintInt(BPVIncrement(10));
    
    BPVDevideCode();
    
    return 0;
}
