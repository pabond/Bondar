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

static const uint8_t BPVIndexNotFound = UINT8_MAX;

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
void BPVHumanDivorce(BPVHuman *object, BPVHuman *partner);

static
void BPVHumanSetChildAtIndex(BPVHuman *parent, uint8_t index, BPVHuman *child);

static
BPVHuman *BPVHumanGetChildAtIndex(BPVHuman *parent, uint8_t index);

static
void BPVHumanRemoveChildAtIndex(BPVHuman *parent, uint8_t index);

static
void BPVHumanRemoveChildFromParent(BPVHuman *parent, uint8_t index);

static
void BPVHumanAddChildAtIndex(BPVHuman *parent, uint8_t index);

static
uint8_t BPVHumanGetChildrenCount(BPVHuman *object);

static
uint8_t BPVHumanLastChildIndex(BPVHuman *object);

static
uint8_t BPVHumanNullChild(BPVHuman *object);

static
void BPVHumanReorganizeChildrensArray(BPVHuman *object);

static
uint8_t BPVHumanGetChildIndex(BPVHuman *parent, BPVHuman *child);

#pragma mark -
#pragma mark Public Implementations

BPVHuman *__BPVHumanCreateObject() {
    BPVHuman *result = calloc(1, sizeof(BPVHuman));
    result->_referenceCount = 1;
    
    return result;
}

void __BPVHumanDeallocateObject(BPVHuman *object) {
    BPVHumanSetName(object, NULL);
    BPVHumanSetFather(object, NULL);
    BPVHumanSetMother(object, NULL);
    if (object->_partner) {
        BPVHumanDivorce(object, object->_partner);
    }
    
    free(object);
}

char *BPVHumanGetName(BPVHuman *object) {
    return object ? object->_name : NULL;
}

