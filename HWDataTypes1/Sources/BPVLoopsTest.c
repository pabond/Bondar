//
//  BPVLoopsTest.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVLoopsTest.h"

#include "BPVPrintDataType.h"

void BPVPrintNumberRangeTimes(int printTimes, int smallerNumber, int biggerNumber) {
    if (printTimes > 20) {
        printTimes = 20;
    } else {
        printTimes = printTimes;
    }
    
    for (int iteration = 1; iteration < biggerNumber - smallerNumber + 1; iteration++) {
        int number = smallerNumber + iteration - 1;
        if (50 == number) {
        return;
        }

        if (0 == number % 3) {
            continue;
        } else {
            for (int printIteration = 0; printIteration < printTimes; printIteration++) {
                printf("%i_", number);
            }
     
            printf("\n");
        }
    }
    
    int iteration = 1;
    while (iteration < biggerNumber - smallerNumber + 1) {
        iteration++;
        int number = smallerNumber + iteration - 2;
        if (50 == number) {
            return;
        }
        
        if (0 == number % 3) {
            continue;
        } else {
            int printIteration = 0;
            while (printIteration < printTimes) {
                printIteration++;
                printf("%i_", number);
            }
            
            printf("\n");
        }
    }
    
    iteration = 1;
    do {
        iteration++;
        int number = smallerNumber + iteration - 2;
        if (50 == number) {
            return;
        }
        
        if (0 == number % 3) {
            continue;
        } else {
            int printIteration = 0;
             do {
                printIteration++;
                printf("%i_", number);
             } while (printIteration < printTimes);
            printf("\n");
        }
    } while (iteration < biggerNumber - smallerNumber + 1);
}

void BPVPrintNonNullTerminatedString(const char string[], unsigned long length) {
    for (unsigned long index = 0; index < length; index++) {
        printf("%c", string[index]);
    }
    
    printf("\n");
}

void BPVPrintNullTerminatedString(const char string[]) {
    BPVPrintNonNullTerminatedString(string, strlen(string));
}

void BPVPrintIntArray(int array[], int size) {
    for (int index = 0; index < size; index++) {
        BPVPrintInt(array[index]);
    }
    printf("\n");
}
