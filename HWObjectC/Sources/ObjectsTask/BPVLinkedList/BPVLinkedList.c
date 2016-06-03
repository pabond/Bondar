//
//  BPVLinkedList.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <String.h>

#include "BPVLinkedList.h"
#include "BPVLinkedListEnumerator.h"
#include "BPVLinkedListNode.h"
#include "BPVLinkedListPrivate.h"
#include "BPVLinkedListEnumeratorPrivate.h"
#include "BPVArray.h"
#include "BPVAutoreleasingStack.h"

#pragma mark -
#pragma mark Private Declarations

static
void BPVLinkedListSetCount(BPVLinkedList *list, uint64_t value);

static
void BPVLinkedListCountAddValue(BPVLinkedList *list, int8_t value);

static
void BPVLinkedListIncrementMutationsCount(BPVLinkedList *list);

#pragma mark -
#pragma mark Public Implementations

void __BPVLinkedListDeallocate(BPVLinkedList *list) {
    BPVLinkedListSetHead(list, NULL);
    
    __BPVObjectDeallocate(list);
}

BPVLinkedList *BPVLinkedListCreate() {
    return BPVObjectCreateWithType(BPVLinkedList);
}

BPVLinkedListEnumerator *BPVLinkedListEnumeratorCreateFromList(BPVLinkedList *list) {
    return BPVLinkedListEnumeratorCreateWithList(list);
}

BPVObject *BPVLinkedListGetFirstObject(BPVLinkedList *list) {
    if (!list) {
        return NULL;
    }
    
    BPVLinkedListNode *node = BPVLinkedListGetHead(list);

    return BPVLinkedListNodeGetObject(node);
}

void BPVLinkedListRemoveFirstObject(BPVLinkedList *list) {
    if (list) {
        BPVLinkedListNode *node = BPVLinkedListGetHead(list);
        BPVLinkedListSetHead(list, BPVLinkedListNodeGetNextNode(node));
        BPVLinkedListCountAddValue(list, -1);
    }
}

BPVObject *BPVLinkedListGetNextObject(BPVLinkedList *list, BPVLinkedListNode *node) {
    if (list && node) {
        return BPVLinkedListNodeGetObject(BPVLinkedListNodeGetNextNode(node));
    }
    
    return NULL;
}


void *BPVLinkedListGetObjectBeforeObject(BPVLinkedList *list, void *object) {
    if (!list) {
        return NULL;
    }
    
    BPVLinkedListNodeContext context;
    memset(&context, 0, sizeof(context));
    context.object = object;
    
    BPVLinkedListNodeGetNodeWithContext(list, BPVLinkedListNodeContainsObject, &context);
    
    void *previousObject =BPVLinkedListNodeGetObject(context.previousNode);
    
    return previousObject;
}

void *BPVLinkedListGetObjectAfterObject(BPVLinkedList *list, void *object) {
    if (!list) {
        return NULL;
    }
    
    BPVLinkedListNodeContext context;
    memset(&context, 0, sizeof(context));
    context.object = object;
    
    BPVLinkedListNode *node = BPVLinkedListNodeGetNodeWithContext(list, BPVLinkedListNodeContainsObject, &context);
    
    return BPVLinkedListGetNextObject(list, node);
}

bool BPVLinkedListIsEmpty(BPVLinkedList *list) {
    return !list || !BPVLinkedListGetHead(list);
}

void BPVLinkedListAddObject(BPVLinkedList *list, void *object) {
    if (list) {
        BPVLinkedListNode *node = BPVLinkedListNodeCreateWithObject(object);
        BPVLinkedListNodeSetNextNode(node, BPVLinkedListGetHead(list));
        
        BPVLinkedListSetHead(list, node);
        BPVLinkedListCountAddValue(list, 1);
        BPVObjectRelease(node);
    }
}

void BPVLinkedListRemoveObject(BPVLinkedList *list, void *object) {
    if (list && object) {
        BPVLinkedListNode *head = BPVLinkedListGetHead(list);
        
        BPVLinkedListNodeContext context;
        memset(&context, 0, sizeof(context));
        context.object = object;
        
        BPVLinkedListNode *node = BPVLinkedListNodeGetNodeWithContext(list, BPVLinkedListNodeContainsObject, &context);
        
        if (node) {
            if (node == head) {
                BPVLinkedListSetHead(list, BPVLinkedListNodeGetNextNode(node));
            } else {
                BPVLinkedListNodeSetNextNode(context.previousNode, BPVLinkedListNodeGetNextNode(node));
                BPVLinkedListCountAddValue(list, -1);
            }
        }
    }
}

