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

BPVPrintType BPVPrintTextType(int value) {
    BPVPrintType printType = BPVTypeDoNothing;
        
    if (0 == value % 3) {
        printType += BPVTypeMama;
        BPVPrintMama();
    }
        
    if (0 == value % 5) {
        printType += BPVTypePapa;
        BPVPrintPapa();
    }
    
    if (BPVTypeDoNothing != printType) {
        printf("\n");
    }
    
    return (BPVPrintType)printType;
}


