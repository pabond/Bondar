//
//  BPVLinkedListsEnumeratorTests.c
//  HWObjectC
//
//  Created by Bondar Pavel on 5/24/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include "BPVLinkedListsEnumeratorTests.h"
#include "BPVObject.h"
#include "BPVLinkedList.h"
#include "BPVLinkedListEnumerator.h"
#include "BPVLinkedListNode.h"
#include "BPVString.h"

void BPVRunLinkedListEnumeratorTest() {
    BPVLinkedList *list = BPVLinkedListCreate();
    
    static const uint8_t objectsCount = 10;
    
    for (uint8_t iterator = 0; iterator < objectsCount; iterator++) {
        BPVObject *object = BPVObjectCreateWithType(BPVObject);
        BPVLinkedListAddObject(list, object);
        
        BPVString *string = BPVStringCreate("string");
        BPVLinkedListAddObject(list, string);
        
        BPVObjectRelease(string);
        BPVObjectRelease(object);
    }
    
    if (1 == BPVObjectGetRetainCount(list)) {
        printf("Test 1 done\n");
    }
    
    if (objectsCount * 2 == BPVLinkedListGetCount(list)) {
        printf("Test 2 done\n");
    }
    
    BPVLinkedListEnumerator *enumerator = BPVLinkedListEnumeratorCreateFromList(list);
    
    if (2 == BPVObjectGetRetainCount(list) && 1 == BPVObjectGetRetainCount(enumerator)) {
        printf("Test 3 done\n");
    }
    
    uint8_t iterations = 0;
    BPVObject *object = BPVLinkedListEnumeratorGetNextObject(enumerator);
    while (BPVLinkedListEnumeratorValid(enumerator)) {
        iterations++;
        object = BPVLinkedListEnumeratorGetNextObject(enumerator);
    }
    
    if (objectsCount * 2 == iterations) {
        printf("Test 4 done\n");
    }
    
    printf("Is enumerator valid %d\n", BPVLinkedListEnumeratorValid(enumerator));

    BPVObjectRelease(enumerator);
    BPVObjectRelease(list);
}