void BPVLinkedListRemoveAllObjects(BPVLinkedList *list) {
    if (list) {
        BPVLinkedListSetHead(list, NULL);
        BPVLinkedListSetCount(list, 0);
    }
}

bool BPVLinkedListContainsObject(BPVLinkedList *list, void *object) {
    BPVLinkedListNode *node = NULL;
    if (!list) {
        return false;
    }
    
    BPVLinkedListNodeContext context;
    memset(&context, 0, sizeof(context));
    context.object = object;
    node = BPVLinkedListNodeGetNodeWithContext(list, BPVLinkedListNodeContainsObject, &context);
    
    return (bool)node;
}

uint64_t BPVLinkedListGetCount(BPVLinkedList *list) {
    return list ? list->_count : 0;
}

#pragma mark -
#pragma mark Private Implementations 

void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head) {
    BPVStrongSetter(list, _head, head);
}

BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list) {
    return list ? list->_head : NULL;
}

void BPVLinkedListSetCount(BPVLinkedList *list, uint64_t value) {
    BPVObjectWeakSetter(list, _count, value);
}

void BPVLinkedListCountAddValue(BPVLinkedList *list, int8_t value) {
    if (list && value) {
        BPVLinkedListSetCount(list, BPVLinkedListGetCount(list) + value);
        BPVLinkedListIncrementMutationsCount(list);
    }
}

void BPVLinkedListSetMutationsCount(BPVLinkedList *list, uint64_t count) {
    BPVObjectWeakSetter(list, _mutationsCount, count);
}

uint64_t BPVLinkedListGetMutationsCount(BPVLinkedList *list) {
    return list ? list->_mutationsCount : 0;
}

void BPVLinkedListIncrementMutationsCount(BPVLinkedList *list) {
    if (list) {
        BPVLinkedListSetMutationsCount(list, BPVLinkedListGetMutationsCount(list) + 1);
    }
}

bool BPVAccumulationFunction(void *object, void *context) {
    BPVLinkedListContext *wrapperContext = (BPVLinkedListContext *)context;
    BPVArray *array = wrapperContext->accumulator;
    
    BPVLinkedListNode *node = object;
    BPVLinkedListNode *nextNode = BPVLinkedListNodeGetNextNode(node);
    
    BPVAutoreleasingStack *stack = (BPVAutoreleasingStack *)BPVLinkedListNodeGetObject(node);
    BPVAutoreleasingStack *nextStack = (BPVAutoreleasingStack *)BPVLinkedListNodeGetObject(nextNode);
    
    if (BPVAutoreleasingStackIsEmpty(stack) && BPVAutoreleasingStackIsEmpty(nextStack)) {
        BPVArrayAddObject(array, stack);
    } else {
        BPVArrayRemoveAllObjects(array);
        return true;
    }
    
    return false;
}

BPVLinkedListNode *BPVLinkedListNodeGetNodeWithContext(BPVLinkedList *list,
                                                       BPVLinkedListComparisonFunction comparator,
                                                       void *context)
{
    BPVLinkedListNode *result = NULL;
    if (!list) {
        return result;
    }
    
    BPVLinkedListEnumerator *enumerator = BPVLinkedListEnumeratorCreateFromList(list);
    
    while (BPVLinkedListEnumeratorValid(enumerator) && BPVLinkedListEnumeratorGetNextNode(enumerator)) {
        BPVLinkedListNode *node = BPVLinkedListEnumeratorGetNode(enumerator);
        
        if (comparator(node, context)) {
            result = node;
        }
    }
    
    BPVObjectRelease(enumerator);
    
    return result;
}

bool BPVLinkedListNodeContainsObject(void *object, void *context) {
    BPVLinkedListNodeContext *contextWithType = (BPVLinkedListNodeContext *)context;
        
    return object && contextWithType->object == BPVLinkedListNodeGetObject(object);
}
