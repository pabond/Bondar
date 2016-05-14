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

const uint8_t BPVIndexNotFound = UINT8_MAX;

struct BPVHuman {
    BPVObject _parentClass;
    
    BPVHumanGender _gender;
    
    char *_name;
    uint8_t _age;
    
    BPVHuman *_partner;
    BPVHuman *_mother;
    BPVHuman *_father;
    
    BPVHuman *_children[BPVHumanChildrenCount];
    uint8_t _childrenCount;
};

#pragma mark -
#pragma mark Private Declarations

static
bool BPVHumansCanGetMarried(BPVHuman *partner1, BPVHuman *partner2);

static
void BPVHumanSetWeakPartner(BPVHuman *human, BPVHuman *partner);

static
void BPVHumanSetStrongPartner(BPVHuman *human, BPVHuman *partner);

static
BPVHuman *BPVHumanGetMalePartner(BPVHuman *human);

static
void BPVHumanChildSetNullParent(BPVHuman *parent, uint8_t index);

static
void BPVHumanSetChildAtIndex(BPVHuman *parent, uint8_t index, BPVHuman *child);

static
bool BPVHumanCanHaveMoreChildern(BPVHuman *human);

static
void BPVHumanReorderChildren(BPVHuman *object, uint8_t index);

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

BPVHuman *BPVHumanCreate() {
    return BPVObjectCreateWithType(BPVHuman);
}

char *BPVHumanGetName(BPVHuman *object) {
    return object ? object->_name : NULL;
}

