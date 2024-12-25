#include "Ship.h"
#include "Exceptions.h"
#include "random"

Ship::Ship(int new_length){
    if (new_length < 1 || new_length > 4) {
        return;
    }
    length = new_length;

    // генерим рандом айди
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1000000, 9999999);

    ship_id = dist(gen);

    all_ship_segments.resize(length);
    for (int i = 0; i < length; i++){
        all_ship_segments[i].SetStatus(ConditionState::HealthyShipSegment);
    }
};


// Конструктор копирования
Ship::Ship(const Ship& other) {
    // Копируем длину
    length = other.length;
    // Копируем ID корабля
    ship_id = other.ship_id;
    // Копируем все сегменты
    all_ship_segments = other.all_ship_segments;
}

// Оператор копирования
Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        // Освобождаем текущие ресурсы
        length = other.length;
        ship_id = other.ship_id;
        all_ship_segments = other.all_ship_segments; // Вектор копируется по умолчанию
    }
    return *this;
}

// Конструктор перемещения
Ship::Ship(Ship&& other)  {
    // Перемещаем данные
    length = other.length;
    ship_id = other.ship_id;
    all_ship_segments = std::move(other.all_ship_segments);

    // Очищаем исходный объект
    other.length = 0;
    other.ship_id = 0;
}

// Оператор перемещения
Ship& Ship::operator=(Ship&& other) {
    if (this != &other) {
        // Освобождаем старые ресурсы
        length = other.length;
        ship_id = other.ship_id;
        all_ship_segments = std::move(other.all_ship_segments);

        // Очищаем исходный объект
        other.length = 0;
        other.ship_id = 0;
    }
    return *this;
}

int Ship::GetLength(){
    return length;
};

// Геттер для ID корабля
int Ship::GetShipId() {
    return ship_id;
}

void Ship::SetLength(int new_lngth){
    length = new_lngth;
    all_ship_segments.resize(length);
    for (int i = 0; i < length; ++i) {
        all_ship_segments[i].SetStatus(ConditionState::HealthyShipSegment);
    }
};

FieldSegment& Ship::GetSegmentState(int index){
    return all_ship_segments.at(index);
};

void Ship::UpdateAllSegments(ConditionState new_cond){
    for (int i = 0; i <  all_ship_segments.size(); i++){
        // обновляем все сегменты корабля на новый
        all_ship_segments[i].SetStatus(new_cond);
    }
};

void Ship::SetShipId(int new_shipId){
    ship_id = new_shipId;
}

void Ship::SetSegmentState(int index, ConditionState new_fieldseg){
    all_ship_segments[index].SetStatus(new_fieldseg);
}


bool Ship::Shipwrecked(){
    int size_seg = all_ship_segments.size();
    int destroy_counter = 0;
    for (int i = 0; i < size_seg; i++){
        if (all_ship_segments[i].GetStatus() == ConditionState::DestroyedShipSegment){
            destroy_counter++;
        }
    }
    // если все сегменты корабля - уничтожены, то возврашаем тру, если нет - фолз
    if (destroy_counter == size_seg){
        return true;
    }else{
        return false;
    }
};
// оператор вывода 
std::ostream& operator<<(std::ostream& out, Ship& ship){
    out << "["
        << ship.GetLength() << " " //запишем длину корабля
        << ship.GetShipId() << " " // запишем айди корабля
        << "("; // начнем записывать все сегменты корабля
    for (int i=0; i<ship.GetLength(); i++){
        out << ship.all_ship_segments[i] << " "; // записываем все шип сегменты через пробел
    }
    out << ")";
    out << "]";
    return out;
};

std::istream& operator>>(std::istream& in, Ship& ship){
    char bracket;          // Для чтения символов скобок
    int length;            // Для хранения длины корабля
    int shipId;
    in >> bracket >> length >> shipId >> bracket;
    // cout << bracket << endl;
    ship.SetLength(length);
    ship.SetShipId(shipId);
    // Считываем сегменты, заключенные в фигурные скобки
    for (int i = 0; i < length; i++) {
        FieldSegment segment;
        in >> segment;  // Используем оператор ввода для FieldSegment
        ship.SetSegmentState(i, segment.GetStatus());  // Присваиваем считанный сегмент в корабль
    }
    in >> bracket >> bracket;
    // cout << bracket << endl;

    return in;
};