void BPVHumanSetName(BPVHuman *object, char *name) {
    if (object && object->_name != name) {
        if (object->_name) {
            free(object->_name);
            object->_name = NULL;
        }
        
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
    if (human && human->_partner != partner) {
        human->_partner = partner;
    }
}

void BPVHumanSetStrongPartner(BPVHuman *human, BPVHuman *partner) {
    if (human && human->_partner != partner) {
        BPVObjectRetain(partner);
        BPVObjectRelease(human->_partner);
    
        human->_partner = partner;
    }
}

void BPVHumanSetPartner(BPVHuman *object, BPVHuman *partner) {
    if (object) {
        if (BPVHumanGetGender(object) == BPVHumanGenderMale) {
            BPVHumanSetStrongPartner(object, partner);
        } else {
            BPVHumanSetWeakPartner(object, partner);
        }
    }
}

BPVHuman *BPVHumanGetFather(BPVHuman *object) {
    return object ? object->_father : NULL;
}

BPVHuman *BPVHumanGetMother(BPVHuman *object) {
    return object ? object->_mother : NULL;
}

//#define BPVHumanSetParent(human, field, value) __BPVHumanSetChildParent (human, &human->_##field, value)

void BPVHumanSetFather(BPVHuman *child, BPVHuman *father) {    //weak
    if (child && child->_father != father) {
        child->_father = father;
    }
}

void BPVHumanSetMother(BPVHuman *child, BPVHuman *mother) {    //weak
    if (child && child->_mother != mother) {
        child->_mother = mother;
    }
}

void BPVHumanSetGender(BPVHuman *object, BPVHumanGender gender) {
    if (object) {
        object->_gender = gender;
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
        if (0 == BPVHumanGetReferenceCount(object)) {
            __BPVHumanDeallocateObject(object);
        } else if (1 == BPVHumanGetReferenceCount(object)) {
            printf("Object %s has reference count 1. Don't forget to delete", object->_name);
        }
    }
}

uint64_t BPVHumanGetReferenceCount(BPVHuman *object) {
    return object->_referenceCount;
}

#pragma mark -
#pragma mark Private Implementations

BPVHumanGender BPVHumanGetGender(BPVHuman *object) {
    return object->_gender;
}

#pragma mark -
#pragma mark Marriage

void BPVHumanDivorce(BPVHuman *object, BPVHuman *partner) {
    
    BPVHuman *strongPartner = BPVHumanGetGender(object) == BPVHumanGenderMale ? object : partner;
    BPVHuman *weakPartner = BPVHumanGetGender(partner) == BPVHumanGenderMale ? object : partner;
    
    BPVHumanSetPartner(weakPartner, NULL);
    BPVHumanSetPartner(strongPartner, NULL);
}

bool BPVHumansCanGetMarried(BPVHuman *object, BPVHuman *partner) {
    return BPVHumanGetGender(object) != BPVHumanGetGender(partner);
}

void BPVHumanMarriage(BPVHuman *object, BPVHuman *partner) {
    if (object && partner) {
        if (BPVHumansCanGetMarried(object, partner)) {
            BPVHumanDivorce(object, partner);

            BPVHumanSetPartner(object, partner);
            BPVHumanSetPartner(partner, object);
            
            printf("Congratulations! You get married");
        }
    }
}

#pragma mark -
#pragma mark Children

void BPVHumanRemoveAllChildren(BPVHuman *parent) {
    if (parent) {
        for (uint8_t index = 0; index < BPVHumanChildrenCount; index++) {
            if (BPVHumanGetChildAtIndex(parent, BPVHumanChildrenCount - index - 1)) {
                BPVHumanRemoveChildAtIndex(parent, index);
            }
        }
    }
}

void BPVHumanRemoveChildAtIndex(BPVHuman *parent, uint8_t index) {
    BPVHumanSetChildAtIndex(parent, index, NULL);
    BPVHumanSetFather(BPVHumanGetChildAtIndex(parent, index), NULL);
    BPVHumanSetMother(BPVHumanGetChildAtIndex(parent, index), NULL);
    
    BPVHumanRemoveChildFromParent(BPVHumanGetChildAtIndex(parent, index)->_father,
                                  BPVHumanGetChildIndex(BPVHumanGetChildAtIndex(parent, index)->_father,
                                                        parent->_children[index]));
    
    BPVHumanRemoveChildFromParent(BPVHumanGetChildAtIndex(parent, index)->_mother,
                                  BPVHumanGetChildIndex(BPVHumanGetChildAtIndex(parent, index)->_mother,
                                                        parent->_children[index]));
    
    BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
}

void BPVHumanSetChildAtIndex(BPVHuman *parent, uint8_t index, BPVHuman *child) {
    if (parent && parent->_children[index] != child) {
        BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
        
        parent->_children[index] = child;
        
        if (child) {
            BPVObjectRetain(child);
        }
    }
}

void BPVHumanAddChildAtIndex(BPVHuman *parent, uint8_t index) {
    BPVHuman *newborn = __BPVHumanCreateObject();
    BPVHumanSetChildAtIndex(parent, parent->childrenCount, newborn);
    if (parent->_partner) {
        BPVHumanSetChildAtIndex(parent->_partner, parent->_partner->childrenCount, newborn);
    }
    
    BPVHuman *strongParent = BPVHumanGetGender(parent) ? parent : BPVHumanGetPartner(parent);
    
    BPVHumanSetFather(newborn, strongParent);
    BPVHumanSetMother(newborn, BPVHumanGetPartner(strongParent));
}

BPVHuman *BPVHumanGetChildAtIndex(BPVHuman *parent, uint8_t index) {
    return parent ? parent->_children[index] : NULL;
}

uint8_t BPVHumanGetChildIndex(BPVHuman *parent, BPVHuman *child) {
    for (uint8_t index = 0; index < BPVHumanChildrenCount; index++) {
        if (parent->_children[index] == child) {
            return index;
        }
    }
    return BPVIndexNotFound;
}

void BPVHumanRemoveChildFromParent (BPVHuman *parent, uint8_t index) {
    parent->_children[index] = NULL;
    BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
    parent->childrenCount -= 1;
}

uint8_t BPVHumanGetChildrenCount(BPVHuman *object) {
    return object ? object->childrenCount : 0;
}

uint8_t BPVHumanLastChildIndex(BPVHuman *object) {
    return object && BPVHumanGetChildrenCount(object) ? BPVHumanGetChildrenCount(object) - 1 : 0;
}

uint8_t BPVHumanNullChild(BPVHuman *object) {
    uint8_t index = 0;
    while (index < BPVHumanChildrenCount) {
        if (!(object->_children[index])) {
            return index;
        }
        
        index++;
    }
    return BPVHumanChildrenCount;
}

void BPVHumanReorganizeChildrensArray(BPVHuman *object) {
    if (object && BPVHumanGetChildrenCount(object)) {
        uint8_t lastChildIndex = BPVHumanLastChildIndex(object);
        uint8_t nullChildrenArrayIndex = BPVHumanNullChild(object);
        if (lastChildIndex != BPVHumanChildrenCount
            && nullChildrenArrayIndex != BPVHumanChildrenCount
            && nullChildrenArrayIndex < lastChildIndex)
        {
            BPVHuman *lastChild = BPVHumanGetChildAtIndex(object, lastChildIndex);
            BPVHumanSetChildAtIndex(object, nullChildrenArrayIndex, lastChild);
            BPVHumanRemoveChildAtIndex(object, lastChildIndex);
        }
    }
}
