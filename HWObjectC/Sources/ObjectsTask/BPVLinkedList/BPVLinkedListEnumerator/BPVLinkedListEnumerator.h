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
#include "BPVLinkedListPrivate.h"

typedef struct BPVLinkedListNode BPVLinkedListNode;

struct BPVLinkedListEnumerator {
    BPVObject _parentClass;
    
    void *_list;
    BPVLinkedListNode *_currentNode;
    
    uint64_t _mutationsCount;
    bool _isValid;
};

typedef struct BPVLinkedListEnumerator BPVLinkedListEnumerator;

extern
void __BPVLinkedListEnumeratorDeallocate(void *object);

extern
BPVLinkedListEnumerator *BPVLinkedListEnumeratorCreateWithList(void *list);

extern
void *BPVLinkedListEnumeratorGetNextObject(BPVLinkedListEnumerator *enumerator);

extern
bool BPVLinkedListEnumeratorIsValid(BPVLinkedListEnumerator *enumerator);

#endif /* BPVLinkedListEnumerator_h */
