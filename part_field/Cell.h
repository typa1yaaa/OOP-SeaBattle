#ifndef CELL_H
#define CELL_H

#include "Ship.h"

#include <memory>
#include <iostream>  // Для потоковых операций
#include <sstream>
#include <iomanip> 

enum class CellState {Ship = 1, No_ship = 2, Unknown = 3};

class Cell {
private:
    CellState cell_status;
    Ship* ship;
    int index_segment;
    int ship_id;
public:
    Cell();
    CellState GetStatus() const;  
    void SetStatus(CellState new_status);
    void SetShip(Ship* new_ship);
    Ship* GetShip() const;  
    void SetIndexSegment(int new_ind);
    int GetIndexSegment() const; 
    int GetShipId();
    void SetShipId(int new_shipid);
    void UpdateCell(CellState newState, int shipId, int segmentIndex);
    ~Cell();  // Указатель на корабль будет освобожден в деструкторе
    friend std::ostream& operator<<(std::ostream& out, Cell& cell);
    friend std::istream& operator>>(std::istream& in, Cell& cell);
};

#endif // CELL_H
