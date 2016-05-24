//
//  BPVRunApplication.c
//  HWMacros
//
//  Created by Bondar Pavel on 4/11/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVRunApplication.h"
#include "BPVArrayTests.h"
#include "BPVLinkedListsEnumeratorTests.h"

void BPVRunApplication() {
    BPVRunArrayTests();
    BPVRunLinkedListEnumeratorTest();
}