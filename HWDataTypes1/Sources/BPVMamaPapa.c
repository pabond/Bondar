//
//  BPVMamaPapa.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVMamaPapa.h"

#include <stdio.h>

void BPVPrintMama() {
    printf("Mama");
}

void BPVPrintPapa() {
    printf("Papa");
}

BPVTypeToPrint BPVPrintType(int value) {
    if (0 == value % 3 || 0 == value % 5) {
        int printType = BPVCaseDoNothing;
        
        if (0 == value % 3) {
            printType = BPVCaseMama;
            BPVPrintMama();
        }
        
        if (0 == value % 5) {
            printType += BPVCasePapa;
            BPVPrintPapa();
        }
        
        printf("\n");
        printf("Type to print is %d\n", printType);
        return (BPVTypeToPrint)printType;
    }
    
    return BPVCaseDoNothing;
}



