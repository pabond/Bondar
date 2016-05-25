//
//  BPVObject.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/10/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVObject_h
#define BPVObject_h

#include <stdlib.h>

typedef void (*BPVObjectDeallocator)(void *object);

typedef struct {
    uint64_t _retainCount;
    BPVObjectDeallocator _deallocatorFunctionPointer;
} BPVObject;

#define BPVObjectCreateWithType(type) \
    __BPVCreateObject(sizeof(type), (BPVObjectDeallocator)__##type##Deallocate)

extern
void __BPVObjectDeallocate(void *object);

extern
void *__BPVCreateObject(size_t objectSize, BPVObjectDeallocator dealocator);

extern
uint64_t BPVObjectGetRetainCount(void *object);

extern
void *BPVObjectRetain(void *object);

extern
void BPVObjectRelease(void *object);

#define BPVObjectWeakSetter(object, field, value) \
    if (object) { \
        object->field = value; \
    }

#define BPVObjectStrogSetter(object, field, value) \
    if (object && object->field != value) { \
        BPVObjectRelease(object->field); \
        object->field = BPVObjectRetain(value); \
    }

/*
extern
void BPVObjectStrogSetter(void *object, void **field, void *value);

extern
void BPVObjectWeakSetter(void *object, void **field, void *value);
*/
 
#endif /* BPVObject_h */
