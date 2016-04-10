//
//  BPVArrayInit.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//
#include <stdio.h>

#include <string.h>

#include "BPVArrayInit.h"

#include "BPVMathFunctions.h"

#include "BPVPrintDataType.h"

#include "BPVLoopForArray.h"


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
    //BPVForLoop(myArray[size], size);
    
    for (int element = 0; element < size; element++) {
    BPVPrintInt(myArray[element]);
    BPVPrintInt(myArray2[element]);
    }
    
    int element = 0;
    while (element < size) {
        BPVPrintInt(myArray[element]);
        BPVPrintInt(myArray2[element]);
        element += 1;
    }
    
    element = 0;
    do {
        BPVPrintInt(myArray[element]);
        BPVPrintInt(myArray2[element]);
        element += 1;
    } while (element < size);
    
    int myArray3[2];
    myArray3[0] = 3;
    
    for (element = 0; element < sizeof(myArray3)/sizeof(0); element++) {
        BPVPrintInt(myArray3[element]);                                //2nd element = 0;
    }
}

void BPVStrings() {
    const char string1[] = {'H', 'e', 'l', 'l', 'o', '!'};
    const char string2[] = "My name is Paul";
    
    for (int symbol = 0; symbol < strlen(string1); symbol++) {
        printf("%c", string1[symbol]);
    }
    puts("");
    
    for (int symbol = 0; symbol < strlen(string2); symbol++) {
        printf("%c", string2[symbol]);
    }
    puts("");
}
