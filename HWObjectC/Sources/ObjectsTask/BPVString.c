//
//  BPVString.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "BPVString.h"
#include "BPVObject.h"

struct BPVString {
    BPVObject _parentClass;
    
    void *_data;
    uint64_t _count;
};

#pragma mark -
#pragma mark Private Declarations

static
void BPVStringSetString(BPVString *object, char *string);

static
BPVString *BPVStringCopySrting(char *string);

static
size_t BPVStringGetSize(char *string);

#pragma mark -
#pragma mark Public Implementations

void __BPVStringDeallocate(void *object) {
    
    BPVStringSetString(object, NULL);
    
    __BPVObjectDeallocate(object);
}

BPVString* BVPStringCreate() {
    return BPVObjectCreateWithType(BPVString);
}

char *BPVStringGetString(BPVString *object) {
    return object ? object->_data : NULL;
}

#pragma mark -
#pragma mark Private Implementations

void BPVStringSetString(BPVString *object, char *string) {
    if (object && BPVStringGetString(object) != string) {
        if (object->_data) {
            free(object->_data);
            object->_data = NULL;
        }
        
        if (string) {
            object->_data = BPVStringCopySrting(string);
        }
    }
}

BPVString *BPVStringCopyString(char *string) {
    return string ? strdup(string) : NULL;
}

size_t BPVStringGetSize(char *string) {
    return string ? strlen(string) : 0;
}
