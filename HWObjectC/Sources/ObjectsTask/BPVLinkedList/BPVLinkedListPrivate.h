//
//  BPVLinkedListPrivate.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/23/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedListPrivate_h
#define BPVLinkedListPrivate_h

typedef struct BPVLinkedList BPVLinkedList;

extern
void BPVLinkedListSetMutationsCount(BPVLinkedList *list, uint64_t count);

extern
uint64_t BPVLinkedListGetMutationsCount(BPVLinkedList *list);

#endif /* BPVLinkedListPrivate_h */
