//
//  BPVObject.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/10/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVObject.h"

#pragma mark -
#pragma mark Private Declarations

static
void BPVObjectSetCount(BPVObject *object, uint64_t value);

static
void BPVObjectRetainCountAddValue(BPVObject *object, int8_t value);

#pragma mark -
#pragma mark Public Implementations

void __BPVObjectDeallocate(void *object) {
    if (object) {
        free(object);
    }
}

void *__BPVCreateObject(size_t objectSize, BPVObjectDeallocator dealocator) {
    
    if (objectSize && dealocator) {
        BPVObject *object = calloc(1, objectSize);
        
        object->_retainCount = 1;
        object->_deallocatorFunctionPointer = dealocator;
        
        return object;
    }
    
    return NULL;
}

uint64_t BPVObjectGetRetainCount(void *object) {
    return object ? ((BPVObject *)object)->_retainCount : 0;
}

void *BPVObjectRetain(void *object) {
    if (object) {
        BPVObjectRetainCountAddValue(((BPVObject*)object), 1);
    }
    
    return object;
}

void BPVObjectRelease(void *object) {
    if (object) {
        BPVObject *objectPointer = (BPVObject *)object;
        BPVObjectRetainCountAddValue(objectPointer, -1);
        if (0 == BPVObjectGetRetainCount(objectPointer)) {
            objectPointer->_deallocatorFunctionPointer(object);
        }
    }
}

/*
void BPVObjectStrogSetter(void *object, void **field, void *value) {
    if (!object && *field == value) {
        return;
    }
    
    BPVObjectRelease(*field);
    *field = BPVObjectRetain(value);
}

void BPVObjectWeakSetter(void *object, void **field, void *value) {
    if (object) {
        object->field = value;
    }
}
*/

#pragma mark -
#pragma mark Privare Implementations

void BPVObjectSetCount(BPVObject *object, uint64_t value) {
    if (object) {
        object->_retainCount = value;
    }
}

void BPVObjectRetainCountAddValue(BPVObject *object, int8_t value) {
    if (object) {
        BPVObjectSetCount(object, object->_retainCount += value);
    }
}
