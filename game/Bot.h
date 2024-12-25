#ifndef BOT_H
#define BOT_H

#include "Field.h"
#include "User.h"
#include <random>
#include <algorithm>
/// TODO: СДЕЛАТЬ НАСЛЕДИЕ ОТ ЮЗЕРА
class Bot{ 
private:
    std::shared_ptr<Field> field;
    std::shared_ptr<Field> enemy_field;
    std::shared_ptr<ShipManager> ship_manager;
    std::vector<Point> need_points;//нужные поинты
    std::vector<Point> forbidden_points;//ненужные поинты

public:
    //добавляем все приваты
    Bot(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemy_field, std::shared_ptr<ShipManager> new_ship_manager);
    // рандомная расстановка кораблей
    void RandomPlaceShips();
    // метод возврата поля
    Field& GetField();
    std::shared_ptr<Field> GetFieldPtr();
    // метод возврата вражеского поля
    Field& GetEnemyField();
    // атака клетки поля игрока - рандомим клетку для атаки 
    bool AttackOpponent();
    // метод возврата общего количества кораблей
    int GetCountShips();
    // рандомные точки
    Point GenerateRandomPoint(int field_size);
    Orientation GenerateRandomOrientation();
    ShipManager& GetShipManager();
    
    void SetFields(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemyfield);
    void SetShipManager(std::shared_ptr<ShipManager> shipmanager);
    friend std::ostream& operator<<(std::ostream& out, Bot& bot);
    friend std::istream& operator>>(std::istream& in, Bot& bot);

};

#endif //BOT_H