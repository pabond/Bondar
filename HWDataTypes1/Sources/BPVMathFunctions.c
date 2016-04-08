//
//  BPVMathFunctions.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVMathFunctions.h"

int BPVMaxValue(int value1, int value2) {
    return (value1 > value2) ? value1 : value2;
}

int BPVMinValue(int value1, int value2) {
    return (value1 < value2) ? value1 : value2;
}

int BPVMultiply(int value1, int value2) {
    return value1 * value2;
}

int BPVDevide(int value1, int value2) {
    return value1 / value2;
}

int BPVAdd(int value1, int value2) {
    return value1 + value2;
}

int BPVMinus(int value1, int value2) {
    return value1 - value2;
}

int BPVDevideWithoutReminder(int value1, int value2) {
    return value1 % value2;
}
