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

extern const uint8_t BPVIndexNotFound;

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

#pragma mark -
#pragma mark Accessors Declarations

char *BPVHumanGetName(BPVHuman *object);
void BPVHumanSetName(BPVHuman *object, char *name);

uint8_t BPVHumanGetAge(BPVHuman *object);
void BPVHumanSetAge(BPVHuman *object, uint8_t age);

BPVHuman *BPVHumanGetPartner(BPVHuman *object);
void BPVHumanSetPartner(BPVHuman *object, BPVHuman *partner);

BPVHuman *BPVHumanGetFather(BPVHuman *object);
BPVHuman *BPVHumanGetMother(BPVHuman *object);
void BPVHumanSetFather(BPVHuman *child, BPVHuman *father);
void BPVHumanSetMother(BPVHuman *child, BPVHuman *father);

BPVHumanGender BPVHumanGetGender(BPVHuman *object);
void BPVHumanSetGender(BPVHuman *object, BPVHumanGender gender);

void BPVHumansGetMarried(BPVHuman *partner1, BPVHuman *partner2);
void BPVHumanDivorce(BPVHuman *object);

void BPVHumanGiveBirthToChild(BPVHuman *parent);
BPVHuman *BPVHumanGetChildAtIndex(BPVHuman *parent, uint8_t index);
uint8_t BPVHumanGetChildIndex(BPVHuman *parent, BPVHuman *child);
uint8_t BPVHumanGetChildrenCount(BPVHuman *object);
void BPVHumanRemoveChildAtIndex(BPVHuman *parent, uint8_t index);

#endif /* BPVHuman_h */
