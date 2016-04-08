//
//  BPVArrayInit.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//
#include <stdio.h>

#include "BPVArrayInit.h"

#include "BPVMathFunctions.h"

#include "BPVPrintDataType.h"

void BPVArrayTest() {
    int myArray[] = {1, 2, 2, 3, 3, 5, 7, 9};
    int myArray2[7];
    myArray2[0] = 3;
    myArray2[1] = 5;
    myArray2[2] = 4;
    myArray2[3] = 7;
    myArray2[4] = 1;
    myArray2[5] = 2;
    myArray2[6] = 33;
    myArray2[7] = 22;
    int size = sizeof(myArray)/sizeof(0);
    BPVPrintInt(size);

    for(int element = 0; element < size; element++) {
    BPVPrintInt(myArray[element]);
    BPVPrintInt(myArray2[element]);
    }
    
    int element = 0;
    while(element < size) {
        BPVPrintInt(myArray[element]);
        BPVPrintInt(myArray2[element]);
        element += 1;
    }
    element = 0;
    do {
        BPVPrintInt(myArray[element]);
        BPVPrintInt(myArray2[element]);
        element += 1;
    } while(element < size);
    
    int myArray3[2];
    myArray3[0] = 3;
    
    for(element = 0; element < sizeof(myArray3)/sizeof(0); element++) {
        BPVPrintInt(myArray3[element]);                                //2nd element = 0;
    }
}
