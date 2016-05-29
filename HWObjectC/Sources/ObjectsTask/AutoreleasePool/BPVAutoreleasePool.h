//
//  BPVAutoreleasePool.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/28/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVAutoreleasePool_h
#define BPVAutoreleasePool_h

#include <stdbool.h>

#include "BPVObject.h"

typedef struct BPVLinkedList BPVLinkedList;
typedef struct BPVAutoreleasingStack BPVAutoreleasingStack;

typedef struct BPVAutoreleasePool BPVAutoreleasePool;

struct BPVAutoreleasePool {
    BPVObject _parentClass;
    
    BPVLinkedList *_list;
    uint64_t _stacksCount;
};

extern
void __BPVAutoreleasePoolDeallocate(BPVAutoreleasePool *pool);

extern
BPVAutoreleasePool *BPVAutoreleasePoolCreateWithEmptyStack();

extern
bool BPVAutoreleasePoolIsValid(BPVAutoreleasePool *pool);

extern
void BPVAutoreleasePoolDrain(BPVAutoreleasePool *pool);

extern
uint64_t BPVAutoreleasePoolGetCount(BPVAutoreleasePool *pool);

extern
void BPVAutoreleasePoolSetLinkedList(BPVAutoreleasePool *pool, BPVLinkedList *list);

extern
BPVLinkedList BPVAutoreleasePoolGetLinkedList(BPVAutoreleasePool *pool);


#endif /* BPVAutoreleasePool_h */
