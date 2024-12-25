#include "Field.h"
#include <limits>

Field::Field(int new_field_size){
    field_size = new_field_size;
    
    all_cells.resize(field_size, vector<Cell>(field_size));

    // // Инициализация всех клеток
    // for (int y = 0; y < field_size; y++) {
    //     for (int x = 0; x < field_size; x++) {
    //         all_cells[y][x].SetStatus(CellState::Unknown);
    //         all_cells[y][x].SetShip(nullptr);
    //         all_cells[y][x].SetIndexSegment(-1);
    //         all_cells[y][x].SetShipId(0);
    //     }
    // }
};

Field::Field(const Field& other) : field_size(other.field_size), all_cells(other.all_cells) {};

Field::Field(Field&& other) noexcept : field_size(other.field_size), all_cells(move(other.all_cells)) {
    other.field_size = 0;
};

Field& Field::operator=(const Field& other) {
    if (this == &other) return *this;
    field_size = other.field_size;
    all_cells = other.all_cells;
    return *this;
};

Field& Field::operator=(Field&& other) noexcept {
    if (this == &other) return *this;
    field_size = other.field_size;
    all_cells = move(other.all_cells);
    other.field_size = 0;
    return *this;
};

void Field::AddAllShips(ShipManager& manager, vector<Point>& all_coords, vector<Orientation>& all_orientation) {
    try{
        if (manager.GetAllShips().empty()) {
            throw NoShipManagerException();
        }

        if (all_orientation.empty()){
            throw MismatchOfValues();
        }

        if (manager.GetAllShips().size() != all_orientation.size()){
            throw MismatchOfValues();
        }

        for (size_t i = 0; i < manager.GetAllShips().size(); i++) {
            Ship& ship = manager.GetAllShips()[i]; // Получаем ссылку на оригинальный объект корабля
            this->AddShip(ship, all_coords[i], all_orientation[i]);
            
            // Убедимся, что статусы сегментов устанавливаются на Healthy после добавления
            for (int j = 0; j < ship.GetLength(); j++) {
                FieldSegment& segment = ship.GetSegmentState(j);
                segment.SetStatus(ConditionState::HealthyShipSegment);
            }
        }
    }catch (const NoShipManagerException& e) {
        std::cout << e.what() << " Please enter valid data for ship manager." << std::endl;
        //
    } catch (const MismatchOfValues& e){
        std::cout << e.what() << " Please ensure the sizes match." << std::endl;
        //
    }
};

bool Field::AddShip(Ship& ship, Point coord, Orientation ship_orientation) {
    
    if (this->CanPlaceShip(ship, coord, ship_orientation)){
        for (int i = 0; i < ship.GetLength(); i++){
            if (ship_orientation == Orientation::Horizontally){
                all_cells[coord.y][coord.x + i].SetStatus(CellState::Ship);
                all_cells[coord.y][coord.x + i].SetShip(&ship);
                all_cells[coord.y][coord.x + i].SetIndexSegment(i);
                // cout << "Ship added at (" << coord.x + i << ", " << coord.y << ") as segment " << i << endl;

            } else {
                all_cells[coord.y + i][coord.x].SetStatus(CellState::Ship);
                all_cells[coord.y + i][coord.x].SetShip(&ship);
                all_cells[coord.y + i][coord.x].SetIndexSegment(i);
                // cout << "Ship added at (" << coord.x << ", " << coord.y + i << ") as segment " << i << endl;

            }
        }

        // Убедимся, что все сегменты корабля здоровы
        for (int i = 0; i < ship.GetLength(); i++) {
            FieldSegment& segment = ship.GetSegmentState(i); 
            segment.SetStatus(ConditionState::HealthyShipSegment); 
        }

        return true; // корабль успешно размещен
    } else {
        return false; // не удалось разместить корабль
    }
}

