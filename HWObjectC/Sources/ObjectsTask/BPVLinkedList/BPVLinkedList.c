//
//  BPVLinkedList.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVLinkedList.h"

#include "BPVLinkedListNode.h"

#pragma mark -
#pragma mark Private Declarations

static
void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head);

static
BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list);

static
void BPVLinkedListSetCount(BPVLinkedList *list, uint64_t value);

static
void BPVLinkedListCountAddValue(BPVLinkedList *list, int8_t value);

#pragma mark -
#pragma mark Public Implementations

void __BPVLinkedListDeallocate(BPVLinkedList *list) {
    BPVLinkedListSetHead(list, NULL);
    
    __BPVObjectDeallocate(list);
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
    
    if (!list && object == BPVLinkedListNodeGetObject(head)) {
        return NULL;
    }
    
    BPVObject *previousObject = BPVLinkedListNodeGetObject(head);
    BPVLinkedListNode *currentNode = BPVLinkedListNodeGetNextNode(head);
    
    do {
        previousObject = BPVLinkedListNodeGetObject(currentNode);
        currentNode = BPVLinkedListNodeGetNextNode(BPVLinkedListGetHead(list));
        if (object == BPVLinkedListNodeGetObject(currentNode)) {
            break;
        }
    } while (BPVLinkedListNodeGetNextNode(currentNode));
    
    return previousObject;
}

bool BPVLinkedListIsEmpty(BPVLinkedList *list) {
    return !list && !BPVLinkedListGetHead(list);
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

void BPVLinkedListRemoveObject(BPVLinkedList *list, void *object);

void BPVLinkedListRemoveAllObjects(BPVLinkedList *list) {
    if (list) {
        BPVLinkedListSetHead(list, NULL);
        BPVLinkedListSetCount(list, 0);
    }
}

bool BPVLinkedListContainsObject(BPVLinkedList *list, void *object);

uint64_t BPVLinkedListGetCount(BPVLinkedList *list) {
    return list ? list->_count : 0;
}

#pragma mark -
#pragma mark Private Implementations 

void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head) {
    if (list && head != list->_head) {
        BPVObjectRelease(head);
        
        list->_head = BPVObjectRetain(head);
    }
}

BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list) {
    return list ? list->_head : NULL;
}

void BPVLinkedListSetCount(BPVLinkedList *list, uint64_t value) {
    if (list) {
        list->_count = value;
    }
}

void BPVLinkedListCountAddValue(BPVLinkedList *list, int8_t value) {
    if (list && value) {
        BPVLinkedListSetCount(list, BPVLinkedListGetCount(list) + value);
    }
}
