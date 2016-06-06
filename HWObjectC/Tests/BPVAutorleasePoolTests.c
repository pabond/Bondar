//
//  BPVAutorleasePoolTests.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/30/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVAutorleasePoolTests.h"
#include "BPVAutoreleasePool.h"
#include "BPVAutoreleasingStack.h"

void BPVRunAutoreleasePoolTest() {
    
    BPVAutoreleasePool *pool = BPVAutoreleasePoolCreateWithListAndStack();
    
    if (pool && BPVAutoreleasePoolIsValid(pool)) {
        printf("Pool created & pool is valid\n");
    }
    
    if (BPVAutoreleasePoolGetFirstAutoreleasingStack(pool)) {
        printf("stack valid\n");
    }
    
    if (!BPVAutoreleasingStackIsEmpty(BPVAutoreleasePoolGetFirstAutoreleasingStack(pool))) {
        printf("stack not empty\n");
    }
    
    BPVObject *object = BPVObjectCreateWithType(BPVObject);
    
    if (object) {
        printf("Object created\n");
    }
    
     BPVAutoreleasePoolAddObject(pool, object);
    
    printf("%llu\n", BPVAutoreleasingStackGetCount(BPVAutoreleasePoolGetFirstAutoreleasingStack(pool)));
    
    for (uint8_t count = 0; count < 4; count++) {
        BPVAutoreleasePoolAddObject(pool, object);
    }
    
    printf("test runing\n");
    
    BPVAutoreleasePoolDrain(pool);
    
    if (!BPVAutoreleasePoolIsValid(pool)) {
        printf("Pool is not valid after drain\n");
    }
}
