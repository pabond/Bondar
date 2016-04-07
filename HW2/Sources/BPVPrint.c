//
//  BPVPrint.c
//  HW2
//
//  Created by Bondar Pavel on 4/6/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVPrint.h"

void BPVPrintHelloWorld() {
    printf("Hello, World!\n");
}

void BPVPrintHelloParents() {
    BPVPrintHelloMama();
    BPVPrintHelloPapa();
}

void BPVPrintHelloMama() {
    printf("Hello, mama!\n");
}

void BPVPrintHelloPapa() {
    printf("Hello, papa!\n");
}