//
//  BPVRunApplication.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/11/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVRunApplication.h"

#include "BPVPrintDataType.h"

#include "BPVMacrosTask.h"

#include "BPVStructureTask.h"


void BPVRunApplication() {
    BPVPrintDataType();
    BPVPrintTypeUsingMacros();
    BPVPrintOffsetofValue();
}