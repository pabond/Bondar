//
//  BPVRunApplication.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/9/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVRunApplication.h"

#include "BPVPrintDataType.h"

#include "BPVMathFunctions.h"

#include "BPVDivideCode.h"

#include "BPVBoolFunctions.h"

#include "BPVDeputy.h"

#include "BPVArrayInit.h"

#include "BPVStringTest.h"

#include "BPVLoopsTest.h"

#include "BPVMamaPapa.h"

void BPVLauncher() {
    BPVPrintNumberRange(57, -250);
    BPVPrintDataTypesMathTest();
    BPVPrintFloat(3 * 3 / 4 % 7 + 4 * 3 - 1.5 + 65);
    BPVPrinDataType();
    BPVDivideCode();
    BPVBoolValue(true);
    BPVBoolMathOperations(5, 3);
    BPVPrintWithPuts();         // puts prints char with \n
    BPVDeputySalary();
    BPVArrayTest();
    BPVStrings();
    BPVPrintNumberRangeTimes(5, 500, 520);
    BPVConditionFunction(335);
}
