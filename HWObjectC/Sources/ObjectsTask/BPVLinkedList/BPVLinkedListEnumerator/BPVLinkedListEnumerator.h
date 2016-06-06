//
//  BPVLinkedListEnumerator.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedListEnumerator_h
#define BPVLinkedListEnumerator_h

#include <stdbool.h>

#include "BPVObject.h"

typedef struct BPVLinkedListNode BPVLinkedListNode;

struct BPVLinkedListEnumerator {
    BPVObject _parentClass;
    
    void *_list;
    BPVLinkedListNode *_currentNode;
    
    uint64_t _mutationsCount;
    bool _valid;
};

typedef struct BPVLinkedListEnumerator BPVLinkedListEnumerator;

extern
void __BPVLinkedListEnumeratorDeallocate(void *object);

extern
BPVLinkedListEnumerator *BPVLinkedListEnumeratorCreateWithList(void *list);

extern
void *BPVLinkedListEnumeratorGetNextObject(BPVLinkedListEnumerator *enumerator);

extern
void *BPVLinkedListEnumeratorGetNextNode(BPVLinkedListEnumerator *enumerator);

extern
bool BPVLinkedListEnumeratorValid(BPVLinkedListEnumerator *enumerator);

#endif /* BPVLinkedListEnumerator_h */
