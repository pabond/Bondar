//
//  BPVStructureTask.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/18/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include <stddef.h>

#include "BPVStructureTask.h"

#pragma mark -
#pragma mark Functions for structures

void BPVPrintOffsetofValue() {
    printf("Offsetof boolValue1 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, boolValue1));
    printf("Offsetof boolValue2 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, boolValue2));
    printf("Offsetof boolValue3 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, boolValue3));
    printf("Offsetof boolValue4 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, boolValue4));
    printf("Offsetof boolValue5 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, boolValue5));
    printf("Offsetof boolValue6 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, boolValue6));
    printf("Offsetof shortValue1 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, shortValue1));
    printf("Offsetof shortValue2 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, shortValue2));
    printf("Offsetof shortValue3 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, shortValue3));
    printf("Offsetof intValue in BPVTypesStucture is %lu.\n", offsetof(typesStructure, intValue));
    printf("Offsetof floatValue1 in BPVTypesStucture is %lu.\n", offsetof(typesStructure, floatValue));
    printf("Offsetof string in BPVTypesStucture is %lu.\n", offsetof(typesStructure, string));
    printf("Offsetof longLongValue in BPVTypesStucture is %lu.\n", offsetof(typesStructure, longLongValue));
    printf("Offsetof doubleValue in BPVTypesStucture is %lu.\n", offsetof(typesStructure, doubleValue));
    
    BPVPrintStructureSize();
}

void BPVPrintStructureSize() {
    printf("Size of structure is: %lu\n", sizeof(typesStructure));
    printf("Size of structure is: %lu\n", sizeof(BPVSortedTypesStructure));
}
