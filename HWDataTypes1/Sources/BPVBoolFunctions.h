//
//  BPVBoolFunctions.h
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/8/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVBoolFunctions_h
#define BPVBoolFunctions_h

#include <stdbool.h>

/*
 true && true = true;
 true && false = false;
 false && true = false;
 false && false = false;
 true || true = true;
 true || false = true;
 false || true = true;
 false || false = false;
 */

void BPVBoolValue(bool value);
void BPVBoolMathOperations(int value1, int value2);

#endif /* BPVBoolFunctions_h */
