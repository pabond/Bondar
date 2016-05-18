//
//  BPVArray.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <string.h>

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
uint64_t BPVArrayPrefferedCapacity(BPVArray *array);

static
void BPVArrayResize(BPVArray *array);

static
void BPVArrayCountAddValue(BPVArray *array, int8_t value);

static
void BPVArraySetObjectAtIndex(BPVArray *array, void *object, uint64_t count);

static
void BPVArrayReorderObjects(BPVArray *array, uint8_t index);

#pragma mark -
#pragma mark Public Implementations

void __BPVArrayDeallocate(BPVArray *array) {
    if (array) {
        BPVArraySetCapacity(array, 0);
    }
    
    __BPVObjectDeallocate(array);
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
    if (array) {
        BPVArraySetObjectAtIndex(array, NULL, index);
        BPVArrayReorderObjects(array, index);
        BPVArrayCountAddValue(array, -1);
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

uint64_t BPVArrayGetCapacity(BPVArray *array) {
    if (!array) {
        return 0;
    }
    
    return array->_capacity;
}

#pragma mark -
#pragma mark Private Implementations

void BPVArraySetCapacity(BPVArray *array, uint64_t capacity) {
    if (array && capacity != array->_capacity) {
        size_t size = capacity * sizeof(*array->_data);
        if (size && array->_data) {
            free(array->_data);
            array->_data = NULL;
        } else {
            array->_data = realloc(array->_data, size);
        }
        
        if (capacity > array->_capacity) {
            void *startPointer = array->_data + array->_capacity;
            size_t numberOfBytes = (capacity - array->_capacity) * sizeof(*array->_data);
            
            memset(startPointer, 0, numberOfBytes);
        }
        
        array->_capacity = capacity;
    }
}

uint64_t BPVArrayPrefferedCapacity(BPVArray *array) {
    uint64_t prefferedCapacity = BPVArrayGetCount(array);
    if (array) {
        uint64_t count = BPVArrayGetCount(array);
        if (count > BPVArrayGetCapacity(array)) {
            prefferedCapacity = count;
        }
    }
    
    return prefferedCapacity;
}

bool BPVArrayShouldResize(BPVArray *array) {
    return array && BPVArrayGetCapacity(array) != BPVArrayPrefferedCapacity(array);
}

void BPVArrayResize(BPVArray *array) {
    if (array && BPVArrayShouldResize(array)) {
        BPVArraySetCapacity(array, BPVArrayPrefferedCapacity(array));
    }
}

void BPVArrayCountAddValue(BPVArray *array, int8_t value) {
    if (array) {
        array->_count += value;
        
        BPVArrayResize(array);
    }
}

void BPVArraySetObjectAtIndex(BPVArray *array, void *object, uint64_t count){
    BPVArray *currentObjectAtIndex = BPVArrayGetObjectAtIndex(array, count);
    if (array && currentObjectAtIndex != object) {
        BPVObjectRelease(currentObjectAtIndex);
        
        array->_data[count] = BPVObjectRetain(object);
    }
}

void BPVArrayReorderObjects(BPVArray *array, uint8_t index) {
    if (array) {
        uint64_t count = BPVArrayGetCount(array);
        
        void **data = array->_data;
        if (index < count) {
            uint64_t pointersCount = count - (index + 1);
            
            memmove(&data[index], &data[index + 1], pointersCount * sizeof(*data));
        }
        
        data[count - 1] = NULL;
    }
}
