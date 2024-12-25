#ifndef ABILITIES_H
#define ABILITIES_H

#include "Field.h"
#include <random>

// Класс-родитель
class Abilities {
public:
    virtual void UseAbilities() = 0;
    virtual ~Abilities() = default;
    virtual std::string GetType() = 0;
};

// Классы-наследники
class DoubleDamage : public Abilities {
private:
    Field* field = nullptr; // Ссылка на поле игрока 
public:
    DoubleDamage(Field& new_field); // Только объявление
    void UseAbilities() override;
    std::string GetType() override;
};

class Scanner : public Abilities {
private:
    Field* field = nullptr;
public:
    Scanner(Field& new_field); // Только объявление
    void UseAbilities() override;
    std::string GetType() override;
};

class Bombing : public Abilities {
private:
    Field* field = nullptr;
public:
    Bombing(Field& new_field); // Только объявление
    void UseAbilities() override;
    std::string GetType() override;
};

#endif // ABILITIES_H
