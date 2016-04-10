//
//  BPVPrintDataType.h
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVPrintDataType_h
#define BPVPrintDataType_h

#include <stdbool.h>

void BPVPrinDataType();
void BPVPrintInt(int intNumber);
void BPVPrintFloat(float floatNumber);
void BPVPrintChar(char character);
void BPVPrintString(char string[]);
void BPVPrintBool(bool value);
void BPVPrintWithPuts();
void BPVPrintDataTypesMathTest();
void BPVPrintAllTypes(long long longLongValue,
                      long longValue,
                      int intValue,
                      float floatValue,
                      double doubleValue,
                      char charValue,
                      short shortValue,
                      unsigned int unsignedIntValue);

void BPVPrintIncrement(int value);
void BPVPrintNumberRange(int value1, int value2);
void BPVPrintTypeSize();

#endif /* BPVPrintDataType_h */
