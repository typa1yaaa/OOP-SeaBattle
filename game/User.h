#ifndef USER_H
#define USER_H

#include "Field.h"
#include "AbilitiesManager.h"

class User{
private:
    std::shared_ptr<Field> field;
    std::shared_ptr<Field> enemy_field;
    std::shared_ptr<ShipManager> ship_manager;
    std::shared_ptr<AbilitiesManager> abilities_manager;

public:

    //добавляем все приваты
    User(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemy_field, std::shared_ptr<ShipManager> new_ship_manager);
    // расстановка кораблей, как захочет пользователь
    void PlaceShips();
    // рандомная расстановка кораблей
    void RandomPlaceShips();
    // метод возврата поля
    Field& GetField();
    // std::shared_ptr<Field> GetFieldPtr();
    // метод возврата вражеского поля
    Field& GetEnemyField();
    // использование абилки на вражеское поле
    void UsingAbilities();
    bool AttackOpponent();
    // метод возврата общего количества кораблей
    int GetCountShips();
    int GetAbilCount();
    // деструктор
    ~User() = default;
    //обновление поля врага
    void SetEnemyField(std::shared_ptr<Field> new_enemy_field);
    // рандомные точки
    Point GenerateRandomPoint(int field_size);
    Orientation GenerateRandomOrientation();
    ShipManager& GetShipManager();
    AbilitiesManager& GetAbilManager();
    void SetFields(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemyfield);
    void SetShipManager(std::shared_ptr<ShipManager> shipmanager);
    void SetAbilManager(std::shared_ptr<AbilitiesManager> new_abilmanager);
    
    std::shared_ptr<Field> GetFieldPtr();
    std::shared_ptr<Field> GetEnemyFieldPtr();
    std::shared_ptr<ShipManager> GetShipManagerPtr();
    std::shared_ptr<AbilitiesManager> GetAbilitiesManagerPtr();

    friend std::ostream& operator<<(std::ostream& out, User& user);
    friend std::istream& operator>>(std::istream& in, User& user);
};

#endif //USER_H