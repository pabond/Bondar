//
//  BPVDevideCode.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVDevideCode.h"

#include "BPVMathFunctions.h"

#include "BPVPrintDataType.h"

void BPVDevideCode() {
    double doubleResult = 3.0;
    int result = BPVMultiply(doubleResult, doubleResult);
    result = BPVDevide(result, 4);
    result = BPVDevideWithoutReminder(result, 7);
    doubleResult = BPVMultiply(doubleResult, 4);
    doubleResult = BPVMinus(doubleResult, 1.5f);
    doubleResult = BPVAdd(doubleResult, 'A');
    result = BPVAdd(result, doubleResult);
    BPVPrintInt(result);
}
