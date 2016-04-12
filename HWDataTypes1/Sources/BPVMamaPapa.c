//
//  BPVMamaPapa.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVMamaPapa.h"

#include <stdio.h>

typedef enum {
    BPVCaseMama = 3,
    BPVCasePapa = 5
} BPVNumberToPrint;

void BPVPrintMama() {
    printf("Mama");
}

void BPVPrintPapa() {
    printf("Papa");
}

void BPVConditionFunction(int value) {
    int numberToPrint = 0;
    
    if (0 == value % (BPVCasePapa * BPVCaseMama)) {
        numberToPrint = 1;
    } else if (0 == value % BPVCaseMama) {
        numberToPrint = BPVCaseMama;
    } else if (0 == value % BPVCasePapa) {
        numberToPrint = BPVCasePapa;
    }
    
    if (1 == numberToPrint
        || numberToPrint == BPVCaseMama
            || numberToPrint == BPVCasePapa)
    {
        if (numberToPrint == BPVCaseMama) {
            BPVPrintMama();
        } else if (numberToPrint == BPVCasePapa) {
            BPVPrintPapa();
        } else {
            BPVPrintMama();
            BPVPrintPapa();
        }
        printf("\n");
    }
}