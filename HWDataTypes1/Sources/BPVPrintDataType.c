//
//  BPVPrintDataType.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVPrintDataType.h"

void BPVPrintInt(int intNumber) {
    printf("Integer number: %i\n", intNumber);
}

void BPVPrintFloat(float floatNumber) {
    printf("Float number: %f\n", floatNumber);
}

void BPVPrintChar(char character) {
    printf ("Char: %c\n", character);
}

void BPVPrintString(char string[]) {
    printf ("Sting: %s\n", string);
}
