//
//  BPVLinkedListTests.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/24/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVLinkedListPrivate.h"
#include "BPVLinkedList.h"
#include "BPVLinkedListTests.h"

void BPVRunLinkedListTest() {
    BPVLinkedListNodeContext *context = BPVLinkedListGetEmptyContext();
    printf("Size of context = %lu\n", sizeof(*context));
}