bool Field::CanPlaceShip(Ship& ship, Point coord, Orientation ship_orientation) {
    int x = coord.x;
    int y = coord.y;

    // Проверка выхода за границы поля
    if ((ship_orientation == Orientation::Horizontally && y + ship.GetLength() > field_size) ||
        (ship_orientation == Orientation::Vertically && x + ship.GetLength() > field_size)) {
        return false; // Выход за границы
    }

    // Проверка на занятые клетки
    for (int i = 0; i < ship.GetLength(); i++) {
        int currentX = x + (ship_orientation == Orientation::Horizontally ? i : 0);
        int currentY = y + (ship_orientation == Orientation::Vertically ? i : 0);

        if (currentX < 0 || currentX >= field_size || currentY < 0 || currentY >= field_size) {
            return false; // Выход за пределы поля
        }

        // Проверка на уже размещенные корабли
        if (all_cells[currentY][currentX].GetStatus() == CellState::Ship) {
            return false; // Клетка уже занята другим кораблем
        }

        // Проверка соседних клеток на занятость (для обеспечения отступа 1 клетку вокруг)
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int adjX = currentX + dx;
                int adjY = currentY + dy;

                // Проверка только внутри поля
                if (adjX >= 0 && adjX < field_size && adjY >= 0 && adjY < field_size) {
                    if (all_cells[adjY][adjX].GetStatus() == CellState::Ship) {
                        return false; // Если в соседней клетке уже есть корабль
                    }
                }
            }
        }
    }

    return true; // Если все проверки прошли, возвращаем true
}

bool Field::CanPlaceAllShips(std::vector<Ship>& ships) {
    int total_ship_segments = 0;
    for (Ship& ship : ships) {
        total_ship_segments += ship.GetLength();
    }

    int free_cells = 0;
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size; x++) {
            if (all_cells[y][x].GetStatus() == CellState::Unknown) {
                free_cells++;
            }
        }
    }

    return free_cells >= total_ship_segments;
}

bool Field::AttackCell(Point coord) {
    int x = coord.x;
    int y = coord.y;

    if (x < 0 || y < 0 || x >= field_size || y >= field_size) {
        throw ViolationAttackForField();
    }
    if (all_cells[y][x].GetStatus() == CellState::Ship) {
        Ship* target_ship = all_cells[y][x].GetShip();
        if (target_ship == nullptr) {
            cout << "Error: No ship found in cell despite cell state being Ship." << endl;
        }

        int index_segment = all_cells[y][x].GetIndexSegment();
        FieldSegment& segment = target_ship->GetSegmentState(index_segment);
        if (segment.GetStatus() == ConditionState::HealthyShipSegment && flag_dd == 0){
            segment.SetStatus(ConditionState::DamagedShipSegment);
            cout << "The ship is hit, jupii!" << endl;

        }else if (segment.GetStatus() == ConditionState::HealthyShipSegment && flag_dd == 1){
            segment.SetStatus(ConditionState::DestroyedShipSegment);
            cout << "The ship has been destroyed!" << endl;

        }else if (segment.GetStatus() == ConditionState::DamagedShipSegment)  {
            segment.SetStatus(ConditionState::DestroyedShipSegment);
            cout << "The ship has been destroyed!" << endl;

        } else {
            cout << "This segment is already destroyed." << endl;
        }

        // проверяем, уничтожен ли корабль???
        if (target_ship->Shipwrecked()){
            //если уничтожен, то подаем тру значение
            flag_dd = 0;
            return true;
        }

    } else {
        cout << "You missed, try it next time :(" << endl;
        flag_dd = 0;
        all_cells[y][x].SetStatus(CellState::No_ship);
    }
    
    flag_dd = 0;

    return false;//корабль не уничтожен полностью
};

