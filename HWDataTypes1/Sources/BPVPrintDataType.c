//
//  BPVPrintDataType.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVPrintDataType.h"

#include "BPVRangeOfNumber.h"

void BPVPrintInt(int intNumber) {
    printf("Integer number: %i\n", intNumber);
}

void BPVPrintFloat(float floatNumber) {
    printf("Float number: %f\n", floatNumber);
}

void BPVPrintChar(char character) {
    printf("Char: %c\n", character);
}

void BPVPrintString(char string[]) {
    printf("Sting: %s\n", string);
}

void BPVPrintBool(bool value) {
    printf("Bool value: %i\n", value);
}

void BPVPrinDataType() {
    BPVPrintInt(5);
    BPVPrintChar('&');
    BPVPrintFloat(3.55f);
    BPVPrintString("Hello, World");
}

void BPVPrintRangeOfNumber(int value1, int value2) {
    printf("%u\n", BPVRangeOfNumber(value1, value2));
}

void BPVPrint() {
    printf("\n");
}

void BPVPrintWithPuts() {
    puts("I like it");
}

void BPVPrintAllTypes(long long longLongVal, long longVal, int intVal, float floatVal,
                      double doubleVal, char charVal, short shortVal, unsigned int unsignedIntVal) {
    printf("All types are: long long: %lld, long: %ld, int: %i, float: %f, double: %f, char: %c, short: %i, unsigned: %u\n",
           longLongVal, longVal, intVal, floatVal, doubleVal, charVal, shortVal, unsignedIntVal);
}

void BPVPrintDataTypesMathTest() {
    long long longLongNumber = 44;
    long longNumber = 43;
    int intNumber = 3334;
    float floatNumber = 3.5f;
    short shortNumber = 3;
    double doubleNumber = 2.55;
    char charType = 'a';
    unsigned int unsignedIntNumber = 35;
    
    BPVPrintAllTypes (longLongNumber, longNumber, intNumber, floatNumber, doubleNumber,
                      charType, shortNumber, unsignedIntNumber);
    
    printf("%f\n", intNumber / floatNumber);
    printf("%f\n", floatNumber * intNumber);
    printf("%i\n", intNumber / unsignedIntNumber);
    printf("%i\n", unsignedIntNumber % intNumber);
    printf("%i\n", shortNumber + intNumber);
    printf("%c\n", intNumber);   // prints nothing
    
    
    //trash in variable without initialisation
    long long longLongVal;
    long longVal;
    int intVal;
    float floatVal;
    short shortVal;
    double doubleVal;
    char charVal;
    unsigned int unsignedIntVal;
    
    BPVPrintAllTypes (longLongVal, longVal, intVal, floatVal, doubleVal, charVal, shortVal, unsignedIntVal);
    
    intVal = 5;
    BPVPrintIncrement(intVal);
}

void BPVPrintIncrement(int value) {
    printf("Postfix increment: %i\n", value++); //do nothing. value + 1 - works
    printf("Prefix incremnt: %i\n", --value);
}

