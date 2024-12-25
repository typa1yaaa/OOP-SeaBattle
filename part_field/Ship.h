#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <vector>
#include "FieldSegment.h"

using namespace std;

class Ship {
private:
    int length;
    vector<FieldSegment> all_ship_segments;
    int ship_id;

public:
    Ship(int new_length = 1);

    int GetLength();

    FieldSegment& GetSegmentState(int index);

    void UpdateAllSegments(ConditionState new_cond);

    bool Shipwrecked();

    void SetLength(int new_lngth);

    int GetShipId();

    void SetShipId(int new_shipId);

    void SetSegmentState(int index, ConditionState new_fieldseg);

    // Конструктор копирования
    Ship(const Ship& other);

    // Оператор копирования
    Ship& operator=(const Ship& other);

    // Конструктор перемещения
    Ship(Ship&& other);

    // Оператор перемещения
    Ship& operator=(Ship&& other);

    friend std::ostream& operator<<(std::ostream& out, Ship& ship);
    friend std::istream& operator>>(std::istream& in, Ship& ship);

};

#endif // SHIP_H