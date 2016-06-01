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
    BPVLinkedList *list = BPVLinkedListCreate();
    
    BPVObject *object = BPVObjectCreateWithType(BPVObject);
    BPVObject *object2 = BPVObjectCreateWithType(BPVObject);
    BPVLinkedListAddObject(list, object);
    BPVLinkedListAddObject(list, object2);
    
    BPVLinkedListGetObjectAfterObject(list, object);
}