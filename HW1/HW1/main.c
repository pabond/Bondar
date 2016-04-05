//
//  main.c
//  HW1
//
//  Created by Bondar Pavel on 4/5/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>
//#include "ICPrint.h"

void ICPrintHelloWorld () {         // ICPrintHelloWorld after calling runs code inside scope or till "return;"
    printf("Hello, mama!\n");       //Easy to change output in function. Text changed in one please, output changed everyware
}

/*
void ICPrintHelloWorld () {
    printf("Hello, World!\n");
}

void ICPrintHelloWorld () {
    printf("Hello, World!\n");
}
 */

//  ICPrintHelloWorld ();       // out of function "main" scope and out of stack. "Conflicting types"


int main(int argc, const char * argv[]) {
    // return 0;
    printf("Hello, World!\n");
    // return 0;
    printf("Nice to meet you\n");
    // return 0;
    printf("My name is: ");
    // return 0;
    printf("Pasha\n");
    // return 0;
    
    ICPrintHelloWorld();      //Calls function ICPrintHelloW
    // return 0;
    ICPrintHelloWorld();      // can call function as much as we need
    // return 0;
    ICPrintHelloWorld();
    // return 0;
    ICPrintHelloWorld();
    return 0;            // return stops function impementation and go out from the function with return value with type of function or nothing if void function
    
    
//    ICPrintHelloWorld();    //Code after "return" will not run. "Return" ends the function
}

//  ICPrintHelloWorld();      // out of function "main" scope and out of stack. "Conflicting types"

/*
void ICPrintHelloWorld () {    // program not working, not comiling
printf("Hello, World!\n");
}
*/