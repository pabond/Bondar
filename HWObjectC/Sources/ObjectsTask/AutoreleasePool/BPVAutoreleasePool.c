//
//  BPVAutoreleasePool.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/28/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <string.h>

#include "BPVAutoreleasePool.h"
#include "BPVAutoreleasingStack.h"
#include "BPVLinkedListNode.h"
#include "BPVArray.h"
#include "BPVLinkedList.h"
#include "BPVLinkedListPrivate.h"

static const uint64_t kBPVStackSize = 64;

static BPVAutoreleasePool *__autoreleasePool = NULL;

#pragma mark -
#pragma mark Private Declarations

static
void BPVAutoreleasePoolDrainAll(BPVAutoreleasePool *pool);

static
BPVAutoreleasingStack *BPVAutoreleasePoolNewStack(BPVAutoreleasePool *pool);

static
BPVAutoreleasingStack *BPVAutoreleasePoolAddStackToList(BPVAutoreleasePool *pool);

static
void BPVAutoreleasePoolSetPoolsCount(BPVAutoreleasePool *pool, uint64_t value);

static
BPVLinkedList *BPVAutoreleasePoolSetLinkedList(BPVAutoreleasePool *pool);

static
void BPVAutoreleasePoolPoolsCountAddValue(BPVAutoreleasePool *pool, int64_t value);

static
void BPVAutoreleasePoolFindEmptySteksToResizePool(BPVAutoreleasePool *pool);

#pragma mark -
#pragma mark Public Implementations

void __BPVAutoreleasePoolDeallocate(BPVAutoreleasePool *pool) {
    BPVAutoreleasePoolDrainAll(pool);
    BPVObjectRelease(BPVAutoreleasePoolGetLinkedList(pool));
    
    __BPVObjectDeallocate(pool);
}

BPVAutoreleasePool *BPVAutoreleasePoolCreateWithListAndStack() {
    if (!__autoreleasePool) {
        __autoreleasePool = BPVObjectCreateWithType(BPVAutoreleasePool);
        BPVAutoreleasePoolSetLinkedList(__autoreleasePool);
        BPVAutoreleasePoolAddStackToList(__autoreleasePool);
    }
    
    BPVAutoreleasePoolAddObject(__autoreleasePool, NULL);
    BPVAutoreleasePoolPoolsCountAddValue(__autoreleasePool, 1);
    
    return __autoreleasePool;
}

BPVAutoreleasePool *BPVAutoreleasePoolGetPool() {
    return __autoreleasePool;
}

bool BPVAutoreleasePoolIsValid(BPVAutoreleasePool *pool) {
    return pool && BPVAutoreleasePoolGetPoolsCount(pool);
}

void BPVAutoreleasePoolDrain(BPVAutoreleasePool *pool) {
    if (!pool && !BPVAutoreleasePoolIsValid(pool)) {
        return;
    }
    
    BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
    void *object = BPVLinkedListGetFirstObject(list);
    BPVAutoreleasingStackPopObjectType type = BPVAutoreleasingStackPopObjectTypeNone;
    
    do {
        type =  BPVAutoreleasingStackPopObjects((BPVAutoreleasingStack *)object);
        object = BPVLinkedListGetObjectAfterObject(list, object);
    } while (type != BPVAutoreleasingStackPopObjectTypeNull);
    
    BPVAutoreleasePoolPoolsCountAddValue(pool, -1);
    BPVAutoreleasePoolFindEmptySteksToResizePool(pool);
}

uint64_t BPVAutoreleasePoolGetPoolsCount(BPVAutoreleasePool *pool) {
    return pool ? pool->_poolsCount : 0;
}

BPVLinkedList *BPVAutoreleasePoolGetLinkedList(BPVAutoreleasePool *pool) {
    return pool ? pool->_list : NULL;
}

void BPVAutoreleasePoolAddObject(BPVAutoreleasePool *pool, void *object) {
    if (!pool) {
        return;
    }
    
    BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
    void *stackObject = BPVLinkedListGetFirstObject(list);
    BPVAutoreleasingStack *stack = (BPVAutoreleasingStack *)stackObject;
    
    if (BPVAutoreleasingStackIsFull(stack)) {
        stack = BPVAutoreleasePoolAddStackToList(pool);
    }

    if (BPVAutoreleasingStackIsEmpty(stack)) {
        stackObject = BPVLinkedListGetObjectAfterObject(list, stackObject);
        if (stackObject) {
            BPVAutoreleasingStack *nextStack = (BPVAutoreleasingStack *)stackObject;
            stack = BPVAutoreleasingStackIsFull(nextStack) ? stack : nextStack;
        }
    }
    
    BPVAutoreleasingStackPushObject(stack, object);
}

