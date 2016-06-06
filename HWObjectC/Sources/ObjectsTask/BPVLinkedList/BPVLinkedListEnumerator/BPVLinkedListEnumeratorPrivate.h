//
//  BPVLinkedListEnumeratorPrivate.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/25/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVLinkedListEnumeratorPrivate_h
#define BPVLinkedListEnumeratorPrivate_h

typedef struct BPVLinkedListNode BPVLinkedListNode;
typedef struct BPVLinkedListEnumerator BPVLinkedListEnumerator;

extern
BPVLinkedListNode *BPVLinkedListEnumeratorGetNode(BPVLinkedListEnumerator *enumerator);

#endif /* BPVLinkedListEnumeratorPrivate_h */
