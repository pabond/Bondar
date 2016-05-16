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

static
void BPVArraySetObjectAtIndex(BPVArray *array, void *object, uint64_t count);

static
void BPVArrayReorderObjects(BPVArray *array, uint8_t index);

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
        if (BPVArrayShouldResize(array)) {
            BPVArrayResize(array);
        }
  
        BPVArraySetObjectAtIndex(array, object, BPVArrayGetCount(array));
        BPVArrayCountAddValue(array, 1);
    }
}

uint64_t BPVArrayGetCount(BPVArray *array) {
    return array ? array->_count : kBPVNotFound;
}

bool BPVArrayContainsObject(BPVArray *array, void *object) {
    return array && kBPVNotFound != BPVArrayGetObjectIndex(array, object);
}

uint64_t BPVArrayGetObjectIndex(BPVArray *array, void *object) {
    uint64_t result = kBPVNotFound;
    
    if (array && object) {
        for (uint64_t index = 0; index < BPVArrayGetCount(array); index++) {
            if (BPVArrayGetObjectAtIndex(array, index) == object) {
                result = index;
            }
        }
    }
    
    return result;
}

void *BPVArrayGetObjectAtIndex(BPVArray *array, uint64_t index) {
    return array && index < BPVArrayGetCount(array) ? array->_data[index] : NULL;
}

void BPVArrayRemoveObjectAtIndex(BPVArray *array, uint64_t index) {
    if (array && index < BPVArrayGetCount(array)) {
        BPVArraySetObjectAtIndex(array, NULL, index);
        
        BPVArrayReorderObjects(array, index);
        array->_count -= 1;
    }
}

void BPVArrayRemoveAllObjects(BPVArray *array) {
    if (array) {
        uint64_t count = BPVArrayGetCount(array);
        for (uint64_t index = 0; index < count; index++) {
            BPVArrayRemoveObjectAtIndex(array, count - index - 1);
        }
        
        BPVArraySetCapacity(array, 0);
    }
}

#pragma mark -
#pragma mark Private Implementations

void BPVArraySetCapacity(BPVArray *array, uint64_t capacity) {
    if (array) {
        array->_capacity = capacity;
    }
}

bool BPVArrayShouldResize(BPVArray *array) {
    
}

void BPVArrayResize(BPVArray *array);

void BPVArrayCountAddValue(BPVArray *array, uint64_t value) {
    if (array) {
        array->_count += value;
    }
}

void BPVArrayReorderObjects(BPVArray *array, uint8_t index) {
    uint8_t lastObjectIndex = BPVArrayGetCount(array) - 1;
    if (array && index < lastObjectIndex) {
        BPVArray *lastObject = BPVArrayGetObjectAtIndex(array, lastObjectIndex);
        BPVArraySetObjectAtIndex(array, lastObject, index);
        BPVArrayRemoveObjectAtIndex(array, lastObjectIndex);
    }
}
