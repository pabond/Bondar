//
//  BPVStringTest.c
//  HWDataTypes1
//
//  Created by Bondar Pavel on 4/10/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#include <stdio.h>

#include <string.h>

#include "BPVStringTest.h"

void BPVStrings() {
    const char string1[] = "Hello!";
    const char string2[] = "My name is Paul\0";
    
    for (int symbol = 0; symbol < strlen(string1); symbol++) {
        printf("%c", string1[symbol]);
    }
    
    puts("");
    
    for (int symbol = 0; symbol < strlen(string2); symbol++) {
        printf("%c", string2[symbol]);
    }
    
    puts("");
    
    for (int symbol = 0; symbol < sizeof(string1); symbol++) {
        if (string1[symbol] == '\0') {
            printf("%s - is null-terminated string. It's length is %lu, and size is %lu\n",
                   string1,
                   strlen(string1),
                   sizeof(string1));
            
            break;
        }
    }
        
    for (int symbol = 0; symbol < sizeof(string2); symbol++) {
        if (string2[symbol] == '\0') {
            printf("%s - is null-terminated string. It's length is %lu, and size is %lu\n",
                       string2,
                       strlen(string2),
                       sizeof(string2));
                
            break; //All strrings are null-terminated
        }
    }
    
    const char string3[7] = "I'm a student at IDAP college.";   //Prints only 7 symbols and \n not printing in this case
    const char string4[15] = "We learn C"; // Why prints twice
    puts(string3);
    puts(string4);
    
    const char string5[] = "String test \0 with double null-termination\0"; //
    printf ("%s\n", string5); // printf prints string only till '\0' character
    
    unsigned long charArraySize = strlen(string1) + 1;
    printf("String size %lu \n", charArraySize);
}
