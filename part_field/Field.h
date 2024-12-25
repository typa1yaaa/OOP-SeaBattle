#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include "Ship.h"
#include "Cell.h"
#include "Exceptions.h"
#include "ShipManager.h"
#include <unordered_map>
enum class Orientation {Horizontally = 0, 
                        Vertically = 1};

class Field {
private:
    int field_size;
    vector<vector<Cell>> all_cells;
    int flag_dd=0; //изначально дд = 0

public:
    Field(int new_field_size = 10);

    // Конструктор копирования
    Field(const Field& other);

    // Конструктор перемещения
    Field(Field&& other) noexcept;

    // Оператор присваивания
    Field& operator=(const Field& other);

    // Оператор перемещения
    Field& operator=(Field&& other) noexcept;

    void AddAllShips(ShipManager& manager, vector<Point>& all_coords, vector<Orientation>& all_orientation);

    bool AddShip(Ship& ship, Point coord, Orientation ship_orientation);

    bool CanPlaceShip(Ship& ship, Point coord, Orientation ship_orientation);

    bool CanPlaceAllShips(std::vector<Ship>& ships);
    
    void SetFieldSize(int new_fs);
    
    bool AttackCell(Point coord);
    
    void PrintField();

    vector<vector<Cell>>& GetAllCell();
    
    int GetFieldSize();

    void DoubleDamageFlag();

    int ReturnFlag();
    
    bool IsEmpty();
    
    void UpdateField();
    Field Clone();

    friend std::ostream& operator<<(std::ostream& out, Field& field);
    friend std::istream& operator>>(std::istream& in, Field& field);
};

#endif // Field_H