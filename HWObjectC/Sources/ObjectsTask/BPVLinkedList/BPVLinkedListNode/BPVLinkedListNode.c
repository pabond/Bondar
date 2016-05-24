//
//  BPVLinkedListNode.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVLinkedListNode.h"

void __BPVLinkedListNodeDeallocate(BPVLinkedListNode *node) {
    BPVLinkedListNodeSetNextNode(node, NULL);
    BPVLinkedListNodeSetObject(node, NULL);
    
    __BPVObjectDeallocate(node);
}

BPVLinkedListNode *BPVLinkedListNodeCreateWithObject(BPVObject *object) {
    BPVLinkedListNode *result = BPVObjectCreateWithType(BPVLinkedListNode);
    BPVLinkedListNodeSetObject(result, object);
    
    return result;
}

BPVLinkedListNode *BPVLinkedListNodeGetNextNode(BPVLinkedListNode *node) {
    return node ? node->_nextNode : NULL;
}

void BPVLinkedListNodeSetNextNode(BPVLinkedListNode *node, BPVLinkedListNode *nextNode) {
    BPVLinkedListNode *previousNode = node->_nextNode;
    
    if (node && nextNode != previousNode) {
        BPVObjectRelease(previousNode);
        
        node->_nextNode = BPVObjectRetain(nextNode);
    }
}

BPVObject *BPVLinkedListNodeGetObject(BPVLinkedListNode *node) {
    return node ? node->_object : NULL;
}

void BPVLinkedListNodeSetObject(BPVLinkedListNode *node, void *object) {
    BPVLinkedListNode *previousObject = node->_object;
    
    if (node && object != previousObject && node != object) {
        BPVObjectRelease(previousObject);
        
        node->_object = BPVObjectRetain(object);
    }
}