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
void BPVLinkedListSetHead(BPVLinkedList *object, BPVLinkedListNode *head);

static
void *BPVLinkedListGetHead(BPVLinkedList *list);

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
    }
}

BPVLinkedList *BPVLinkedListGetObjectBeforeObject(BPVLinkedList *list) {
    return NULL; //back when enumerator will be writen
}

bool BPVLinkedListIsEmpty(BPVLinkedList *list) {
    return !list && !BPVLinkedListGetHead(list);
}

void BPVLinkedListAddObject(BPVLinkedList *list, void *object) {
    if (list && !BPVLinkedListContainsObject(list, object)) {
        <#statements#>
    }
}

void BPVLinkedListRemoveObject(BPVLinkedList *list, void *object);

void BPVLinkedListRemoveAllObjects(BPVLinkedList *list);

bool BPVLinkedListContainsObject(BPVLinkedList *list, void *object) {
    return ;
}

uint64_t BPVLinkedListGetCount(BPVLinkedList *list);

#pragma mark -
#pragma mark Private Implementations 

void BPVLinkedListSetHead(BPVLinkedList *object, BPVLinkedListNode *head);

BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list) {
    return list ? list->_head : NULL;
}

