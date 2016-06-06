//
//  BPVLinkedListNode.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedListNode_h
#define BPVLinkedListNode_h

#include "BPVObject.h"

typedef struct BPVLinkedListNode BPVLinkedListNode;

struct BPVLinkedListNode {
    BPVObject _parentClass;
    
    BPVLinkedListNode *_nextNode;
    void *_object;
};

extern
void __BPVLinkedListNodeDeallocate(BPVLinkedListNode *node);

extern
BPVLinkedListNode *BPVLinkedListNodeCreateWithObject(BPVObject *object);

extern
BPVLinkedListNode *BPVLinkedListNodeGetNextNode(BPVLinkedListNode *node);

extern
void BPVLinkedListNodeSetNextNode(BPVLinkedListNode *node, BPVLinkedListNode *nextNode);

extern
BPVObject *BPVLinkedListNodeGetObject(BPVLinkedListNode *node);

extern
void BPVLinkedListNodeSetObject(BPVLinkedListNode *node, void *object);

#endif /* BPVLinkedListNode_h */
