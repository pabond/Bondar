//
//  BPVLinkedListEnumerator.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVLinkedListEnumerator.h"
#include "BPVLinkedListNode.h"
#include "BPVLinkedList.h"

#pragma mark -
#pragma mark Private Declarations

static
void BPVLinkedListEnumeratorSetList(BPVLinkedListEnumerator *enumerator, BPVLinkedList *list);

static
BPVLinkedList *BPVLinkedListEnumeratorGetList(BPVLinkedListEnumerator *enumerator);

static
void BPVLinkedListEnumeratorSetNode(BPVLinkedListEnumerator *enumerator, BPVLinkedListNode *node);

static
BPVLinkedListNode *BPVLinkedListEnumeratorGetNode(BPVLinkedListEnumerator *enumerator);

static
void BPVLinkedListEnumeratorSetMutationsCount(BPVLinkedListEnumerator *enumerator, uint64_t mutationsCount);

static
uint64_t BPVLinkedListEnumeratorGetMutationsCount(BPVLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Public Implementations

void __BPVLinkedListEnumeratorDeallocate(void *object) {
    BPVLinkedListEnumeratorSetNode(object, NULL);
    BPVLinkedListEnumeratorSetList(object, NULL);
    
    __BPVObjectDeallocate(object);
}

BPVLinkedListEnumerator *BPVLinkedListEnumeratorCreateWithList(void *list) {
    if (!list) {
        return NULL;
    }
    
    BPVLinkedListEnumerator *enumerator = BPVObjectCreateWithType(BPVLinkedListEnumerator);
    
    BPVLinkedListEnumeratorSetList(enumerator, list);
    BPVLinkedListEnumeratorSetMutationsCount(enumerator, BPVLinkedListGetMutationsCount(list));
    
    return enumerator;
}

void *BPVLinkedListEnumeratorGetNextObject(BPVLinkedListEnumerator *enumerator) {
    if (!enumerator) {
        return NULL;
    }
    
    return NULL;
}

bool BPVLinkedListEnumeratorIsValid(BPVLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Private Implementations

void BPVLinkedListEnumeratorSetList(BPVLinkedListEnumerator *enumerator, BPVLinkedList *list) {
    if (enumerator && enumerator->_list != list) {
        BPVObjectRelease(enumerator);
        
        enumerator->_list = BPVObjectRetain(list);
    }
}

BPVLinkedList *BPVLinkedListEnumeratorGetList(BPVLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_list : NULL;
}

void BPVLinkedListEnumeratorSetNode(BPVLinkedListEnumerator *enumerator, BPVLinkedListNode *node) {
    if (enumerator && enumerator->_currentNode != node) {
        BPVObjectRelease(enumerator);
        
        enumerator->_currentNode = BPVObjectRetain(node);
    }

}

BPVLinkedListNode *BPVLinkedListEnumeratorGetNode(BPVLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_currentNode : NULL;
}

void BPVLinkedListEnumeratorSetMutationsCount(BPVLinkedListEnumerator *enumerator, uint64_t mutationsCount) {
    if (enumerator) {
        enumerator->_mutationsCount = mutationsCount;
    }
}

uint64_t BPVLinkedListEnumeratorGetMutationsCount(BPVLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_mutationsCount : 0;
}
