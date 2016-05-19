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

#pragma mark -
#pragma mark Private Declarations

static
void BPVStringSetString(BPVString *object, char *string);

static
char *BPVStringCopy(char *string);

#pragma mark -
#pragma mark Public Implementations

void __BPVStringDeallocate(void *object) {
    BPVStringSetString(object, NULL);
    
    __BPVObjectDeallocate(object);
}

BPVString* BPVStringCreate(char *string) {
    BPVString *object = BPVObjectCreateWithType(BPVString);
    BPVStringSetString(object, string);
    
    return object;
}

char *BPVStringGetString(BPVString *object) {
    return object ? object->_data : NULL;
}

size_t BPVStringGetSize(char *string) {
    return string ? strlen(string) : 0;
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
            object->_data = BPVStringCopy(string);
        }
    }
}

char *BPVStringCopy(char *string) {
    return string ? strdup(string) : NULL;
}
