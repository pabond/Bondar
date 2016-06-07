//
//  BPVLinkedListPrivate.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/23/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedListPrivate_h
#define BPVLinkedListPrivate_h

#include "BPVLinkedList.h"

typedef struct BPVLinkedListNodeObjectContext BPVLinkedListNodeObjectContext;

typedef struct {
    BPVLinkedListNodeObjectContext *objectContext;
    void *previousNode;
    void *node;
    void *object;
} BPVLinkedListNodeContext;

typedef bool (*BPVLinkedListComparisonFunction)(void *object, void *context);

struct BPVLinkedListNodeObjectContext {
    void *accumulator;
    BPVLinkedListComparisonFunction comparator;
};

extern
void BPVLinkedListSetMutationsCount(BPVLinkedList *list, uint64_t count);

extern
uint64_t BPVLinkedListGetMutationsCount(BPVLinkedList *list);

extern
void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head);

extern
BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list);

extern
BPVLinkedListNode *BPVLinkedListGetNodeWithContext(BPVLinkedList *list,
                                                       BPVLinkedListComparisonFunction comparator,
                                                       void *context);

extern
void *BPVLinkedListGetObjectWithContext(BPVLinkedList *list,
                                        BPVLinkedListComparisonFunction comparator,
                                        void *context);

extern
bool BPVNodeObjectBridgeFunction(void *object, void *context);

extern
bool BPVLinkedListAccumulateObjects(void *object, void *context);

extern
bool BPVLinkedListNodeContainsObject(void *node, void *context);

#endif /* BPVLinkedListPrivate_h */
