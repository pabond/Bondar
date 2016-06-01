//
//  BPVAutoreleasingStack.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/26/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVAutoreleasingStack_h
#define BPVAutoreleasingStack_h

#include <stdbool.h>

#include "BPVObject.h"

typedef struct BPVAutoreleasingStack BPVAutoreleasingStack;

struct BPVAutoreleasingStack {
    BPVObject _parentClass;
    
    void **_data;
    void **_head;
    uint64_t _count;
    size_t _size;
};

typedef enum {
    BPVAutoreleasingStackPopObjectTypeNone,
    BPVAutoreleasingStackPopObjectTypeNull,
    BPVAutoreleasingStackPopObjectTypeObject
} BPVAutoreleasingStackPopObjectType;

extern
void __BPVAutoreleasingStackDeallocate(void *object);

extern
BPVAutoreleasingStack *BPVAutoreleasingStackCreateWithSize(size_t size);

extern
bool BPVAutoreleasingStackIsFull(BPVAutoreleasingStack *stack);

extern
bool BPVAutoreleasingStackIsEmpty(BPVAutoreleasingStack *stack);

extern
void BPVAutoreleasingStackPushObject(BPVAutoreleasingStack *stack, void *object);

extern
BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObject(BPVAutoreleasingStack *stack);

extern
BPVAutoreleasingStackPopObjectType BPVAutoreleasingStackPopObjects(BPVAutoreleasingStack *stack);

extern
void **BPVAutoreleasingStackGetData(BPVAutoreleasingStack *stack);

extern
uint64_t BPVAutoreleasingStackGetCount(BPVAutoreleasingStack *stack);

extern
size_t BPVAutoreleasingStackGetSize(BPVAutoreleasingStack *stack);

extern
void BPVAutoreleasingStackPopAllObjects(BPVAutoreleasingStack *stack);

#endif /* BPVAutoreleasingStack_h */
