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
    
    printf("%f\n", 3 * 3 / 4 % 7 + 4 * 3 - 1.5 + 65);
    
    BPVPrintInt(5);
    BPVPrintChar('&');
    BPVPrintFloat(3.55f);
    BPVPrintString("Hello, World");
    
    return 0;
}
