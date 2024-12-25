#include "ShipManager.h"

ShipManager::ShipManager(const vector<int>& count_ship, const vector<int>& len_ship){
    if (count_ship.size() != len_ship.size()){
        throw invalid_argument("Vectors count_ships and len_ship must be of the same length.");
    }
    count_ships = count_ship;
    len_ships = len_ship;

    for (int i = 0; i < len_ship.size(); i++){
        for (int j = 0; j < count_ship[i]; j++){
            Ship new_ship(len_ship[i]);
            all_ships.push_back(new_ship);
        }
    }
};

vector<Ship>& ShipManager::GetAllShips() {
    return all_ships;
};

void ShipManager::SetAllShips(std::vector<Ship> new_allships){
    // Очищаем текущий список кораблей
    all_ships.clear();
    // Проходим по всем кораблям из нового вектора и добавляем их в текущий вектор
    for (auto& ship : new_allships) {
        all_ships.push_back(std::move(ship));  // Используем std::move для перемещения объекта
    }
}

Ship* ShipManager::SearchShipId(int shipId){
    for (int i = 0; i < all_ships.size(); i++){
        if (all_ships[i].GetShipId() == shipId){
            return &(all_ships[i]);
        }
    }
    return nullptr;
}

// Метод клонирования
ShipManager ShipManager::Clone() {
    return ShipManager(*this);
}

ShipManager::ShipManager(const ShipManager& other) {
    // Копируем все векторы
    this->count_ships = other.count_ships;
    this->len_ships = other.len_ships;

    // Копируем все корабли (глубокое копирование)
    for (const auto& ship : other.all_ships) {
        this->all_ships.push_back(ship); // Предполагается, что вектор кораблей содержит объекты типа Ship с правильным конструктором копирования
    }
}

ShipManager::ShipManager(ShipManager&& other) noexcept {
    // Перемещаем данные, вместо их копирования
    this->count_ships = std::move(other.count_ships);
    this->len_ships = std::move(other.len_ships);

    // Перемещаем все корабли
    this->all_ships = std::move(other.all_ships);

    // Обнуляем данные в исходном объекте
    other.count_ships.clear();
    other.len_ships.clear();
    other.all_ships.clear();
}


// оператор вывода 
std::ostream& operator<<(std::ostream& out, ShipManager& ship_manager){
    out << "[" << ship_manager.GetAllShips().size();
    for (int i=0; i<ship_manager.GetAllShips().size(); i++){
        out << ship_manager.GetAllShips()[i] << " "; // записали корабли через пробел
    }
    out << ']';
    return out;
};

// оператор ввода
std::istream& operator>>(std::istream& in, ShipManager& ship_manager){
    char bracket;
    int num_ships;
    in >> bracket;
    in >> num_ships;
    std::vector<Ship> new_allships;
    // Считываем корабли
    for (int i = 0; i < num_ships; i++) {
        Ship ship;
        in >> ship;
        new_allships.push_back(ship);
    }
    ship_manager.SetAllShips(new_allships);
    in >> bracket;
    return in;

};