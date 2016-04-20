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


struct BPVTypesStructure {
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
    bool boolValue5;
    double doubleValue;
    bool boolValue6;
    short shortValue3;
};

typedef struct BPVTypesStructure typesStructure;

void BPVPrintStructureSize();
void BPVPrintOffsetofValue();


typedef struct {
    long long longLongValue;    //8
    double doubleValue;         //8
    const char *string;         //8
    int intValue;               //4
    float floatValue;           //4
    short shortValue1;          //2
    short shortValue2;          //2
    short shortValue3;          //2
    union {
        struct {
            bool boolValue1 : 1;
            bool boolValue2 : 1;
            bool boolValue3 : 1;
            bool boolValue4 : 1;
            bool boolValue5 : 1;
            bool boolValue6 : 1;
            } booleans;
        uint8_t bitfield : 1;
    };                           //1
                                        //expected size 40 bytes
} BPVSortedTypesStructure;

#endif /* BPVStructureTask_h */
