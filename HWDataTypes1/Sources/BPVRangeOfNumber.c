//
//  BPVRangeOfNumber.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/7/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include "BPVRangeOfNumber.h"

#include <stdio.h>

unsigned int BPVRangeOfNumber(int signedMaxNumber, int signedMinNumber) {
    return signedMaxNumber - (signedMinNumber);
}