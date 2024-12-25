#include "User.h"
#include "AbilitiesManager.h"

//добавляем все приваты
User::User(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemy_field, std::shared_ptr<ShipManager> new_ship_manager) {
    if (!new_field || !new_enemy_field || !new_ship_manager) {
        throw std::invalid_argument("Invalid arguments passed to User constructor.");
    }

    // Присваиваем unique_ptr
    field = new_field;
    enemy_field = new_enemy_field;
    ship_manager = new_ship_manager;

    // Инициализируем abilities_manager
    abilities_manager = std::make_shared<AbilitiesManager>(*enemy_field);  // Теперь создаем abilities_manager через unique_ptr
    
}

// расстановка кораблей, как захочет пользователь
void User::PlaceShips() {
    while(true){
        try{
            if (!field->CanPlaceAllShips(ship_manager->GetAllShips())) {
                exception InvalidFieldSize;
            }
            break;   
        }catch(const InvalidFieldSize& e){
            std::cout << e.what() << endl;
            std::cout << "Input correct value size field: "; 
            int new_fs;
            std::cin >> new_fs;
            //обновим размер поля для игрока и бота
            field->SetFieldSize(new_fs);
            enemy_field->SetFieldSize(new_fs);
        }
    }

    std::vector<Point> coords;
    std::vector<Orientation> all_orient;
    int num_ships = ship_manager->GetAllShips().size();
    // cout << num_ships << endl;
        for (int i = 0; i < num_ships; i++) {
            Point cur_coord;
            Ship& ship = ship_manager->GetAllShips()[i]; // Работаем со ссылкой на корабль
            

            // Получение координат
            while (true) {
                try {
                    std::cout << "Please post the coordinates where you want to put the ship in the format “x y”: ";
                    std::cin >> cur_coord.x >> cur_coord.y;
                    cur_coord.x--;
                    cur_coord.y--;
                    if (cur_coord.x < 0 || cur_coord.y < 0 || cur_coord.x >= field->GetFieldSize() || cur_coord.y >= field->GetFieldSize()) {
                        throw InvalidPoint();
                    }
                    coords.emplace_back(cur_coord);
                    break;
                } catch (const InvalidPoint& e) {
                    cout << e.what() << endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            // Получение ориентации
            while (true) {
                try {
                    std::cout << "Enter the orientation (v/V for vertical, h/H for horizontal): ";
                    std::string input;
                    std::cin >> input;
                    if (input.size() != 1) {
                        throw std::invalid_argument("Invalid input. Please enter a single character.");
                    }
                    char cur_orient = input[0];
                    if (cur_orient == 'H' || cur_orient == 'h') {
                        all_orient.emplace_back(Orientation::Horizontally);
                    } else if (cur_orient == 'V' || cur_orient == 'v') {
                        all_orient.emplace_back(Orientation::Vertically);
                    } else {
                        throw std::invalid_argument("Invalid orientation. Please enter 'H' or 'V'.");
                    }
                    break;
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << " Try again." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            // Размещение корабля
            if (field->AddShip(ship, cur_coord, all_orient.back())) {
                std::cout << "Ship placed at " << cur_coord.x << ", " << cur_coord.y << " with length " << ship.GetLength() << std::endl;
                field->PrintField();
            } else {
                std::cout << "Invalid ship position. Try again." << std::endl;
                coords.pop_back(); // Удаляем последнюю координату
                all_orient.pop_back(); // Удаляем последнюю ориентацию
                i--; // Попробовать снова для того же корабля
            }
        }
    }

// рандомная расстановка кораблей
void User::RandomPlaceShips() {
    if (ship_manager->GetAllShips().size() == 0) {
        throw NoShipManagerException();
    }

    if (ship_manager->GetAllShips().empty()) {
        throw std::runtime_error("No ships available in ShipManager.");
    }
    
    int field_size = field->GetFieldSize();
    int couner_false_ships = 0;
    int stop_flag = 0;
    vector<Orientation> all_orient;
    for (Ship &ship : ship_manager->GetAllShips()) {
        while (true) {
            // Генерация случайной ориентации
            Orientation orient = GenerateRandomOrientation();
            Point cur_point = GenerateRandomPoint(field_size);

            // Проверяем, можно ли поставить корабль
            if (field->AddShip(ship, cur_point, orient)) {
                // если можно - переходим к след кораблю
                all_orient.push_back(orient);
                break;
            }else{
                couner_false_ships++;
            }

            if (couner_false_ships > 10000){
                stop_flag = 1;
                break;
            }
        }
    }
    if (stop_flag == 1){
        std::cout << "You've brought in too many ships. The maximum possible number of ships has been placed." << endl;
    }
}
    
// метод возврата поля
Field& User::GetField(){
    return *field;
}


// метод возврата вражеского поля
Field& User::GetEnemyField(){
    return *enemy_field;
}

// использование абилки на вражеское поле
void User::UsingAbilities(){
    abilities_manager->ApplicationOfAbilities();
}

bool User::AttackOpponent() {
    Point attack_point;
    std::cout << "Enter the coordinates for the attack (x y): ";
    
    // Получаем координаты с проверкой на валидность
    while (true) {
        std::cin >> attack_point.x >> attack_point.y;
        attack_point.x--; // Понижаем на 1, т.к. координаты от 1, а массивы начинаются с 0
        attack_point.y--;    
        // Проверка на корректность ввода (координаты должны быть в пределах поля)
        if (attack_point.x < 0 || attack_point.y < 0 || attack_point.x >= field->GetFieldSize() || attack_point.y >= field->GetFieldSize()) {
            std::cin.clear();  // сброс флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очищаем буфер ввода
            std::cout << "Invalid coordinates. Please enter valid values for x and y between 1 and " 
                    << field->GetFieldSize() << ": ";
        } else {
            
            break;
        }
    }

    // Проверяем, есть ли поле врага
    if (enemy_field != nullptr) {
        bool is_ship_destroyed = enemy_field->AttackCell(attack_point);  // Атака клетки
        
        // Если корабль уничтожен, добавляем случайную способность
        if (is_ship_destroyed) {
            // std::cout << "You destroyed an enemy ship!" << std::endl;
            abilities_manager->AddRandomAbility(); // Добавляем способность
            return true;  // Возвращаем true, если корабль уничтожен
        } else {
            return false;
        }
    }

    std::cout << "Enemy field is not available!" << std::endl;
    return false;  // Если поле противника не найдено
}

// метод возврата общего количества кораблей
int User::GetCountShips(){
    return ship_manager->GetAllShips().size();
};

ShipManager& User::GetShipManager(){
    return *ship_manager;
}

AbilitiesManager& User::GetAbilManager(){
    return *abilities_manager;
}

int User::GetAbilCount(){
    return abilities_manager->CountAbiliti();
}

void User::SetEnemyField(std::shared_ptr<Field> new_enemy_field){
    enemy_field = new_enemy_field;
}

// рандомные точки
Point User::GenerateRandomPoint(int field_size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, field_size - 1);
    return {dist(gen), dist(gen)};
}

Orientation User::GenerateRandomOrientation() {
    return (rand() % 2 == 0) ? Orientation::Horizontally : Orientation::Vertically;
}

std::shared_ptr<Field> User::GetFieldPtr() {
    return field;
}

std::shared_ptr<Field> User::GetEnemyFieldPtr() {
    return enemy_field;
}

std::shared_ptr<ShipManager> User::GetShipManagerPtr() {
    return ship_manager;
}

std::shared_ptr<AbilitiesManager> User::GetAbilitiesManagerPtr() {
    return abilities_manager;
}

void User::SetFields(std::shared_ptr<Field> new_field, std::shared_ptr<Field> new_enemyfield){
    field = new_field;
    enemy_field = new_enemyfield;
}

void User::SetShipManager(std::shared_ptr<ShipManager> shipmanager){
    ship_manager = shipmanager;
}

void User::SetAbilManager(std::shared_ptr<AbilitiesManager> new_abilmanager){
    abilities_manager = new_abilmanager;
}

std::ostream& operator<<(std::ostream& out, User& user){
// Выводим данные пользователя в формате:
    // field
    // enemy_field
    // ship_manager
    // abilities_manager
    out << user.GetField() <<'\n' << user.GetEnemyField()<<'\n' << user.GetShipManager() <<'\n'<< user.GetAbilManager();
    return out;
}

std::istream& operator>>(std::istream& in, User& user){
    std::string line;
    Field field(user.GetField().GetFieldSize());//КЛОН
    Field enemy_field(user.GetField().GetFieldSize());//КЛОН
    ShipManager man(user.GetShipManager().count_ships,user.GetShipManager().len_ships);//КЛОН
    in >> field; 
    in >> enemy_field;
    in >> man;
    AbilitiesManager abil_man(enemy_field);//КЛОН
    in >> abil_man;

    auto shar_field = std::make_shared<Field>(field);
    auto shar_enemyfield = std::make_shared<Field>(enemy_field);
    auto shipmanager = std::make_shared<ShipManager>(man);
    auto abilmanager = std::make_shared<AbilitiesManager>(abil_man);

    user.SetFields(shar_field, shar_enemyfield);
    user.SetShipManager(shipmanager);
    user.SetAbilManager(abilmanager);

    return in;
}