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
    BPVTypeDoNothing,
    BPVTypeMama,
    BPVTypePapa,
    BPVTypeMamaPapa
} BPVPrintType;

BPVPrintType BPVPrintTextType(int value);

#endif /* BPVMamaPapa_h */
