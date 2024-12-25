#include "Bot.h"
//добавляем все приваты
Bot::Bot(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemy_field, std::shared_ptr<ShipManager> new_ship_manager) {
    if (!new_field || !new_enemy_field || !new_ship_manager) {
        throw std::invalid_argument("Invalid arguments passed to Bot constructor.");
    }

    field = new_field;
    enemy_field = new_enemy_field;
    ship_manager = new_ship_manager;

}

// рандомная расстановка кораблей
void Bot::RandomPlaceShips() {
    if (!field) {
        throw std::runtime_error("Field is not initialized.");
    }
    if (ship_manager->GetAllShips().empty()) {
        throw std::runtime_error("No ships available in ShipManager.");
    }
    
    // cout << field->GetFieldSize() << endl;
    

    int field_size = field->GetFieldSize();
    int couner_false_ships = 0;

    for (Ship &ship : ship_manager->GetAllShips()) {
        while (true) {
            // Генерация случайной ориентации
            Orientation orient = GenerateRandomOrientation();
            Point cur_point = GenerateRandomPoint(field_size);
            // Проверяем, можно ли поставить корабль
            if (field->AddShip(ship, cur_point, orient)) {
                // если можно - переходим к след кораблю
                break;
            }else{
                couner_false_ships++;
            }

            if (couner_false_ships > 100000){
                break;
            }
        }

    }
}
    
// метод возврата поля
Field& Bot::GetField(){
    return *field;
}

// метод возврата поля
std::shared_ptr<Field> Bot::GetFieldPtr(){
    return field;
}

// метод возврата вражеского поля
Field& Bot::GetEnemyField(){
    return *enemy_field;
}

// атака клетки поля игрока - рандомим клетку для атаки 
bool Bot::AttackOpponent() {
    Point attack_point;
    // Если нет точек для атаки, генерируем случайную точку
    if (need_points.empty()) {
        attack_point = GenerateRandomPoint(field->GetFieldSize() - 1);
        while (std::find(forbidden_points.begin(), forbidden_points.end(), attack_point) != forbidden_points.end()) {
            attack_point = GenerateRandomPoint(field->GetFieldSize() - 1);
        }
    } else {
        attack_point = need_points.back();
        need_points.pop_back();
    }

    if (enemy_field == nullptr) {
        std::cerr << "Enemy field is null!" << std::endl;
        return false;
    }

    // Атакуем клетку и обновляем поле пользователя
    bool destroy_enemyship = enemy_field->AttackCell(attack_point);

    return destroy_enemyship;
}

// метод возврата общего количества кораблей
int Bot::GetCountShips(){
    return ship_manager->GetAllShips().size();
};

// рандомные точки
Point Bot::GenerateRandomPoint(int field_size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, field_size - 1);
    return {dist(gen), dist(gen)};
}

Orientation Bot::GenerateRandomOrientation() {
    return (rand() % 2 == 0) ? Orientation::Horizontally : Orientation::Vertically;
}

ShipManager& Bot::GetShipManager(){
    return *ship_manager;
}

void Bot::SetFields(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemyfield){
    field = new_field;
    enemy_field = new_enemyfield;
}
void Bot::SetShipManager(std::shared_ptr<ShipManager> shipmanager){
    ship_manager = shipmanager;
}

std::ostream& operator<<(std::ostream& out, Bot& bot){
    out <<  bot.GetField() << '\n' << bot.GetEnemyField()<< '\n' << bot.GetShipManager();
    return out; 
}

std::istream& operator>>(std::istream& in, Bot& bot){
    std::string line;
    
    Field field(bot.GetField().GetFieldSize());
    Field enemy_field(bot.GetEnemyField().GetFieldSize());
    ShipManager man(bot.GetShipManager().count_ships, bot.GetShipManager().len_ships);

    in >> field ;
    in >> enemy_field;
    in >> man;

    auto shar_field = std::make_shared<Field>(field);
    auto shar_enemyfield = std::make_shared<Field>(enemy_field);
    auto shipmanager = std::make_shared<ShipManager>(man);

    bot.SetFields(shar_field, shar_enemyfield);
    bot.SetShipManager(shipmanager);
    return in;
}
