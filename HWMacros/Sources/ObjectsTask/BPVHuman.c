//
//  BPVHuman.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/21/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdlib.h>

#include <assert.h>

#include <string.h>

#include "BPVHuman.h"

struct BPVHuman {
    char *_name;
    uint8_t _age;
    uint8_t _children[BPVMaxHumanChildren];
    BPVHumanGender _gender;
    BPVHuman *_partner;
    BPVHuman *_parent;
    uint64_t _referenceCount;
};

#pragma mark -
#pragma mark Private Declarations

#pragma mark -
#pragma mark Public Implementations

BPVHuman *BPVHumanCreateObject() {
    BPVHuman *result = calloc(1, sizeof(BPVHuman));
    
    assert(NULL != result);
    
    return result;
}

void _BPVHumanDeallocateObject(BPVHuman *object) {
    BPVHumanSetName(object, NULL);
    BPVHumanSetParent(object, NULL);
    BPVHumanSetPartner(object, NULL);
    
    free(object);
}

char BPVHumanName(BPVHuman *object) {
    return *(!object ? NULL : object->_name);
}

void BPVHumanSetName(BPVHuman *object, char *name) {
    if (object && object->_name) {
        free(object->_name);
        object->_name = NULL;
        
        if (name) {
            object->_name = strdup(name);
        }
    }
}

int BPVHumanAge(BPVHuman *object) {
    if(!object) {
        return 0;
    }
    
    return object->_age;
}

void BPVHumanSetAge(BPVHuman *object, uint8_t age) {
    if (object) {
    object->_age = age;
    }
}

BPVHuman BPVHumanPartner(BPVHuman *object, BPVHuman *partner) {
    return *(object ? object->_partner : NULL);
}

void BPVHumanSetPartner(BPVHuman *object, BPVHuman *partner) {
    object->_partner = partner;
}

BPVHuman BPVHumanParent(BPVHuman *object, BPVHuman *parent) {
    return *(object ? object->_parent : NULL);
}

void BPVHumanSetParent(BPVHuman *object, BPVHuman *parent) {
    if (object) {
        if (object->_parent) {
            BPVObjectRelease(object->_parent);
            object->_parent = NULL;
        }
        object->_parent = parent;
        BPVObjectRetain(parent);
    }
}

void BPVObjectRetain(BPVHuman *object) {
    if (object) {
        object->_referenceCount++;
    }
}

void BPVObjectRelease(BPVHuman *object) {
    if (object) {
        if (0 == --(object->_referenceCount)) {
            _BPVHumanDeallocateObject(object);
        }
    }
}

#pragma mark -
#pragma mark Privat Implementations
