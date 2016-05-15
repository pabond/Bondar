//
//  BPVString.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdlib>

#include "BPVObject.h"
#include "BPVString.h"

struct BPVString {
    
}


void BPVStringSetString(void *object, void field, char *string) {
    if (object && BPVHumanGetField(field) != string) {
        if (BPVHumanGetName(object)) {
            free(BPVHumanGetName(object));
            object->_name = NULL;
        }
        
        if (name) {
            object->_name = strdup(name);
        }
    }
}