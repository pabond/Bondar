//
//  main.c
//  HW1
//
//  Created by Bondar Pavel on 4/5/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>
#include "ICPrint.h"

//  ICPrintHelloWorld ();       // out of function "main" scope and out of stack. "Conflicting types"


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    printf("Nice to meet you\n");
    printf("My name is: ");
    printf("Pasha\n");
    
    ICPrintHelloWorld();      //Calls function ICPrintHelloW
    
    return 0;
    
//    ICPrintHelloWorld();    //Code after "return" will not run. "Return" ends the function
}

//  ICPrintHelloWorld();      // out of function "main" scope and out of stack. "Conflicting types"
