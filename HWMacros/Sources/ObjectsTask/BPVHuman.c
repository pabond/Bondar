//
//  BPVHuman.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/21/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "BPVHuman.h"

static const uint8_t BPVHumanChildrenCount = 20;

struct BPVHuman {
    uint64_t _referenceCount;
    BPVHumanGender _gender;
    
    char *_name;
    uint8_t _age;
    
    BPVHuman *_partner;
    BPVHuman *_mother;
    BPVHuman *_father;
    
    BPVHuman *_children[BPVHumanChildrenCount];
    uint8_t childrenCount;
};

#pragma mark -
#pragma mark Private Declarations

static
void BPVHumanMarriage(BPVHuman *partner1, BPVHuman *partner2);

static
bool BPVHumansCanGetMarried(BPVHuman *partner1, BPVHuman *partner2);

static
BPVHumanGender BPVHumanGetGender(BPVHuman *object);

static
void BPVHumanDevorce(BPVHuman *object);

static
void BPVHumanSetChildAtIndex (BPVHuman *parent, uint8_t index, BPVHuman *child);

static
void BPVChildBirth(BPVHuman *parent1);

static
BPVHuman *BPVHumanGetChildAtIndex (BPVHuman *parent, uint8_t index);

static
void BPVHumanRemoveChildAtIndex (BPVHuman *parent, uint8_t index);

static
void BPVHumanRemoveChildFromParents (BPVHuman *parent, uint8_t index);

static
void BPVHumanAddChildAtIndex (BPVHuman *parent, uint8_t index);

static
uint8_t BPVHumanGetChildrenCount(BPVHuman *object);

static
void BPVHumanReorganizeChildrensArray(BPVHuman *object);

#pragma mark -
#pragma mark Public Implementations

BPVHuman *BPVHumanCreateObject() {
    BPVHuman *result = calloc(1, sizeof(BPVHuman));
    
    assert(NULL != result);
    result->_referenceCount = 1;
    
    BPVObjectRelease(result);
    
    return result;
}

void __BPVHumanDeallocateObject(BPVHuman *object) {
    BPVHumanSetName(object, NULL);
    BPVHumanSetFather(object, NULL);
    BPVHumanSetMother(object, NULL);
    BPVHumanSetPartner(object, NULL);
    
    free(object);
}

