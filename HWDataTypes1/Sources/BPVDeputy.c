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
    BPVPeculator,
    BPVRelativelyFair,
    BPVAngel,
    BPVDead,
} BPVEntity;

void BPVDeputySalary(BPVEntity entity) {
    long salary = 90000000;
    long selfProperty = 90000000000000;
    
    if(selfProperty == salary * 1000 * 1000) {
        entity = BPVPeculator;
    } else if (selfProperty == salary * 120) {
        entity = BPVRelativelyFair;
    } else if (selfProperty == salary * 120) {
        entity = BPVAngel;
    } else {
        entity = BPVDead;
    }
    
    switch (entity) {
        case BPVPeculator:
            puts("This deputy is peculator");
            break;
        case BPVRelativelyFair:
            puts("This deputy is relatively fair");
            break;
        case BPVAngel:
            puts("This deputy is angel");
            break;
        case BPVDead:
        default:
            puts("This deputy die");
            break;
    }
}