BPVAutoreleasingStack *BPVAutoreleasePoolGetFirstAutoreleasingStack(BPVAutoreleasePool *pool) {
    if (!pool) {
        return NULL;
    }
    
    BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
    void *stackObject = BPVLinkedListGetFirstObject(list);
    
    return (BPVAutoreleasingStack *)stackObject;
}

BPVAutoreleasingStack *BPVAutoreleasePoolGetLastAutoreleasingStack(BPVAutoreleasePool *pool) {
    if (!pool) {
        return NULL;
    }
    
    BPVAutoreleasingStack *stack = BPVAutoreleasePoolGetFirstAutoreleasingStack(pool);
    BPVAutoreleasingStack *nextStack = BPVAutoreleasePoolGetNextAutoreleasingStack(pool, stack);
    while (nextStack) {
        stack = nextStack;
        nextStack = BPVAutoreleasePoolGetNextAutoreleasingStack(pool, stack);
    }
    
    return stack;
}

BPVAutoreleasingStack *BPVAutoreleasePoolGetNextAutoreleasingStack(BPVAutoreleasePool *pool, void *stack) {
    return pool && stack ? BPVLinkedListGetObjectAfterObject(BPVAutoreleasePoolGetLinkedList(pool), stack) : NULL;
}

#pragma mark -
#pragma mark Private Implementations

void BPVAutoreleasePoolDrainAll(BPVAutoreleasePool *pool) {
    do {
        BPVAutoreleasePoolDrain(pool);
    } while (BPVAutoreleasePoolIsValid(pool));
    
    BPVAutoreleasePoolFindEmptySteksToResizePool(pool);
}

BPVAutoreleasingStack *BPVAutoreleasePoolAddStackToList(BPVAutoreleasePool *pool) {
    BPVAutoreleasingStack *stack = BPVAutoreleasePoolNewStack(pool);
    BPVLinkedListAddObject(BPVAutoreleasePoolGetLinkedList(pool), stack);
    
    BPVObjectRelease(stack);
    
    return stack;
}

bool BPVAutoreleasePoolDeleteEmptySteks(BPVArray *accumulator, BPVAutoreleasingStack *stack, BPVAutoreleasingStack *nextStack) {
    if (BPVAutoreleasingStackIsEmpty(stack) && BPVAutoreleasingStackIsEmpty(nextStack)) {
        BPVArrayAddObject(accumulator, stack);
    } else {
        BPVArrayRemoveAllObjects(accumulator);
        BPVObjectRelease(accumulator);
        return true;
    }
    
    return false;
}

void BPVAutoreleasePoolFindEmptySteksToResizePool(BPVAutoreleasePool *pool) {
    if (!pool) {
        return;
    }
    
    BPVLinkedList *list = BPVAutoreleasePoolGetLinkedList(pool);
    BPVLinkedListContext context;
    memset(&context, 0, sizeof(context));
    
    BPVArray *array = BPVArrayCreateArrayWithCapacity(0);
    
    context.accumulator = array;
    context.comparator = BPVAutoreleasePoolDeleteEmptySteks;
    
    BPVLinkedListGetObjectWithContext(list, BPVWrapperContext, &context);
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

BPVAutoreleasingStack *BPVAutoreleasePoolNewStack(BPVAutoreleasePool *pool) {
    return pool ? BPVAutoreleasingStackCreateWithSize(kBPVStackSize) : NULL;
}

void BPVAutoreleasePoolSetPoolsCount(BPVAutoreleasePool *pool, uint64_t value) {
    if (pool) {
        pool->_poolsCount = value;
    }
}

void BPVAutoreleasePoolPoolsCountAddValue(BPVAutoreleasePool *pool, int64_t value) {
    if (pool && value) {
        BPVAutoreleasePoolSetPoolsCount(pool, BPVAutoreleasePoolGetPoolsCount(pool) + value);
    }
}
