//
//  BPVArray.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVArray_h
#define BPVArray_h

#include <stdbool.h>

#include "BPVObject.h"

extern const uint64_t kBPVNotFound;

typedef struct BPVArray BPVArray;

extern
void __BPVArrayDeallocate(BPVArray *object);

extern
BPVArray *BPVArrayCreateArrayWithCapacity(uint64_t capacity);

extern
void BPVArrayAddObject(BPVArray *array, void *object);

extern
uint64_t BPVArrayGetCount(BPVArray *array);

extern
bool BPVArrayContainsObject(BPVArray *array, void *object);

extern
uint64_t BPVArrayGetObjectIndex(BPVArray *array, void *object);

extern
void *BPVArrayGetObjectAtIndex(BPVArray *array, uint64_t index);

extern
void BPVArrayRemoveObjectAtIndex(BPVArray *array, uint64_t index);

extern
void BPVArrayRemoveAllObjects(BPVArray *array);

#endif /* BPVArray_h */
