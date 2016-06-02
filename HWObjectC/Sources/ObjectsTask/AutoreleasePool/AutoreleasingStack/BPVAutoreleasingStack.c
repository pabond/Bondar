//
//  BPVAutoreleasingStack.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/26/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVAutoreleasingStack.h"

#pragma mark -
#pragma mark Private Declarations

static
void BPVAutoreleasingStackSetCount(BPVAutoreleasingStack *stack, uint64_t count);

static
void BPVAutoreleasingStackCountAddValue(BPVAutoreleasingStack *stack, int64_t value);

static
void BPVAutoreleasingStackSetObject(BPVAutoreleasingStack *stack, void *object);

static
void BPVAutoreleasingStackSetSize(BPVAutoreleasingStack *stack, size_t size);

#pragma mark -
#pragma mark Public Implementations

void __BPVAutoreleasingStackDeallocate(void *stack) {
    BPVAutoreleasingStackPopAllObjects(stack);
    BPVAutoreleasingStackSetSize(stack, 0);
    BPVAutoreleasingStackSetCount(stack, 0);
    
    __BPVObjectDeallocate(stack);
}

BPVAutoreleasingStack *BPVAutoreleasingStackCreateWithSize(size_t size) {
    if (!size) {
        return NULL;
    }
    
    BPVAutoreleasingStack *stack = BPVObjectCreateWithType(BPVAutoreleasingStack);
    BPVAutoreleasingStackSetSize(stack, size);
    BPVAutoreleasingStackSetCount(stack, 0);

    return stack;
}

bool BPVAutoreleasingStackIsFull(BPVAutoreleasingStack *stack) {
    if (!stack) {
        return false;
    }
    
    void **data = BPVAutoreleasingStackGetData(stack);
    size_t size = BPVAutoreleasingStackGetSize(stack);
    uint64_t count = size / sizeof(*data);
    
    return BPVAutoreleasingStackGetCount(stack) == count;
}

bool BPVAutoreleasingStackIsEmpty(BPVAutoreleasingStack *stack) {
    return stack && BPVAutoreleasingStackGetCount(stack) == 0;
}

void BPVAutoreleasingStackPushObject(BPVAutoreleasingStack *stack, void *object) {
    if (!stack) {
        return;
    }
    
    if (BPVAutoreleasingStackIsFull(stack)) {
        printf("This stack is full, object not added\n");
        return;
    }
    
    BPVAutoreleasingStackSetObject(stack, object);
    BPVAutoreleasingStackCountAddValue(stack, 1);
}

BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObject(BPVAutoreleasingStack *stack) {
    BPVAutoreleasingStackPopObjectType type = BPVAutoreleasingStackPopObjectTypeNone;
    if (stack) {
        void *object = *(stack->_data + (BPVAutoreleasingStackGetCount(stack) - 1));
        type = object ? BPVAutoreleasingStackPopObjectTypeObject : BPVAutoreleasingStackPopObjectTypeNull;
        BPVAutoreleasingStackSetObject(stack, NULL);
        BPVAutoreleasingStackCountAddValue(stack, -1);
    }
    
    return type;
}

BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObjects(BPVAutoreleasingStack *stack) {
    BPVAutoreleasingStackPopObjectType type = BPVAutoreleasingStackPopObjectTypeNone;
    if (stack && !BPVAutoreleasingStackIsEmpty(stack)) {
        do {
            type = BPVAutoreleasingStackPopObject(stack);
        } while (BPVAutoreleasingStackPopObjectTypeNull != type && !BPVAutoreleasingStackIsEmpty(stack));
    }
    
    return type;
}

void BPVAutoreleasingStackPopAllObjects(BPVAutoreleasingStack *stack) {
    if (stack) {
        while (!BPVAutoreleasingStackIsEmpty(stack)) {
            BPVAutoreleasingStackPopObject(stack);
        }
    }
}


#pragma mark -
#pragma mark Private Implementations

void **BPVAutoreleasingStackGetData(BPVAutoreleasingStack *stack) {
    return stack ? stack->_data : NULL;
}

void BPVAutoreleasingStackSetCount(BPVAutoreleasingStack *stack, uint64_t count) {
    if (stack) {
        stack->_count = count;
    }
}

uint64_t BPVAutoreleasingStackGetCount(BPVAutoreleasingStack *stack) {
    return stack ? stack->_count : 0;
}

void BPVAutoreleasingStackCountAddValue(BPVAutoreleasingStack *stack, int64_t value) {
    if (stack && value) {
        BPVAutoreleasingStackSetCount(stack, BPVAutoreleasingStackGetCount(stack) + value);
    }
}

void BPVAutoreleasingStackSetObject(BPVAutoreleasingStack *stack, void *object) {
    if (stack) {
        if (!object) {
            BPVObjectRelease(*(stack->_data + (BPVAutoreleasingStackGetCount(stack) - 1)));
        }
        
        *(stack->_data + BPVAutoreleasingStackGetCount(stack)) = object;
    }
}

size_t BPVAutoreleasingStackGetSize(BPVAutoreleasingStack *stack) {
    return stack ? stack->_size : 0;
}

void BPVAutoreleasingStackSetSize(BPVAutoreleasingStack *stack, size_t size) {
    if (stack) {
        if (stack->_size != size) {
            free(stack->_data);
        }
        
        if (size) {
            stack->_data = calloc(1, size);
        }
        
        stack->_size = size;
    }
}
