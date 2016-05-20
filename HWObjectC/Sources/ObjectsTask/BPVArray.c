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
void BPVArrayResizeIfNeeded(BPVArray *array);

static
void BPVArraySetCount(BPVArray *array, uint64_t value);

static
void BPVArrayCountAddValue(BPVArray *array, int8_t value);

static
void BPVArraySetObjectAtIndex(BPVArray *array, void *object, uint64_t count);

static
void BPVArrayReorderObjects(BPVArray *array, uint8_t index);

#pragma mark -
#pragma mark Public Implementations

void __BPVArrayDeallocate(BPVArray *array) {
    BPVArraySetCapacity(array, 0);
    
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
            BPVArrayResizeIfNeeded(array);
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
            BPVArraySetObjectAtIndex(array, NULL, count - index - 1);
        }
        
        BPVArraySetCapacity(array, 1);
    }
}

uint64_t BPVArrayGetCapacity(BPVArray *array) {
    return array ? array->_capacity : 0;
}

#pragma mark -
#pragma mark Private Implementations

void BPVArraySetCapacity(BPVArray *array, uint64_t capacity) {
    if (array) {
        uint64_t previousCapacity = array->_capacity;
        size_t elementSize = sizeof(*array->_data);
        
        if (capacity != previousCapacity) {
            size_t size = capacity * elementSize;
            if (!capacity) {
                if (array->_data) {
                    free(array->_data);
                    array->_data = NULL;
                }
            } else {
                array->_data = realloc(array->_data, size);
                
                if (capacity > previousCapacity) {
                    void *startPointer = array->_data + previousCapacity;
                    uint64_t capacityDelta = capacity - previousCapacity;
                    size_t numberOfBytes = capacityDelta * elementSize;
                    
                    memset(startPointer, 0, numberOfBytes);
                }

            }
            
            array->_capacity = capacity;
        }
    }
}

uint64_t BPVArrayPrefferedCapacity(BPVArray *array) {
    if (!array) {
        return 0;
    }

    uint64_t capacity = BPVArrayGetCount(array);
    uint64_t count = BPVArrayGetCount(array);
    
    if (!capacity) {
        return 1;
    }
    
    if (count >= capacity) {
        return capacity * 2;
    }
    
    if (count <= capacity / 3) {
        return capacity / 2;
    }
    
    return capacity;
}

bool BPVArrayShouldResize(BPVArray *array) {
    return array && BPVArrayGetCapacity(array) != BPVArrayPrefferedCapacity(array);
}

void BPVArrayResizeIfNeeded(BPVArray *array) {
    if (array && BPVArrayShouldResize(array)) {
        BPVArraySetCapacity(array, BPVArrayPrefferedCapacity(array));
    }
}

void BPVArraySetCount(BPVArray *array, uint64_t value) {
    array->_count = value;
}

void BPVArrayCountAddValue(BPVArray *array, int8_t value) {
    if (array) {
        uint64_t newValue = value + BPVArrayGetCount(array);
        BPVArraySetCount(array, newValue);
        
        BPVArrayResizeIfNeeded(array);
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
