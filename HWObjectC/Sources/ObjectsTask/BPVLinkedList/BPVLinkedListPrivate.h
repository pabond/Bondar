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

typedef struct {
    void *previousNode;
    void *node;
    void *object;
} BPVLinkedListNodeContext;

typedef bool (*BPVLinkedListComparisonFunction)(BPVLinkedListNode *node, BPVLinkedListNodeContext *context);

extern
void BPVLinkedListSetMutationsCount(BPVLinkedList *list, uint64_t count);

extern
uint64_t BPVLinkedListGetMutationsCount(BPVLinkedList *list);

extern
void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head);

extern
BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list);

extern
void *BPVLinkedListCreateEmptyContext();

extern
BPVLinkedListNode *BPVLinkedListNodeGetNodeWithContext(BPVLinkedList *list,
                                                       BPVLinkedListComparisonFunction comparator,
                                                       BPVLinkedListNodeContext *context);

extern
bool BPVLinkedListNodeContainsObject(BPVLinkedListNode *node, BPVLinkedListNodeContext *context);

#endif /* BPVLinkedListPrivate_h */
