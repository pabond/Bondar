//
//  BPVDeputy.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVDeputy.h"

#include "BPVPrintDataType.h"



typedef enum {
    BPVDetupyPeculator,
    BPVDeputyRelativelyFair,
    BPVDeputyAngel,
    BPVDeputyDead,
} BPVDeputyType;

static
void BPVPrintDeputyType(deputyType) {
    
    switch (deputyType) {
        case BPVDetupyPeculator:
            puts("This deputy is a peculator");
            break;
            
        case BPVDeputyRelativelyFair:
            puts("This deputy is relatively fair");
            break;
            
        case BPVDeputyAngel:
            puts("This deputy is an angel");
            break;
            
        case BPVDeputyDead:
        default:
            puts("This deputy is dead");
            break;
            
    }
}

void BPVDeputySalary(BPVDeputyType deputyType) {
    long salary = 100000000;
    long selfProperty = 100000000000000;
    
    if (selfProperty >= salary * 1000 * 1000) {
        deputyType = BPVDetupyPeculator;
    } else if (selfProperty >= salary * 120) {
        deputyType = BPVDeputyRelativelyFair;
    } else if (selfProperty >= salary * 12) {
        deputyType = BPVDeputyAngel;
    } else {
        deputyType = BPVDeputyDead;
    }
    
    BPVPrintDeputyType(deputyType);
}

