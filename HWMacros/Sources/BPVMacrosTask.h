//
//  BPVMacrosTask.h
//  HWMacros
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVMacrosTask_h
#define BPVMacrosTask_h


#define BPVPrintTypeValue(type, outputSpecifier) \
    void BPVOutput_##type(type value) { \
        printf(#type " value = " #outputSpecifier "\n", value); \
}

//#define BPVPrintTypeWithDefine(type, velue) { \
//            BPVPrintTypeValue(type, value) 


//    }


#endif /* BPVMacrosTask_h */
