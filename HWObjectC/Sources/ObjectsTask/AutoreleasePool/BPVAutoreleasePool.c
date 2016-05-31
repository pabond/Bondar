//
//  BPVAutoreleasePool.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/28/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVAutoreleasePool.h"
#include "BPVAutoreleasingStack.h"

static const uint64_t kBPVStackSize = 64;

BPVAutoreleasePool *autoreleasePool = NULL;

#pragma mark -
#pragma mark Private Declarations

static
void BPVAutoreleasePoolDrainAll(BPVAutoreleasePool *pool);

static
void BPVAutoreleasePoolDeleteEmptyStacks(BPVAutoreleasePool *pool);

static
BPVAutoreleasingStack *BPVAutoreleasePoolNewStack(BPVAutoreleasePool *pool);

static
BPVAutoreleasingStack *BPVAutoreleasePoolAddStackToList(BPVAutoreleasePool *pool);

static
void BPVAutoreleasePoolSetCount(BPVAutoreleasePool *pool, uint64_t value);

static
void BPVAutoreleasePoolCountAddValue(BPVAutoreleasePool *pool, int64_t value);

#pragma mark -
#pragma mark Public Implementations

void __BPVAutoreleasePoolDeallocate(BPVAutoreleasePool *pool) {
    BPVAutoreleasePoolDrainAll(pool);
    BPVObjectRelease(pool->_list);
    
    __BPVObjectDeallocate(pool);
}

BPVAutoreleasePool *BPVAutoreleasePoolCreateWithListAndStack() {
    if (!autoreleasePool) {
        autoreleasePool = BPVObjectCreateWithType(BPVAutoreleasePool);
        BPVAutoreleasePoolSetLinkedList(autoreleasePool);
        BPVAutoreleasePoolAddStackToList(autoreleasePool);
    }
    
    BPVAutoreleasePoolAddObject(autoreleasePool, NULL);
    BPVAutoreleasePoolCountAddValue(autoreleasePool, 1);
    
    return autoreleasePool;
}

bool BPVAutoreleasePoolIsValid(BPVAutoreleasePool *pool) {
    return BPVAutoreleasePoolGetCount(pool);
}

void BPVAutoreleasePoolDrain(BPVAutoreleasePool *pool) {
    if (pool && BPVAutoreleasePoolIsValid(pool)) {
        BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
        void *object = BPVLinkedListGetFirstObject(list);
        BPVAutoreleasingStackPopObjectType type = BPVAutoreleasingStackPopObjectTypeNone;
        
        do {
            type =  BPVAutoreleasingStackPopObjectsUntilNull((BPVAutoreleasingStack *)object);
            object = BPVLinkedListGetObjectAfterObject(list, object);
        } while (type != BPVAutoreleasingStackPopObjectTypeNull);
        
        BPVAutoreleasePoolCountAddValue(pool, -1);
        BPVAutoreleasePoolDeleteEmptyStacks(pool);
    }
}

uint64_t BPVAutoreleasePoolGetCount(BPVAutoreleasePool *pool) {
    return pool ? pool->_poolsCount : 0;
}

BPVLinkedList *BPVAutoreleasePoolSetLinkedList(BPVAutoreleasePool *pool) {
    if (!pool) {
        return NULL;
    }
    
    BPVLinkedList *list = BPVLinkedListCreate();
    BPVStrongSetter(pool, _list, list);
    
    BPVObjectRelease(list);
    
    return list;
}

BPVLinkedList *BPVAutoreleasePoolGetLinkedList(BPVAutoreleasePool *pool) {
    return pool ? pool->_list : NULL;
}

void BPVAutoreleasePoolAddObject(BPVAutoreleasePool *pool, void *object) {
    if (pool) {
        BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
        void *object = BPVLinkedListGetFirstObject(list);
        BPVAutoreleasingStack *stack = (BPVAutoreleasingStack *)object;
        
        if (BPVAutoreleasingStackIsFull(stack)) {
            stack = BPVAutoreleasePoolAddStackToList(pool);
        }

        if (BPVAutoreleasingStackIsEmpty(stack)) {
            object = BPVLinkedListGetObjectAfterObject(list, object);
            if (object) {
                BPVAutoreleasingStack *nextStack = (BPVAutoreleasingStack *)object;
                stack = BPVAutoreleasingStackIsFull(nextStack) ? stack : nextStack;
            }
        }
        
        BPVAutoreleasingStackPushObject(stack, object);
    }
}

#pragma mark -
#pragma mark Private Implementations

void BPVAutoreleasePoolDrainAll(BPVAutoreleasePool *pool) {
    do {
        BPVAutoreleasePoolDrain(pool);
    } while (BPVAutoreleasePoolIsValid(pool));
    
    BPVAutoreleasePoolDeleteEmptyStacks(pool);
}

BPVAutoreleasingStack *BPVAutoreleasePoolAddStackToList(BPVAutoreleasePool *pool) {
    BPVAutoreleasingStack *stack = BPVAutoreleasePoolNewStack(pool);
    BPVLinkedListAddObject(BPVAutoreleasePoolGetLinkedList(pool), stack);
    
    BPVObjectRelease(stack);
    
    return stack;
}

void BPVAutoreleasePoolDeleteEmptyStacks(BPVAutoreleasePool *pool) {
    if (pool) {
        BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
        void *object = BPVLinkedListGetFirstObject(list);
        BPVAutoreleasingStack *stack = (BPVAutoreleasingStack *)object;
        while (BPVAutoreleasingStackIsEmpty(stack)) {
            BPVAutoreleasingStack *previousStack = stack;
            object = BPVLinkedListGetObjectAfterObject(list, object);
            stack = (BPVAutoreleasingStack *)object;
            if (BPVAutoreleasingStackIsEmpty(stack)) {
                BPVLinkedListRemoveObject(list, previousStack);
            }
        }
    }
}

BPVAutoreleasingStack *BPVAutoreleasePoolNewStack(BPVAutoreleasePool *pool) {
    return pool ? BPVAutoreleasingStackCreateWithSize(kBPVStackSize) : NULL;
}

void BPVAutoreleasePoolSetCount(BPVAutoreleasePool *pool, uint64_t value) {
    if (pool) {
        pool->_poolsCount = value;
    }
}

void BPVAutoreleasePoolCountAddValue(BPVAutoreleasePool *pool, int64_t value) {
    if (pool && value) {
        BPVAutoreleasePoolSetCount(pool, BPVAutoreleasePoolGetCount(pool) + value);
    }
}
