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
#include "BPVLinkedListPrivate.h"

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

static
void BPVLinkedListEnumeratorSetValidity(BPVLinkedListEnumerator *enumerator, bool value);

static
bool BPVLinkedListEnumeratorMutationsCountValidate(BPVLinkedListEnumerator *enumerator);

#pragma mark -
#pragma mark Public Implementations

void __BPVLinkedListEnumeratorDeallocate(void *object) {
    BPVLinkedListEnumeratorSetNode(object, NULL);
    BPVLinkedListEnumeratorSetList(object, NULL);
    
    __BPVObjectDeallocate(object);
}

BPVLinkedListEnumerator *BPVLinkedListEnumeratorCreateWithList(void *list) {
    if (!list && !BPVLinkedListGetHead(list)) {
        return NULL;
    }
    
    BPVLinkedListEnumerator *enumerator = BPVObjectCreateWithType(BPVLinkedListEnumerator);
    
    BPVLinkedListEnumeratorSetList(enumerator, list);
    BPVLinkedListEnumeratorSetMutationsCount(enumerator, BPVLinkedListGetMutationsCount(list));
    BPVLinkedListEnumeratorSetValidity(enumerator, true);
    
    return enumerator;
}

void *BPVLinkedListEnumeratorGetNextObject(BPVLinkedListEnumerator *enumerator) {
    if (enumerator && BPVLinkedListEnumeratorMutationsCountValidate(enumerator)) {
        BPVLinkedListNode *node = BPVLinkedListEnumeratorGetNode(enumerator);
        BPVLinkedList *list = BPVLinkedListEnumeratorGetList(enumerator);
        
        node = !node ? BPVLinkedListGetHead(list) : BPVLinkedListNodeGetNextNode(node);
        BPVLinkedListEnumeratorSetNode(enumerator, node);
        
        if (!node) {
            BPVLinkedListEnumeratorSetValidity(enumerator, false);
        }
        
        return BPVLinkedListNodeGetObject(node);
    }
    
    return NULL;
}

bool BPVLinkedListEnumeratorIsValid(BPVLinkedListEnumerator *enumerator){
    return enumerator && enumerator->_isValid;
}

#pragma mark -
#pragma mark Private Implementations

void BPVLinkedListEnumeratorSetList(BPVLinkedListEnumerator *enumerator, BPVLinkedList *list) {
    BPVObjectStrogSetter(enumerator, _list, list);
}

BPVLinkedList *BPVLinkedListEnumeratorGetList(BPVLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_list : NULL;
}

void BPVLinkedListEnumeratorSetNode(BPVLinkedListEnumerator *enumerator, BPVLinkedListNode *node) {
    BPVObjectStrogSetter(enumerator, _currentNode, node);
}

BPVLinkedListNode *BPVLinkedListEnumeratorGetNode(BPVLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_currentNode : NULL;
}

void BPVLinkedListEnumeratorSetMutationsCount(BPVLinkedListEnumerator *enumerator, uint64_t mutationsCount) {
    BPVObjectWeakSetter(enumerator, _mutationsCount, mutationsCount);
}

uint64_t BPVLinkedListEnumeratorGetMutationsCount(BPVLinkedListEnumerator *enumerator) {
    return enumerator ? enumerator->_mutationsCount : 0;
}

void BPVLinkedListEnumeratorSetValidity(BPVLinkedListEnumerator *enumerator, bool value) {
    BPVObjectWeakSetter(enumerator, _isValid, value)
}

bool BPVLinkedListEnumeratorMutationsCountValidate(BPVLinkedListEnumerator *enumerator) {
    BPVLinkedList *list = BPVLinkedListEnumeratorGetList(enumerator);
    
    return BPVLinkedListGetMutationsCount(list) == BPVLinkedListEnumeratorGetMutationsCount(enumerator);
}
