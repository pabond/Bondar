//
//  BPVStructureTask.h
//  HWMacros
//
//  Created by Bondar Pavel on 4/18/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVStructureTask_h
#define BPVStructureTask_h

#include <stdbool.h>

#include <stdio.h>

#include <stddef.h>

typedef struct {
    bool boolValue1;
    int intValue;
    float floatValue;
    bool boolValue2;
    short shortValue1;
    bool boolValue3;
    const char *string;
    long long longLongValue;
    bool boolValue4;
    short shortValue2;
    bool boolVAlue5;
    double doubleValue;
    short shortValue3;
} BPVTypesStructure;

#pragma mark -
#pragma mark Functions for structures

void BPVPrintOffcetofValue() {
    printf("", );
}

#endif /* BPVStructureTask_h */
