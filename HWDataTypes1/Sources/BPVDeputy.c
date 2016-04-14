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
} BPVDeputyEntity;

void BPVDeputySalary(BPVDeputyEntity entity) {
    long salary = 100000000;
    long selfProperty = 100000000000000;
    
    if (selfProperty >= salary * 1000 * 1000) {
        entity = BPVDetupyPeculator;
    } else if (selfProperty < salary * 1000 * 1000 && selfProperty >= salary * 120) {
        entity = BPVDeputyRelativelyFair;
    } else if (selfProperty < salary * 120 && selfProperty >= salary * 12) {
        entity = BPVDeputyAngel;
    } else {
        entity = BPVDeputyDead;
    }
    
    switch (entity) {
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
