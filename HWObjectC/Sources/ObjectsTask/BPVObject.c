//
//  BPVObject.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/10/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVObject.h"

void __BPVObjectDeallocate(void *object) {
    if (object) {
        free(object);
    }
}

void *__BPVCreateObject(size_t objectSize, BPVObjectDeallocator dealocator) {
    
    if (objectSize && dealocator) {
        BPVObject *object = calloc(1, objectSize);
        
        object->_referenceCount = 1;
        object->_deallocatorFunctionPointer = dealocator;
        
        return object;
    }
    
    return NULL;
}

uint64_t BPVObjectGetReferenceCount(void *object) {
    return object ? ((BPVObject *)object)->_referenceCount : 0;
}

void *BPVObjectRetain(void *object) {
    if (object) {
        ((BPVObject*)object)->_referenceCount += 1;
    }
    
    return object;
}

void BPVObjectRelease(void *object) {
    if (object) {
        BPVObject *objectPointer = (BPVObject *)object;
        objectPointer->_referenceCount -= 1;
        if (0 == BPVObjectGetReferenceCount(objectPointer)) {
            objectPointer->_deallocatorFunctionPointer(object);
        }
    }
}