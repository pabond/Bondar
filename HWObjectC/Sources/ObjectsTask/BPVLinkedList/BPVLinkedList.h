//
//  BPVLinkedList.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/20/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedList_h
#define BPVLinkedList_h

#include <stdbool.h>

#include "BPVObject.h"

typedef struct BPVLinkedListNode BPVLinkedListNode;
typedef struct BPVLinkedListEnumerator BPVLinkedListEnumerator;

typedef struct {
    BPVObject _parentClass;
    
    BPVLinkedListNode *_head;
    
    uint64_t _count;
    uint64_t _mutationsCount;
} BPVLinkedList;

extern
void __BPVLinkedListDeallocate(BPVLinkedList *list);

extern
BPVLinkedList *BPVLinkedListCreate();

extern
BPVLinkedListEnumerator *BPVLinkedListEnumeratorCreateFromList(BPVLinkedList *list);

extern
BPVObject *BPVLinkedListGetFirstObject(BPVLinkedList *list);

extern
void BPVLinkedListRemoveFirstObject(BPVLinkedList *list);

extern
BPVObject *BPVLinkedListGetNextObject(BPVLinkedList *list, BPVLinkedListNode *node);

extern
void *BPVLinkedListGetObjectBeforeObject(BPVLinkedList *list, void *object);

extern
void *BPVLinkedListGetObjectAfterObject(BPVLinkedList *list, void *object);

extern
bool BPVLinkedListIsEmpty(BPVLinkedList *list);

extern
void BPVLinkedListAddObject(BPVLinkedList *list, void *object);

extern
void BPVLinkedListRemoveObject(BPVLinkedList *list, void *object);

extern
void BPVLinkedListRemoveAllObjects(BPVLinkedList *list);

extern
bool BPVLinkedListContainsObject(BPVLinkedList *list, void *object);

extern
uint64_t BPVLinkedListGetCount(BPVLinkedList *list);

extern
BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list);

#endif /* BPVLinkedList_h */
