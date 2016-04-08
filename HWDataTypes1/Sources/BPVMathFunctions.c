//
//  BPVMathFunctions.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVMathFunctions.h"

#include <stdio.h>

int BPVMaxValue(int value1, int value2) {
    return (value1 > value2) ? value1 : value2;
}

int BPVMinValue(int value1, int value2) {
    return (value1 < value2) ? value1 : value2;
}