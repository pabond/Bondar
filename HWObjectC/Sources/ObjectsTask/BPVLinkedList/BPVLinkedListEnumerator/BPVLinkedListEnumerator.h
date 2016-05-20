//
//  BPVLinkedListEnumerator.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedListEnumerator_h
#define BPVLinkedListEnumerator_h

#include "BPVObject.h"

typedef struct BPVLinkedList BPVLinkedList;
typedef struct BPVLinkedListNode BPVLinkedListNode;

typedef struct {
    BPVObject _parentClass;
    
    BPVLinkedList *_list;
    BPVLinkedListNode *_currentNode;
} BPVLinkedListEnumerator;


#endif /* BPVLinkedListEnumerator_h */
