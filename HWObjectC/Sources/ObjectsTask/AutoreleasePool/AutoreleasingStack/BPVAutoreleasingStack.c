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
void BPVAutoreleasingStackSetHead(BPVAutoreleasingStack *stack, void *head);

static
void *BPVAutoreleasingStackGetHead(BPVAutoreleasingStack *stack);

static
void BPVAutoreleasingStackSetSize(BPVAutoreleasingStack *stack, size_t size);

#pragma mark -
#pragma mark Public Implementations

void __BPVAutoreleasingStackDeallocate(void *stack) {
    BPVAutoreleasingStackSetHead(stack, NULL);
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
    BPVAutoreleasingStackSetHead(stack, BPVAutoreleasingStackGetData(stack));

    return stack;
}

bool BPVAutoreleasingStackIsFull(BPVAutoreleasingStack *stack) {
    if (!stack) {
        return false;
    }
    
    void **data = BPVAutoreleasingStackGetData(stack);
    size_t size = BPVAutoreleasingStackGetSize(stack);
    uint64_t count = size/sizeof(*data);
    
    return BPVAutoreleasingStackGetCount(stack) == count;
}

bool BPVAutoreleasingStackIsEmpty(BPVAutoreleasingStack *stack) {
    return stack && BPVAutoreleasingStackGetHead(stack) == BPVAutoreleasingStackGetData(stack);
}

void BPVAutoreleasingStackPushObject(BPVAutoreleasingStack *stack, void *object) {
    if (!stack) {
        return;
    }
    
    if (BPVAutoreleasingStackIsFull(stack)) {
        printf("This stack is full, object not added\n");
        return;
    }
    
    void **newHead = BPVAutoreleasingStackGetHead(stack) + 1;
    newHead = object;
    BPVAutoreleasingStackSetHead(stack, newHead);
    BPVAutoreleasingStackCountAddValue(stack, 1);
}

BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObject(BPVAutoreleasingStack *stack) {
    BPVAutoreleasingStackPopObjectType type = BPVAutoreleasingStackPopObjectTypeNone;
    if (stack) {
        void **head = BPVAutoreleasingStackGetHead(stack);
        void **previousObject = BPVAutoreleasingStackGetHead(stack) - 1;
        BPVAutoreleasingStackSetHead(stack, previousObject);
        type = head ? BPVAutoreleasingStackPopObjectTypeObject : BPVAutoreleasingStackPopObjectTypeNull;
        BPVAutoreleasingStackCountAddValue(stack, -1);
        
        BPVObjectRelease(head);
    }
    
    return type;
}

BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObjectsUntilNull(BPVAutoreleasingStack *stack) {
    BPVAutoreleasingStackPopObjectType type = BPVAutoreleasingStackPopObjectTypeNone;
    if (stack) {
        do {
            type = BPVAutoreleasingStackPopObject(stack);
        } while (!(BPVAutoreleasingStackPopObjectTypeNull == type || !BPVAutoreleasingStackIsEmpty(stack)));
    }
    
    return type;
}

void BPVAutoreleasingStackPopAllObjects(BPVAutoreleasingStack *stack) {
    if (stack) {
        do {
            BPVAutoreleasingStackPopObject(stack);
        } while (!BPVAutoreleasingStackIsEmpty(stack));
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