char BPVHumanGetName(BPVHuman *object) {
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

uint8_t BPVHumanGetAge(BPVHuman *object) {
    return object ? object->_age : 0;
}

void BPVHumanSetAge(BPVHuman *object, uint8_t age) {
    if (object) {
        object->_age = age;
    }
}

BPVHuman *BPVHumanGetPartner(BPVHuman *object) {
    return object ? object->_partner : NULL;
}

void BPVHumanSetWeakPartner(BPVHuman *human, BPVHuman *partner) {
        partner->_partner = human;
}

void BPVHumanSetStrongPartner (BPVHuman *human, BPVHuman *partner) {
    BPVObjectRetain(partner);
    BPVObjectRelease(human->_partner);
    
    human->_partner = partner;
}

void BPVHumanSetPartner(BPVHuman *object, BPVHuman *partner) {
    if (object && object->_partner != partner) {
        BPVHumanGetGender(object) == BPVHumanGenderMale
            ? BPVHumanSetStrongPartner(object, partner)
                : BPVHumanSetWeakPartner(object, partner);
    }
}

BPVHuman *BPVHumanGetFather(BPVHuman *object) {
    return object->_father;
}

BPVHuman *BPVHumanGetMother(BPVHuman *object) {
    return object->_mother;
}

//#define BPVHumanSetParent(human, field, value) __BPVHumanSetChildParent (human, &human->_##field, value)

void BPVHumanSetFather(BPVHuman *child, BPVHuman *father) {    //weak
    if (child->_father != father) {
        child->_father = NULL;
        child->_father = father;
    }
}

void BPVHumanSetMother(BPVHuman *child, BPVHuman *mother) {    //weak
    if (child->_mother != mother) {
        child->_mother = NULL;
        child->_mother = mother;
    }
}

void BPVObjectRetain(BPVHuman *object) {
    if (object) {
        object->_referenceCount++;
    }
}

void BPVObjectRelease(BPVHuman *object) {
    if (object) {
        object->_referenceCount -= 1;
        if (0 == object->_referenceCount) {
            __BPVHumanDeallocateObject(object);
        }
    }
}

#pragma mark -
#pragma mark Private Implementations

BPVHumanGender BPVHumanGetGender(BPVHuman *object) {
    return object->_gender;
}

#pragma mark -
#pragma mark Marriage

void BPVHumanDevorce(BPVHuman *object) {
    BPVHumanSetPartner(object, NULL);
}

bool BPVHumansCanGetMarried(BPVHuman *object, BPVHuman *partner) {
    return BPVHumanGetGender(object) != BPVHumanGetGender(partner);
}

void BPVHumanMarriage(BPVHuman *object, BPVHuman *partner) {
    if (object && partner) {
        if (BPVHumansCanGetMarried(object, partner)) {
            BPVHumanDevorce(object);
            BPVHumanDevorce(partner);

            BPVHumanSetPartner(object, partner);
            BPVHumanSetPartner(partner, object);
            
            printf("Congratulations! You get married");
        }
    }
}

#pragma mark -
#pragma mark Children

void BPVHumanRemoveAllChildren (BPVHuman *parent) {
    if (parent) {
        for (uint8_t index = 0; index < BPVHumanChildrenCount; index++) {
            if (BPVHumanGetChildAtIndex(parent, index)) {
                BPVHumanRemoveChildAtIndex(parent, index);
            }
        }
    }
}

void BPVHumanRemoveChildAtIndex (BPVHuman *parent, uint8_t index) {
    BPVHumanSetChildAtIndex(parent, index, NULL);
    BPVHumanSetFather(BPVHumanGetChildAtIndex(parent, index), NULL);
    BPVHumanSetMother(BPVHumanGetChildAtIndex(parent, index), NULL);
    
    BPVHumanRemoveChildFromParents(parent, index);
    
    BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
}

void BPVHumanSetChildAtIndex (BPVHuman *parent, uint8_t index, BPVHuman *child) {
    if (BPVHumanGetChildAtIndex(parent, index)) {
        BPVHumanAddChildAtIndex(parent, index);
    }
}

void BPVHumanAddChildAtIndex (BPVHuman *parent, uint8_t index) {
    BPVHuman *newborn = BPVHumanCreateObject();
    BPVHumanSetChildAtIndex(parent, parent->childrenCount, newborn);
    BPVHumanSetFather(newborn, parent);
    BPVHumanSetMother(newborn, BPVHumanGetPartner(parent));
}

BPVHuman *BPVHumanGetChildAtIndex (BPVHuman *parent, uint8_t index) {
    return parent->_children[index];
}

void BPVHumanRemoveChildFromParents (BPVHuman *parent, uint8_t index) {
    parent->_children[index] = NULL;
    BPVHumanGetPartner(parent)->_children[index] = NULL;
    parent->childrenCount -= 1;
    
}

uint8_t BPVHumanGetChildrenCount(BPVHuman *object) {
    return object->childrenCount;
}

uint8_t BPVHumanLastChild(BPVHuman *object) {
    uint8_t index = 0;
    while (index < BPVHumanChildrenCount) {
        if (object->_children[BPVHumanChildrenCount - index - 1]) {
            return (BPVHumanChildrenCount - index - 1);
        }
        index++;
    }
    return 0;
}



void BPVHumanReorganizeChildrensArray(BPVHuman *object) {
    if (object && BPVHumanGetChildrenCount(object)) {
        
        for (uint8_t index = 0; BPVHumanChildrenCount > index; index++) {
            if (BPVHumanGetChildAtIndex(object, index)) {
                continue;
            } else {
                
            }
        }
    }
}
