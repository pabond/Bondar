//
//  main.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVPrintDataType.h"

#include "BPVPlusMinusOne.h"

#include "BPVMathFunctions.h"

#include "BPVDevideCode.h"

int main(int argc, const char * argv[]) {
    BPVPrintRangeOfNumber(57, -250);
    BPVPrintDataTypesMathTest();
    BPVPrintFloat(3 * 3 / 4 % 7 + 4 * 3 - 1.5 + 65);
    BPVPrinDataType();
    BPVPrintInt(BPVDecrement(5));
    BPVPrintInt(BPVIncrement(10));
    BPVDevideCode();
    
    return 0;
}
