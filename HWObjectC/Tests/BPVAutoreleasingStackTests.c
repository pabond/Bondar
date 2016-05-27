//
//  BPVAutoreleasingStackTests.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/26/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVAutoreleasingStackTests.h"
#include "BPVAutoreleasingStack.h"

static const uint64_t kBPVStackSize = 64;

void BPVRunAutoreleasingStackTest() {
    BPVAutoreleasingStack *stack = BPVAutoreleasingStackCreateWithSize(kBPVStackSize);
    if (!BPVAutoreleasingStackGetCount(stack)) {
        printf("After creation count is 0\n");
    }
    
    if (1 == BPVObjectGetRetainCount(stack)) {
        printf("Retain count = 1\n");
    }
    
    if (kBPVStackSize == BPVAutoreleasingStackGetSize(stack)) {
        printf("Size is correct\n");
    }
    
    if (BPVAutoreleasingStackIsEmpty(stack) && !BPVAutoreleasingStackIsFull(stack)) {
        printf("Stack is empty\n");
    }
    
    

}