void BPVHumanSetName(BPVHuman *object, char *name) {
    if (object && BPVHumanGetName(object) != name) {
        if (BPVHumanGetName(object)) {
            free(BPVHumanGetName(object));
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

BPVHumanGender BPVHumanGetGender(BPVHuman *object) {
    return object->_gender;
}

void BPVHumanSetGender(BPVHuman *object, BPVHumanGender gender) {
    if (object) {
        object->_gender = gender;
    }
}

#pragma mark -
#pragma mark Marriage

bool BPVHumanIsMaried(BPVHuman *human) {
    return human && BPVHumanGetPartner(human);
}

void BPVHumanDivorce(BPVHuman *object) {
    BPVHumanSetPartner(BPVHumanGetPartner(object), NULL);
    BPVHumanSetPartner(object, NULL);
}

void BPVHumansGetMarried(BPVHuman *object, BPVHuman *partner) {
    if (object && partner && BPVHumansCanGetMarried(object, partner)) {
        BPVHumanDivorce(object);
        BPVHumanDivorce(partner);
        
        BPVHumanSetPartner(object, partner);
        BPVHumanSetPartner(partner, object);
        
        printf("Congratulations! You get married");
    }
}

BPVHuman *BPVHumanGetPartner(BPVHuman *object) {
    return object ? object->_partner : NULL;
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

#pragma mark -
#pragma mark Children

BPVHuman *BPVHumanGetFather(BPVHuman *object) {
    return object ? object->_father : NULL;
}

void BPVHumanSetFather(BPVHuman *child, BPVHuman *father) {
    if (child && BPVHumanGetFather(child) != father) {
        child->_father = father;
    }
}

BPVHuman *BPVHumanGetMother(BPVHuman *object) {
    return object ? object->_mother : NULL;
}

void BPVHumanSetMother(BPVHuman *child, BPVHuman *mother) {
    if (child && BPVHumanGetMother(child) != mother) {
        child->_mother = mother;
    }
}

uint8_t BPVHumanGetChildrenCount(BPVHuman *object) {
    return object ? object->_childrenCount : 0;
}

void BPVHumanSetChildrenCount(BPVHuman *human, uint8_t value) {
    if (human) {
        human->_childrenCount = value;
    }
}

BPVHuman *BPVHumanGiveBirthToChild(BPVHuman *parent) {
    BPVHuman *newborn = NULL;
    
    if (parent
        && BPVHumanGetPartner(parent)
        && BPVHumanCanHaveMoreChildern(parent))
    {
        newborn = BPVHumanCreate();
        
        BPVHumanSetChildAtIndex(parent, BPVHumanGetChildrenCount(parent), newborn);
        BPVHumanSetChildAtIndex(BPVHumanGetPartner(parent), BPVHumanGetChildrenCount(BPVHumanGetPartner(parent)), newborn);
        
        BPVHuman *father = BPVHumanGetMalePartner(parent);
        
        BPVHumanSetFather(newborn, father);
        BPVHumanSetMother(newborn, BPVHumanGetPartner(father));
    }
    
    return newborn;
}

void BPVHumanRemoveChildAtIndex(BPVHuman *parent, uint8_t index) {
    BPVHumanSetChildAtIndex(parent, index, NULL);
    BPVHumanChildSetNullParent(parent, index);
    BPVHumanReorderChildren(parent, index);
}

BPVHuman *BPVHumanGetChildAtIndex(BPVHuman *parent, uint8_t index) {
    return parent ? parent->_children[index] : NULL;
}

uint8_t BPVHumanGetChildIndex(BPVHuman *parent, BPVHuman *child) {
    for (uint8_t index = 0; index < BPVHumanGetChildrenCount(parent); index++) {
        if (BPVHumanGetChildAtIndex(parent, index) == child) {
            return index;
        }
    }
    
    return BPVIndexNotFound;
}

#pragma mark -
#pragma mark Private Implementations

bool BPVHumansCanGetMarried(BPVHuman *object, BPVHuman *partner) {
    return BPVHumanGetGender(object) != BPVHumanGetGender(partner);
}

void BPVHumanSetWeakPartner(BPVHuman *human, BPVHuman *partner) {
    if (human && BPVHumanGetPartner(human) != partner) {
        human->_partner = partner;
    }
}

void BPVHumanSetStrongPartner(BPVHuman *human, BPVHuman *partner) {
    if (human && BPVHumanGetPartner(human) != partner) {
        BPVObjectRelease(BPVHumanGetPartner(human));
        
        human->_partner = BPVObjectRetain(partner);
    }
}

BPVHuman *BPVHumanGetMalePartner(BPVHuman *human) {
    return BPVHumanGenderMale == BPVHumanGetGender(human) ? human : BPVHumanGetPartner(human);
}

bool BPVHumanCanHaveMoreChildern(BPVHuman *human) {
    return BPVHumanChildrenCount != BPVHumanGetChildrenCount(human);
}

void BPVHumanChildSetNullParent(BPVHuman *parent, uint8_t index) {
    BPVHuman *child = BPVHumanGetChildAtIndex(parent, index);
    if (parent && BPVHumanGetMalePartner(parent)) {
        BPVHumanSetFather(child, NULL);
    } else {
        BPVHumanSetMother(child, NULL);
    }
}

void BPVHumanSetChildAtIndex(BPVHuman *parent, uint8_t index, BPVHuman *child) {
    if (parent && BPVHumanGetChildAtIndex(parent, index) != child) {
        BPVObjectRelease(BPVHumanGetChildAtIndex(parent, index));
        
        parent->_children[index] = BPVObjectRetain(child);
    }
}

void BPVHumanReorderChildren(BPVHuman *object, uint8_t index) {
    uint8_t lastChildIndex = BPVHumanGetChildrenCount(object) - 1;
    if (object && index < lastChildIndex) {
        BPVHuman *lastChild = BPVHumanGetChildAtIndex(object, lastChildIndex);
        BPVHumanSetChildAtIndex(object, index, lastChild);
        BPVHumanRemoveChildAtIndex(object, lastChildIndex);
    }
}

void BPVHumanRemoveAllChildren(BPVHuman *parent) {
    if (parent) {
        uint8_t count = BPVHumanGetChildrenCount(parent);
        for (uint8_t index = 0; index < count; index++) {
            if (BPVHumanGetChildAtIndex(parent, count - index - 1)) {
                BPVHumanRemoveChildAtIndex(parent, index);
            }
        }
    }
}
