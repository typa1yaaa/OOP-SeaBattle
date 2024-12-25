#ifndef FIELDRENDERIND_H
#define FIELDRENDERIND_H

#include "User.h"
#include "Bot.h"

#include <iostream>

//класс отрисовки поля
class FieldRendering{
public:
    // метод для отрисовки полей
    void draw_fields(User& user, Bot& bot);
};

#endif //FIELDRENDERIND_H
