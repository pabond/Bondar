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

extern
void BPVLinkedListSetMutationsCount(BPVLinkedList *list, uint64_t count);

extern
uint64_t BPVLinkedListGetMutationsCount(BPVLinkedList *list);

extern
void BPVLinkedListSetHead(BPVLinkedList *list, BPVLinkedListNode *head);

extern
BPVLinkedListNode *BPVLinkedListGetHead(BPVLinkedList *list);

#endif /* BPVLinkedListPrivate_h */
