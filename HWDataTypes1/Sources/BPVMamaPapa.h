//
//  BPVMamaPapa.h
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVMamaPapa_h
#define BPVMamaPapa_h

typedef enum {
    BPVCaseDoNothing,
    BPVCaseMama,
    BPVCasePapa
} BPVTypeToPrint;

BPVTypeToPrint BPVPrintType(int value);

#endif /* BPVMamaPapa_h */
