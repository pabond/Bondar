//
//  BPVConditionalStatementsTest.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/10/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVConditionalStatementsTest.h"

typedef enum {
    BPVCaseMama,
    BPVCasePapa,
    BPVCaseMamaPapa
} BPVNumberToPrint;

void BPVPrintMama() {
    printf("Mama");
}

void BPVPrintPapa() {
    puts("Papa");
}

void BPVConditionFunction(int value) {
    int numberToPrint = -1;
    
    if (value % 15 == 0) {
        numberToPrint = BPVCaseMamaPapa;
    } else if (value % 3  == 0) {
        numberToPrint = BPVCaseMama;
    } else if (value % 5 == 0) {
        numberToPrint = BPVCasePapa;
    }
    
    if (numberToPrint == BPVCaseMamaPapa) {
        BPVPrintMama();
        BPVPrintPapa();
    } else if (numberToPrint  == BPVCaseMama) {
        BPVPrintMama();
        puts("");
    } else if (numberToPrint  == BPVCasePapa) {
        BPVPrintPapa();
    }
}