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

void BPVRunArrayTests() {
    printf("test started\n");
    
    uint8_t objectsCount = 10;
    
    for (uint8_t iteration = 0; iteration < 100; iteration++) {
        BPVArray *array = BPVArrayCreateArrayWithCapacity(0);
        
        printf("Retain count after array created: %llu\n", BPVObjectGetRetainCount(array));
        
        BPVObjectRetain(array);
        
        printf("Retain count after RETAIN: %llu\n", BPVObjectGetRetainCount(array));
        
        BPVObjectRelease(array);
        
        printf("Retain count after RELEASE: %llu\n", BPVObjectGetRetainCount(array));
        
        printf("Capacity after array created: %llu\n", BPVArrayGetCapacity(array));
        
        if (array) {
            printf("Arrey created\n");
        }
        
        BPVString *object = BPVStringCreate("test object");
        
        for (uint8_t iteration = 0; iteration < objectsCount; iteration++) {
            BPVArrayAddObject(array, object);
        }
        
        if (BPVArrayGetObjectAtIndex(array, 0)
            && BPVArrayGetObjectAtIndex(array, 1)
            && BPVArrayGetObjectAtIndex(array, 5)
            && BPVArrayGetObjectAtIndex(array, 9))
        {
            printf("%llu objectrs added to array\n", BPVArrayGetCount(array));
            printf("Capacity afterobjects added is %llu\n", BPVArrayGetCapacity(array));
        }
        
        for (uint8_t iteration = 0; iteration < objectsCount; iteration++) {
            BPVArrayRemoveObjectAtIndex(array, iteration);
        }
        
        printf("%llu objectrs in array after removing\n", BPVArrayGetCount(array));
        printf("Capacity after objects deleted: %llu\n", BPVArrayGetCapacity(array));
        
        BPVObjectRelease(array);
    }
    
    printf("test finished\n");
}