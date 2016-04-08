//
//  BPVRangeOfNumber.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVMathFunctions.h"

#include "BPVRangeOfNumber.h"

unsigned int BPVRangeOfNumber(int value1, int value2) {
    int maxValue = BPVMaxValue(value1, value2);
    int minValue = BPVMinValue(value1, value2);
    
    return maxValue - minValue;
}