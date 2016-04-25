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
    BPVHuman *_parent1;
    BPVHuman *_parent2;
    uint64_t _referenceCount;
    uint8_t childrenCount;
};

#pragma mark -
#pragma mark Private Declarations

void BPVHumanMarriage(BPVHuman *partner1, BPVHuman *partner2);

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

void BPVHumanSetWeekPartner(BPVHuman *partner2, BPVHuman *partner1) {
    if (partner2 && partner2->_partner != partner1) {
        partner2->_partner = partner1;
    }
}


BPVHuman BPVHumanParent1(BPVHuman *object) {
    return *(object ? object->_parent1 : NULL);
}

BPVHuman BPVHumanParent2(BPVHuman *object) {
    return *(object ? object->_parent2 : NULL);
}

void BPVHumanSetParents(BPVHuman *object, BPVHuman *parent1, BPVHuman *parent2) {    //week
    if (object && object->_parent1 != parent1) {
        object->_parent1 = parent1;
        
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

void BPVHumanMarriage(BPVHuman *partner1, BPVHuman *partner2) {
    if (partner1 && partner2) {
        if (partner1->_gender == BPVHumanGenderMale && partner2->_gender == BPVHumanGenderFemale) {
            BPVHumanSetPartner(partner1, partner2);
            BPVHumanSetWeekPartner(partner2, partner1);
            printf("Congratulations! You get married");
        } else if (partner1->_gender == BPVHumanGenderFemale && partner2->_gender == BPVHumanGenderMale) {
            BPVHumanSetPartner(partner2, partner1);
            BPVHumanSetWeekPartner(partner1, partner2);
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

void BPVChildBirth(BPVHuman *parent1, BPVHuman *parent2) {
    BPVHuman *newborn = BPVHumanCreateObject();
    
    BPVHumanSetChild(parent1, newborn);
    BPVHumanSetChild(parent2, newborn);
    BPVHumanSetParents(newborn, parent1, parent2);
}