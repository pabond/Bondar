//
//  BPVHuman.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/21/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "BPVHuman.h"
#include "BPVObject.h"

static const uint8_t BPVHumanChildrenCount = 20;

struct BPVHuman {
    BPVObject _parentClass;
    
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
void BPVHumanDivorce(BPVHuman *object);

static
void BPVHumanSetChildAtIndex(BPVHuman *parent, uint8_t index, BPVHuman *child);

static
BPVHuman *BPVHumanGetChildAtIndex(BPVHuman *parent, uint8_t index);

static
void BPVHumanRemoveChildAtIndex(BPVHuman *parent, uint8_t index);

static
void BPVHumanRemoveChildFromParent(BPVHuman *parent, uint8_t index);

static
void BPVHumanAddChild(BPVHuman *parent);

static
uint8_t BPVHumanGetChildrenCount(BPVHuman *object);

static
void BPVHumanReorganizeChildren(BPVHuman *object, uint8_t index);

static
uint8_t BPVHumanGetChildIndex(BPVHuman *parent, BPVHuman *child);

static
void BPVHumanRemoveAllChildren(BPVHuman *parent);

#pragma mark -
#pragma mark Public Implementations

void __BPVHumanDeallocate(void *object) {
    BPVHumanSetName(object, NULL);
    BPVHumanSetFather(object, NULL);
    BPVHumanSetMother(object, NULL);
    BPVHumanDivorce(object);
    BPVHumanRemoveAllChildren(object);
    
    __BPVObjectDeallocate(object);
}

BPVHuman *__BPVHumanCreate() {
    return BPVObjectCreateWithType(BPVHuman);
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
        BPVObjectRelease(human->_partner);
    
        human->_partner = BPVObjectRetain(partner);
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

#pragma mark -
#pragma mark Private Implementations

BPVHumanGender BPVHumanGetGender(BPVHuman *object) {
    return object->_gender;
}

#pragma mark -
#pragma mark Marriage

void BPVHumanDivorce(BPVHuman *object) {
    
    BPVHuman *partner = BPVHumanGetPartner(object);
    
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
            BPVHumanDivorce(object);

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
        for (uint8_t index = 0; index < BPVHumanGetChildrenCount(parent); index++) {
            if (BPVHumanGetChildAtIndex(parent, BPVHumanChildrenCount - index - 1)) {
                BPVHumanRemoveChildAtIndex(parent, index);
            }
        }
    }
}

void BPVHumanRemoveChildAtIndex(BPVHuman *parent, uint8_t index) {
    BPVHumanSetChildAtIndex(parent, index, NULL);
    
    if (BPVHumanGenderMale == BPVHumanGetGender(parent)) {
        BPVHumanSetFather(BPVHumanGetChildAtIndex(parent, index), NULL);
    } else {
        BPVHumanSetMother(BPVHumanGetChildAtIndex(parent, index), NULL);
    }
    
    BPVHumanRemoveChildFromParent(parent, index);
}

void BPVHumanSetChildAtIndex(BPVHuman *parent, uint8_t index, BPVHuman *child) {
    if (parent && parent->_children[index] != child) {
        BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
        
        parent->_children[index] = BPVObjectRetain(child);
    }
}

void BPVHumanAddChild(BPVHuman *parent) {
    BPVHuman *newborn = __BPVHumanCreate();
    BPVHumanSetChildAtIndex(parent, BPVHumanGetChildrenCount(parent), newborn);
    if (BPVHumanGetPartner(parent)) {
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
    for (uint8_t index = 0; index < BPVHumanGetChildrenCount(parent); index++) {
        if (parent->_children[index] == child) {
            return index;
        }
    }
    return BPVIndexNotFound;
}

void BPVHumanRemoveChildFromParent (BPVHuman *parent, uint8_t index) {
    BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
    parent->_children[index] = NULL;
    parent->childrenCount -= 1;
    BPVHumanReorganizeChildren(parent, index);
}

uint8_t BPVHumanGetChildrenCount(BPVHuman *object) {
    return object ? object->childrenCount : 0;
}

void BPVHumanReorganizeChildren(BPVHuman *object, uint8_t index) {
    uint8_t lastChildIndex = BPVHumanGetChildrenCount(object) - 1;
    if (object && index < lastChildIndex) {
            BPVHuman *lastChild = BPVHumanGetChildAtIndex(object, lastChildIndex);
            BPVHumanSetChildAtIndex(object, index, lastChild);
            BPVHumanRemoveChildAtIndex(object, lastChildIndex);
    }
}
