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

static const uint8_t BPVMaxHumanChildren = 20;

struct BPVHuman {
    uint64_t _referenceCount;
    BPVHumanGender _gender;
    
    char *_name;
    uint8_t _age;
    
    BPVHuman *_partner;
    BPVHuman *_mother;
    BPVHuman *_father;
    
    BPVHuman *_children[BPVMaxHumanChildren];
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
void BPVHumanSetChild(BPVHuman *parent, BPVHuman *child);

static
void BPVHumanAddChildeAtIndex (BPVHuman *parent, BPVHuman *child, uint8_t index);

static
void BPVChildBirth(BPVHuman *parent1);

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

void BPVHumanSetChild(BPVHuman *parent, BPVHuman *child) {
    if (parent) {
        BPVObjectRetain(child);
        BPVHumanAddChildeAtIndex(parent, child, parent->childrenCount);
    }
}

void BPVChildBirth(BPVHuman *parent1) {
    BPVHuman *newborn = BPVHumanCreateObject();
    
    BPVHumanSetChild(parent1, newborn);
    BPVHumanSetChild(parent1->_partner, newborn);
    BPVHumanSetFather(newborn, parent1);
    }

void BPVHumanRemoveAllChildren (BPVHuman *parent, uint8_t index) {

}

void BPVHumanRemoveChildrenAtIndex (BPVHuman *parent, uint8_t index) {}
void BPVHumanAddChildeAtIndex (BPVHuman *parent, BPVHuman *child, uint8_t index) {}
void BPVHumanSetChildIndex (BPVHuman *parent, uint8_t index) {}

BPVHuman *BPVHumanGetChildAtIndex (BPVHuman *parent, uint8_t index) {
    return parent->_children[index];
}

void BPVHumanRemoveFromParents (BPVHuman *parent, uint8_t index) {}
