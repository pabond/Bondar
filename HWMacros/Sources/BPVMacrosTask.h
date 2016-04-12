//
//  BPVMacrosTask.h
//  HWMacros
//
//  Created by Bondar Pavel on 4/11/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVMacrosTask_h
#define BPVMacrosTask_h

typedef enum {
    BPVInt,
    BPVFloat,
    BPVChar,
    BPVShort,
    BPVUnsigned,
    BPVDouble,
    BPVLong
} BPVPrimitiveType;

//#define BPVPrintTypeMacros (type, outputSpecifier) \
    void output_##type(type value) { \
    printf(#type " value = " #outputSpecifier "\n", value); \
}

#endif /* BPVMacrosTask_h */
