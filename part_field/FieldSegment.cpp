#include "FieldSegment.h"

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
};

FieldSegment::FieldSegment(){
    segment_status = ConditionState::HealthyShipSegment;
};

ConditionState FieldSegment::GetStatus(){
    return segment_status;
};

void FieldSegment::SetStatus(ConditionState new_status){
    segment_status = new_status;
};

bool FieldSegment::AttackForSegment(int damage){
    // если корабль целый и дамаг = 1
    if (this->GetStatus() == ConditionState::HealthyShipSegment && damage == 1){
        this->SetStatus(ConditionState::DamagedShipSegment); // корабль подбит
        return true;
    }
    // если корабль подбитый и дамаг = 1
    if (this->GetStatus() == ConditionState::DamagedShipSegment && damage == 1){
        this->SetStatus(ConditionState::DestroyedShipSegment); // корабль разрушен
        return true;
    }
    return false; 
};


// оператор вывода
std::ostream& operator<<(std::ostream& out, FieldSegment& field_segment){
    out << "{"
        << static_cast<int>(field_segment.GetStatus()) //сегмент корабля
        << "}";
    return out;
}

// оператор ввода
std::istream& operator>>(std::istream& in, FieldSegment& field_segment){
    char bracket;
    int field__state;
    // считываем данные в формате {<field_state>}
    in >> bracket >> field__state >> bracket;
    // устанавливаем данные значения
    field_segment.SetStatus(static_cast<ConditionState>(field__state));
    return in;
}
