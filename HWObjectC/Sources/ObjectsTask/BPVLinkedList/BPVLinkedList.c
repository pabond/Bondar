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

BPVObject *BPVLinkedListGetObjectBeforeObject(BPVLinkedList *list, BPVObject *object) {
    BPVLinkedListNode *head = BPVLinkedListGetHead(list);
    
    if (!list || object == BPVLinkedListNodeGetObject(head)) {
        return NULL;
    }
    
    BPVObject *previousObject = BPVLinkedListNodeGetObject(head);
    BPVLinkedListNode *currentNode = BPVLinkedListNodeGetNextNode(head);
    
    do {
        previousObject = BPVLinkedListNodeGetObject(currentNode);
        currentNode = BPVLinkedListNodeGetNextNode(currentNode);
        if (object == BPVLinkedListNodeGetObject(currentNode)) {
            break;
        }
    } while (BPVLinkedListNodeGetNextNode(currentNode));
    
    return previousObject;
}

BPVObject *BPVLinkedListGetObjectAfterObject(BPVLinkedList *list, BPVObject *object) {
    if (list) {
        BPVLinkedListNode *head = BPVLinkedListGetHead(list);
        BPVLinkedListNode *currentNode = head;
        BPVObject *currentObject = BPVLinkedListNodeGetObject(head);
        
        do {
            if (object == currentObject) {
                return BPVLinkedListNodeGetObject(BPVLinkedListNodeGetNextNode(currentNode));
            }
            
            currentNode = BPVLinkedListNodeGetNextNode(currentNode);
            currentObject = BPVLinkedListNodeGetObject(currentNode);
            } while (BPVLinkedListNodeGetNextNode(currentNode));
    }
    
    return NULL;
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
        
        BPVLinkedListNodeContext context = BPVLinkedListCreateEmptyContext();
        context.object = object;
        
        BPVLinkedListNode *node;
        do {
            node = BPVLinkedListNodeGetNodeWithContext(list, BPVLinkedListNodeContainsObject, &context);
            if (node) {
                if (node == head) {
                    BPVLinkedListSetHead(list, BPVLinkedListNodeGetNextNode(node));
                } else {
                    BPVLinkedListNodeSetNextNode(context.previousNode, BPVLinkedListNodeGetNextNode(node));
                    BPVLinkedListCountAddValue(list, -1);
                }
            }
        } while (node);
    }
}

void BPVLinkedListRemoveAllObjects(BPVLinkedList *list) {
    if (list) {
        BPVLinkedListSetHead(list, NULL);
        BPVLinkedListSetCount(list, 0);
    }
}

bool BPVLinkedListContainsObject(BPVLinkedList *list, void *object) {
    if (list) {
        BPVLinkedListNodeContext context = BPVLinkedListCreateEmptyContext();
        context.object = object;
        
        return BPVLinkedListNodeGetNodeWithContext(list, BPVLinkedListNodeContainsObject, &context);
    }
    
    return NULL;
}

uint64_t BPVLinkedListGetCount(BPVLinkedList *list) {
    return list ? list->_count : 0;
}

BPVLinkedListNodeContext BPVLinkedListCreateEmptyContext() {
    BPVLinkedListNodeContext context;
    memset(&context, 0, sizeof(context));
    
    return context;
}

#pragma mark -
#pragma mark Private Implementations 

void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head) {
    BPVStrogSetter(list, _head, head);
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

BPVLinkedListNode *BPVLinkedListNodeGetNodeWithContext(BPVLinkedList *list,
                                                       BPVLinkedListComparisonFunction comparator,
                                                       BPVLinkedListNodeContext *context)
{
    if (list) {
        BPVLinkedListEnumerator *enumerator = BPVLinkedListEnumeratorCreateFromList(list);
        BPVLinkedListNode *node = BPVLinkedListEnumeratorGetNode(enumerator);
        context->node = node;
        
        while (BPVLinkedListEnumeratorValid(enumerator)) {
            
            if (BPVLinkedListNodeContainsObject(node, *context)) {
                return node;
            }
            
            context->previousNode = node;
            context->node = BPVLinkedListNodeGetNextNode(node);
            node = context->node;
        }
        
        BPVObjectRelease(enumerator);
    }
    
    return NULL;
}

bool BPVLinkedListNodeContainsObject(BPVLinkedListNode *node, BPVLinkedListNodeContext context) {
    return node && context.object == BPVLinkedListNodeGetObject(node);
}
