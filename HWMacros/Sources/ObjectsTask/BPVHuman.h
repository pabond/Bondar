//
//  BPVHuman.h
//  HWMacros
//
//  Created by Bondar Pavel on 4/21/16.
//  Copyright © 2016 Pavel Bondar. All rights reserved.
//

#ifndef BPVHuman_h
#define BPVHuman_h

#include <stdio.h>

const uint8_t BPVMaxHumanChildren = 20;

/*
1. Создать объектную структуру данных человек, имеющую поля имя, возраст, пол, количество детей, женат или нет, указатель на партнера, на родителей и на массив с детьми, где могло бы быть, максимум, 20 детей.
Требования:
- каждая из сущностей, будь то строка или массив, должны быть обернуты в свой объект, который, как минимум, умел бы выполнять подсчет ссылок и имел базовые аксессоры и тесты;
- реализовать подсчет ссылок, геттеры и сеттеры для полей;
- реализовать метод жениться, который бы устанавливал поле женат в true и указатель на партнера, с которым был брак;
- реализовать метод развестись, который бы устанавливал поле женат и указатель на партнера;
- реализовать метод произвести потомство, который бы создавал ребенка, устанавливал ему родителей, а у родителей добавлял бы ребенка;
- создать тесты на все поведение человека.
*/

typedef enum {
    BPVHumanGenderMale,
    BPVHumanGenderFemale
} BPVHumanGender;

typedef struct BPVHuman BPVHuman;

struct BPVHuman {
    char *_name;
    uint8_t _age;
    uint8_t _children[BPVMaxHumanChildren];
    BPVHumanGender _gender;
    BPVHuman *partner;
            // кто тут родитель?
};

//methods
BPVHuman *BPVHumanCreateObject();
void _BPVHumanDeallocateObject(BPVHuman *object);

char BPVHumanName(BPVHuman *object);
void BPVHumanSetName(BPVHuman *object, char *name);

int BPVHumanAge(BPVHuman *object);
void BPVHumanSetAge(BPVHuman *object, char *age);

BPVHuman BPVHumanPartner(BPVHuman *object, BPVHuman *partner);
void BPVHumanSetPartner(BPVHuman *object, char *age);

#endif /* BPVHuman_h */
