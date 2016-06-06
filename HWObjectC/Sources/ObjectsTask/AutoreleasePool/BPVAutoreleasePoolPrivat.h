//
//  BPVAutoreleasePoolPrivat.h
//  HWObjectC
//
//  Created by Bondar Pavel on 6/6/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVAutoreleasePoolPrivat_h
#define BPVAutoreleasePoolPrivat_h

#include "BPVArray.h"
#include "BPVAutoreleasingStack.h"

bool BPVAutoreleasePoolDeleteEmptySteks(BPVArray *accumulator, BPVAutoreleasingStack *stack, BPVAutoreleasingStack *nextStack);

#endif /* BPVAutoreleasePoolPrivat_h */
