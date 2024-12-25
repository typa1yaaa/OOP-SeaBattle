#include "Cell.h"

Cell::Cell() : cell_status(CellState::Unknown), ship(nullptr), index_segment(-1), ship_id(0) {
}

CellState Cell::GetStatus() const {
    return cell_status;
}

void Cell::SetStatus(CellState new_status) {
    cell_status = new_status;
}

void Cell::SetShip(Ship* new_ship) {
    ship = new_ship;
    //СДЕЛАТЬ ТУТ ШИП АЙДИ
    ship_id = new_ship->GetShipId();
}

Ship* Cell::GetShip() const {
    return ship;
}

void Cell::SetIndexSegment(int new_ind) {
    index_segment = new_ind;
}

int Cell::GetIndexSegment() const{
    return index_segment;
}

int Cell::GetShipId(){
    return ship_id;
}

void Cell::SetShipId(int new_shipid){
    ship_id = new_shipid;
}


Cell::~Cell() {
}

void Cell::UpdateCell(CellState newState, int shipId, int segmentIndex) {
    this->SetStatus(newState);        // Обновляем статус клетки
    this->SetShipId(shipId);
    this->SetIndexSegment(segmentIndex); // Обновляем индекс сегмента
}

// оператор вывода
std::ostream& operator<<(std::ostream& out, Cell& cell){
    out << "["
        << static_cast<int>(cell.GetStatus()) << " "//sellstate как число
        << cell.GetShipId() << " "
        << cell.GetIndexSegment() // сегмент корабля
        << "]";
    return out;
}

// оператор ввода
std::istream& operator>>(std::istream& in, Cell& cell){
    char bracket;
    int cellStateValue;
    int shipId;
    int indexSegment;

    // Считываем данные в формате [<cell_status> <ship_ptr> <index_segment>]
    in >> bracket >> cellStateValue >> shipId >> indexSegment >> bracket;

    // Устанавливаем считанные значения в объект
    cell.UpdateCell(static_cast<CellState>(cellStateValue), shipId, indexSegment);
    // cout << "индекс сегмент " << indexSegment << endl;
    return in;
}