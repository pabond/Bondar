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
    
    if (0 == value % 15) {
        numberToPrint = BPVCaseMamaPapa;
    } else if (0 == value % 3) {
        numberToPrint = BPVCaseMama;
    } else if (0 == value % 5) {
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