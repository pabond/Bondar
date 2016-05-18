//
//  BPVString.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVString_h
#define BPVString_h

#include "BPVObject.h"

typedef struct BPVString BPVString;

struct BPVString {
    BPVObject _parentClass;
    
    void *_data;
    uint64_t _count;
};

extern
void __BPVStringDeallocate(void *object);

extern
BPVString* BPVStringCreate(char *string);

extern
char *BPVStringGetString(BPVString *object);

extern
void BPVStringSetString(BPVString *object, char *string);

extern
size_t BPVStringGetSize(char *string);

#endif /* BPVString_h */
