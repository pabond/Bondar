//
//  BPVArray.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVArray.h"

const uint64_t kBPVNotFound = UINT64_MAX;

struct BPVArray {
    BPVObject _parentClass;
    
    void **_data;
    uint64_t _count;
    uint64_t _capacity;
};

#pragma mark -
#pragma mark Private Declarations

static
void BPVArraySetCapacity(BPVArray *array, uint64_t capacity);

static
bool BPVArrayShouldResize(BPVArray *array);

static
void BPVArrayResize(BPVArray *array);

static
void BPVArrayCountAddValue(BPVArray *array, uint64_t value);

#pragma mark -
#pragma mark Public Implementations

void __BPVArrayDeallocate(BPVArray *object) {
    
    
    __BPVObjectDeallocate(object);
}

BPVArray *BPVArrayCreateArrayWithCapacity(uint64_t capacity) {
    BPVArray *object = BPVObjectCreateWithType(BPVArray);
    BPVArraySetCapacity(object, capacity);
    
    return object;
}

void BPVArrayAddObject(BPVArray *array, void *object) {
    if (array && object) {
        uint64_t count = BPVArrayGetCount(array);
        if (BPVArrayShouldResize(array)) {
            BPVArrayResize(array);
        }
        
        BPVArrayCountAddValue(array, 1);
    }
}

uint64_t BPVArrayGetCount(BPVArray *array) {
    return array ? array->_count : kBPVNotFound;
}

bool BPVArrayContainsObject(BPVArray *array, void *object);

uint64_t BPVArrayGetObjectIndex(BPVArray *array, void *object);

void *BPVArrayGetObjectAtIndex(BPVArray *array, uint64_t index);

void BPVArrayRemoveObjectAtIndex(BPVArray *array, uint64_t index);

void BPVArrayRemoveAllObjects(BPVArray *array);

#pragma mark -
#pragma mark Private Implementations

void BPVArraySetCapacity(BPVArray *array, uint64_t capacity);

bool BPVArrayShouldResize(BPVArray *array); 

void BPVArrayResize(BPVArray *array);

void BPVArrayCountAddValue(BPVArray *array, uint64_t value) {
    if (array) {
        array->_count += value;
    }
}
