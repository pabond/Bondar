//
//  BPVString.h
//  HWObjectC
//
//  Created by Bondar Pavel on 5/14/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVString_h
#define BPVString_h

typedef struct BPVString BPVString;

extern
void __BPVStringDeallocate(void *object);

extern
BPVString* BVPStringCreate();

extern
char *BPVStringGetString(BPVString *object);

#endif /* BPVString_h */
