//
//  BPVBoolFunctions.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVBoolFunctions.h"

#include "BPVMathFunctions.h"

#include "BPVPrintDataType.h"

void BPVBoolValue(bool value) {
    value ? BPVPrintBool(true)  : BPVPrintBool(false);
}

void BPVBoolMathOperations(int value1, int value2) {
    bool result = value1 < value2;
    BPVPrintBool(result);
    result = value1 > value2;
    BPVPrintBool(result);
    result = value1 == value2;
    BPVPrintBool(result);
    result = value1 -2 <= value2;
    BPVPrintBool(result);
    result = value1 -2 >= value2;
    BPVPrintBool(result);
    result ? BPVPrintString("Mom") : BPVPrintString("Dad");
    
    if(value1 > value2) {
        BPVPrintString("Mom");
    } else {
        BPVPrintString("Dad");
    }
   /*
    when we write if(value1 = 5) we can see tip fow to fix it, when we write if(5 = value1) proram will not build
    
    if(value1 = 5) {
        BPVPrintBool(result);
    }
    */
}