#ifndef ABILITIESMANAGER_H
#define ABILITIESMANAGER_H

#include <memory>
#include <queue>
#include <random>
#include <algorithm>
#include "Abilities.h"

class AbilitiesManager{
private:
    queue<shared_ptr<Abilities>> queue_abilities;// очередь способностей
    default_random_engine generator; //генератор случайных чисед
    Field& enemy_field;
public:
    AbilitiesManager(Field& new_enemy_field);
    //использование способности
    void ApplicationOfAbilities();
    //добавление случайной способности при уничтожении вражеского корабля
    void AddRandomAbility();
    int CountAbiliti();
    // метод, который выводит названия всех абилити
    std::string GetAbilitiesNames();
    Field& GetField();
    void SetField(Field& new_field);
    void ClearAbilities();
    void AddAbilities(std::string abil_name);

    AbilitiesManager(const AbilitiesManager& other);
    AbilitiesManager(AbilitiesManager& other) noexcept;
    AbilitiesManager& operator=(AbilitiesManager&& other) noexcept;
    AbilitiesManager& operator=(const AbilitiesManager& other);

    AbilitiesManager Clone();
    // оператор вывода
    friend std::ostream& operator<<(std::ostream& out, AbilitiesManager& abil_manager); 
    // оператор ввода
    friend std::istream& operator>>(std::istream& in, AbilitiesManager& abil_manager);

};

#endif