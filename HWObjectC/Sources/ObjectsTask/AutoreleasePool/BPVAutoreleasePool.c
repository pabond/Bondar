//
//  BPVAutoreleasePool.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/28/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVAutoreleasePool.h"
#include "BPVAutoreleasingStack.h"
#include "BPVLinkedList.h"

#pragma mark -
#pragma mark Private Declarations

static
void BPVAutoreleasePoolPopAll(BPVLinkedList *list);

static
void BPVAutoreleasePoolResize(BPVAutoreleasePool *pool);

static
BPVAutoreleasingStack *BPVAutoreleasePoolAddStack(BPVAutoreleasePool *pool);

static
void BPVAutoreleasePoolSetCount(BPVAutoreleasePool *pool, uint64_t value);

static
void BPVAutoreleasePoolCountAddValue(BPVAutoreleasePool *pool, uint64_t value);

#pragma mark -
#pragma mark Public Implementations

void __BPVAutoreleasePoolDeallocate(BPVAutoreleasePool *pool) {
    BPVAutoreleasePoolSetLinkedList(pool, NULL);
    BPVAutoreleasePoolSetCount(pool, 0);
    
    __BPVObjectDeallocate(pool);
}

BPVAutoreleasePool *BPVAutoreleasePoolCreateWithListAndStack() {
    BPVAutoreleasePool *pool = BPVObjectCreateWithType(BPVAutoreleasePool);
    BPVLinkedList *list = BPVLinkedListCreate();
    BPVAutoreleasingStack *stack = BPVAutoreleasingStackCreateWithSize(64);
    BPVAutoreleasePoolSetLinkedList(pool, list);
    BPVLinkedListAddObject(list, stack);
    
    return pool;
}

bool BPVAutoreleasePoolIsValid(BPVAutoreleasePool *pool) {
    return BPVAutoreleasingStackIsEmpty(BPVLinkedListGetFirstObject(BPVAutoreleasePoolGetLinkedList(pool)));
}

void BPVAutoreleasePoolDrain(BPVAutoreleasePool *pool);

uint64_t BPVAutoreleasePoolGetCount(BPVAutoreleasePool *pool);

#pragma mark -
#pragma mark Private Implementations

void BPVAutoreleasePoolPopAll(BPVLinkedList *list);

void BPVAutoreleasePoolResize(BPVAutoreleasePool *pool);

BPVAutoreleasingStack *BPVAutoreleasePoolAddStack(BPVAutoreleasePool *pool);

void BPVAutoreleasePoolSetCount(BPVAutoreleasePool *pool, uint64_t value);

void BPVAutoreleasePoolCountAddValue(BPVAutoreleasePool *pool, uint64_t value);
