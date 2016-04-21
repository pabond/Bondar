//
//  BPVMacrosTask.h
//  HWMacros
//
//  Created by Bondar Pavel on 4/12/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVMacrosTask_h
#define BPVMacrosTask_h

/*
Lecture 2
1. Создать макрос, который бы генерировал метод для вывода в консоль значения любого примитивного типа. У макроса должно быть 2 параметра: тип, спецификатор вывода. При препроцессинге макрос должен создавать метод output_type, где вместо type должен быть подставлен тип, который мы выводим данным сгенерированным методом. Создать второй макрос, который бы занимался вызовом сгенерированного первым макросом метода, на вход должен получать тип метода.
Требования:
- создать тестовые методы для проверки того, как работает генерация на всех примитивных типах.
 */

#define BPVPrintTypeValue(type, outputSpecifier) \
    void BPVOutput_##type(type value) { \
        printf(#type " value = %" #outputSpecifier "\n", value); \
    }

#define BPVPrintTypeWithMacros(type, value) \
    BPVOutput_##type(value)

void BPVPrintTypeUsingMacros();

#endif /* BPVMacrosTask_h */
