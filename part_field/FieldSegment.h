#ifndef FIELDSEGMENT_H
#define FIELDSEGMENT_H

#include <memory>
#include <fstream>
#include <vector>

class Point{
public:
    int x;
    int y;

    bool operator==(const Point& other) const;
};

enum class ConditionState {DestroyedShipSegment = 0, 
                           DamagedShipSegment = 1, 
                           HealthyShipSegment = 2};


class FieldSegment {
private:
    ConditionState segment_status;

public:
    FieldSegment();
    
    ConditionState GetStatus();

    void SetStatus(ConditionState new_status);

    bool AttackForSegment(int damage = 1); 
    
    // Оператор присваивания перемещением
    friend std::ostream& operator<<(std::ostream& out, FieldSegment& field_segment);
    friend std::istream& operator>>(std::istream& in, FieldSegment& field_segment);
    
};

#endif // FLIELDSEGMENT_H