void Field::PrintField() {
    cout << "\n- The playing field -" << endl;
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size; x++) {
            int index_seg = all_cells[y][x].GetIndexSegment();
             
            // Проверка статуса клетки на Unknown
            if (all_cells[y][x].GetStatus() == CellState::Unknown || index_seg == -1) {
                cout << "~  ";

            }else if (all_cells[y][x].GetStatus() == CellState::Ship) {
                // cout << all_cells[y][x].GetShip() << " ";
                if (all_cells[y][x].GetShip() != nullptr) {
                    // Проверяем статус сегмента, если он существует
                    if (index_seg >= 0 && index_seg < all_cells[y][x].GetShip()->GetLength()) {
                        auto segment_status = all_cells[y][x].GetShip()->GetSegmentState(index_seg).GetStatus();
                        if (segment_status == ConditionState::HealthyShipSegment) {
                            cout << "2  "; // Отображаем здоровый сегмент
                        } else if (segment_status == ConditionState::DamagedShipSegment) {
                            cout << "1  "; // Отображаем поврежденный сегмент
                        } else if (segment_status == ConditionState::DestroyedShipSegment) {
                            cout << "x  "; // Отображаем уничтоженный сегмент
                        }
                    } 
                } else {
                    cout << "~ "; // Если указатель на корабль пустой
                }
            }
            // Если в клетке нет корабля
            else if (all_cells[y][x].GetStatus() == CellState::No_ship) {
                cout << "o  "; // Клетка пустая
            }
        }
        cout << endl;
    }
}

void Field::SetFieldSize(int new_fs){
    field_size = new_fs;
}

vector<vector<Cell>>& Field::GetAllCell(){
    return all_cells;
};

bool Field::IsEmpty(){
    int counter_ships = 0;
    for (int y = 0; y < field_size; y++){
        for (int x = 0; x < field_size; x++){
            if(all_cells[y][x].GetStatus() == CellState::Ship){
                // поле не пустое
                return false;
            }
        }
    }
    // если пройдены все клетки и поле пустое, то возвращаем тру
    return true;
}

int Field::GetFieldSize(){
    return field_size;
};

void Field::DoubleDamageFlag(){
    flag_dd = 1;
};

int Field::ReturnFlag(){
    return flag_dd;
}

void Field::UpdateField(){
    // Инициализация всех клеток
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size; x++) {
            all_cells[y][x].SetStatus(CellState::Unknown);
            all_cells[y][x].SetShip(nullptr);
            all_cells[y][x].SetIndexSegment(-1);
        }
    }
}

Field Field::Clone() {
    return Field(*this);
}

// оператор вывода
std::ostream& operator<<(std::ostream& out, Field& field){
    out << '{'
        << field.GetFieldSize() << " "// записали длину поля
        << field.ReturnFlag() << " "; // записали флаг дд
    for (int y = 0; y < field.GetFieldSize(); y++){
        for (int x = 0; x < field.GetFieldSize(); x++){
            out << field.GetAllCell()[y][x]; // записываем каждую клеточку
        }
    }
    out << '}';
    return out;
}



// оператор ввода
std::istream& operator>>(std::istream& in, Field& field) {
    char bracket;
    int field_size;
    int flag;

    // Проверка начальной скобки
    in >> bracket;
    // cout << " СКОБКА  "<< bracket << endl;
    if (bracket != '{') {
        throw std::runtime_error("Некорректный формат ввода: ожидалась '{'.");
    }


    // Считывание размера поля и флага
    in >> field_size >> flag;
    if (field_size <= 0) {
        throw std::runtime_error("Некорректный размер поля.");
    }

    // Установка размера поля
    field.SetFieldSize(field_size);
    field.all_cells.resize(field_size, std::vector<Cell>(field_size));

    // Установка флага двойного урона, если он есть
    if (flag) {
        field.DoubleDamageFlag();
    } else {
        field.flag_dd = 0;
    }

    // Считывание клеток поля
    for (int y = 0; y < field_size; ++y) {
        for (int x = 0; x < field_size; ++x) {
            Cell cell;
            in >> cell; // Используем оператор ввода для Cell

            // Обновляем клетку в поле
            field.all_cells[y][x] = std::move(cell);
        }
    }

    // Проверка закрывающей скобки
    in >> bracket;
    if (bracket != '}') {
        throw std::runtime_error("Некорректный формат ввода: ожидалась '}'.");
    }

    return in;
}
