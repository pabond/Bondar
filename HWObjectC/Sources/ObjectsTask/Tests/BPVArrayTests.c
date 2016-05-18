//
//  BPVArrayTests.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/15/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVArrayTests.h"
#include "BPVArray.h"
#include "BPVString.h"

void BPVRunArreyTests() {
    printf("test started\n");
    
    for (uint8_t iteration = 0; iteration < 100; iteration++) {
        BPVArray *array = BPVArrayCreateArrayWithCapacity(10);
        
        if (array) {
            printf("Arrey created\n");
        }
        
        BPVString *object = BPVStringCreate("test object");
        
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        BPVArrayAddObject(array, object);
        
        if (BPVArrayGetObjectAtIndex(array, 0)
            && BPVArrayGetObjectAtIndex(array, 1)
            && BPVArrayGetObjectAtIndex(array, 5)
            && BPVArrayGetObjectAtIndex(array, 9))
        {
            printf("Objectrs added to array\n");
        }
        
        BPVArrayRemoveObjectAtIndex(array, 9);
        BPVArrayRemoveObjectAtIndex(array, 8);
        BPVArrayRemoveObjectAtIndex(array, 7);
        BPVArrayRemoveObjectAtIndex(array, 6);
        BPVArrayRemoveObjectAtIndex(array, 5);
        BPVArrayRemoveObjectAtIndex(array, 4);
        BPVArrayRemoveObjectAtIndex(array, 3);
        BPVArrayRemoveObjectAtIndex(array, 2);
        BPVArrayRemoveObjectAtIndex(array, 1);
        BPVArrayRemoveObjectAtIndex(array, 0);
        
        if (BPVArrayGetCount(array)) {
            printf("count not empty\n");
        }
        
        __BPVArrayDeallocate(array);
        
        if (array) {
            printf("arrey not deleted\n");
        }
    }
    
    printf("test finished successfully\n");
}