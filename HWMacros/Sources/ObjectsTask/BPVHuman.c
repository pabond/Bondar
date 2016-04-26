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

void BPVHumanMarriage(BPVHuman *partner1, BPVHuman *partner2);
BPVHumanGender BPVGetGender(BPVHuman *object);
bool BPVHumansCanGetMarriage(BPVHuman *partner1, BPVHuman *partner2);


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
    return object ? object->_age : 0;
}

void BPVHumanSetAge(BPVHuman *object, uint8_t age) {
    if (object) {
    object->_age = age;
    }
}

BPVHuman BPVHumanPartner(BPVHuman *object) {
    return *(object ? object->_partner : NULL);
}

void BPVHumanSetPartner(BPVHuman *object, BPVHuman *partner) {
    if (object && object->_partner != partner) {
        BPVObjectRetain(partner);
        BPVObjectRelease(object->_partner);
        
        object->_partner = partner;
    }
}

void BPVHumanSetWeakPartner(BPVHuman *partner2, BPVHuman *partner1) {
    if (partner2 && partner2->_partner != partner1) {
        partner2->_partner = partner1;
    }
}


BPVHuman BPVHumanParent1(BPVHuman *object) {
    return *(object ? object->_father : NULL);
}

BPVHuman BPVHumanParent2(BPVHuman *object) {
    return *(object ? object->_mother : NULL);
}

void BPVHumanSetParents(BPVHuman *child, BPVHuman *parent, BPVHuman *parent2) {    //weak
    if (child) {
        child->_mother = parent;
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

BPVHumanGender BPVGetGender(BPVHuman *object) {
    return BPVHumanGenderMale == object->_gender ? BPVHumanGenderMale : BPVHumanGenderFemale;
}

bool BPVHumansCanGetMarriage(BPVHuman *partner1, BPVHuman *partner2) {
    return BPVGetGender(partner1) == BPVGetGender(partner2) ? false : true;
}

void BPVHumanSetPartners(BPVHuman *partner1, BPVHuman *partner2) {
    
}

void BPVHumanMarriage(BPVHuman *partner1, BPVHuman *partner2) {
    if (partner1 && partner2) {
        if (BPVHumansCanGetMarriage(partner1, partner2)) {
            
        }
    }
    
    if (partner1 && partner2) {
        if (partner1->_gender == BPVHumanGenderMale && partner2->_gender == BPVHumanGenderFemale) {
            BPVHumanSetPartner(partner1, partner2);
            BPVHumanSetWeakPartner(partner2, partner1);
            printf("Congratulations! You get married");
        } else if (partner1->_gender == BPVHumanGenderFemale && partner2->_gender == BPVHumanGenderMale) {
            BPVHumanSetPartner(partner2, partner1);
            BPVHumanSetWeakPartner(partner1, partner2);
            printf("Congratulations! You get married");
        } else {
            printf("Sorry, we can't marry you");
        }
    }
}

void BPVHumanSetChild(BPVHuman *parent, BPVHuman *child) {
    if (parent) {
        BPVObjectRetain(child);
        
//        parent->_children = ;
    }

}

void BPVChildBirth(BPVHuman *parent1) {
    BPVHuman *newborn = BPVHumanCreateObject();
    
    BPVHumanSetChild(parent1, newborn);
    BPVHumanSetChild(parent1->_partner, newborn);
    BPVHumanSetParents(newborn, parent1, parent1->_partner);
    
    BPVObjectRelease(newborn);
}
