//
//  BPVAutoreleasingStack.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/26/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVAutoreleasingStack.h"

#pragma mark -
#pragma mark Private Declarations

static
void **BPVAutoreleasingStackGetData(BPVAutoreleasingStack *stack);

static
void BPVAutoreleasingStackSetHead(BPVAutoreleasingStack *stack, void *head);

static
void *BPVAutoreleasingStackGetHead(BPVAutoreleasingStack *stack);

static
size_t BPVAutoreleasingStackGetSize(BPVAutoreleasingStack *stack);

static
void BPVAutoreleasingStackSetSize(BPVAutoreleasingStack *stack, size_t size);

#pragma mark -
#pragma mark Public Implementations

void __BPVAutoreleasingStackDeallocate(void *stack) {
    BPVAutoreleasingStackSetHead(stack, NULL);
    BPVAutoreleasingStackSetSize(stack, 0);
    
    __BPVObjectDeallocate(stack);
}

BPVAutoreleasingStack *BPVAutoreleasingStackCreateWithSize(size_t size) {
    if (!size) {
        return NULL;
    }
    
    BPVAutoreleasingStack *stack = BPVObjectCreateWithType(BPVAutoreleasingStack);
    
    BPVAutoreleasingStackSetSize(stack, size);
    BPVAutoreleasingStackSetHead(stack, BPVAutoreleasingStackGetData(stack));
    
    return stack;
}

bool BPVAutoreleasingStackIsFull(BPVAutoreleasingStack *stack) {
    if (!stack) {
        return false;
    }
    
    void **data = BPVAutoreleasingStackGetData(stack);
    void *head = BPVAutoreleasingStackGetHead(stack);
    uint64_t count = BPVAutoreleasingStackGetSize(stack)/sizeof(*data);
    
    return data[count - 1] <= head;
}

bool BPVAutoreleasingStackIsEmpty(BPVAutoreleasingStack *stack) {
    return stack && BPVAutoreleasingStackGetHead(stack) == BPVAutoreleasingStackGetData(stack);
}

void BPVAutoreleasingStackPushObject(BPVAutoreleasingStack *stack, void *object) {
    if (stack && BPVAutoreleasingStackIsFull(stack)) {
        
    }
}

BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObject(BPVAutoreleasingStack *stack);

BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObjectsUntilNull(BPVAutoreleasingStack *stack);

#pragma mark -
#pragma mark Private Implementations

void **BPVAutoreleasingStackGetData(BPVAutoreleasingStack *stack) {
    return stack ? stack->_data : NULL;
}

void BPVAutoreleasingStackSetHead(BPVAutoreleasingStack *stack, void *head) {
    if (stack) {
        stack->_head = head;
    }
}

void *BPVAutoreleasingStackGetHead(BPVAutoreleasingStack *stack) {
    return stack ? stack->_head : NULL;
}

size_t BPVAutoreleasingStackGetSize(BPVAutoreleasingStack *stack) {
    return stack ? stack->_size : 0;
}

void BPVAutoreleasingStackSetSize(BPVAutoreleasingStack *stack, size_t size) {
    if (stack) {
        stack->_size = size;
    }
}
