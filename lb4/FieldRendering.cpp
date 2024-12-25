#include "FieldRendering.h"

void FieldRendering::draw_fields(User& user, Bot& bot) {
    int field_size = user.GetField().GetFieldSize();
    cout << "\n"<< string((field_size * 1.5 + 3), ' ') << "--- The playing fields ---" << endl;
    cout  <<"    User's Field" << string((field_size+1) * 2, ' ') << "Enemy's Field" << endl;
    cout << "    ";
    for (int i=0; i < field_size; i++){
        cout << i + 1 << "  ";
    }
    
     // Отступ между полями
    cout << "     ";

    for (int i=0; i < field_size; i++){
        cout << i + 1 << "  ";
    }
    cout << "\n" << "   ";;
    for(int i=0; i < 6*field_size + 5; i++){
        cout << "-";
    }
    cout << "\n";

    for (int y = 0; y < field_size; y++) {
        cout << y+1 << " | ";

        // Отрисовка строки поля пользователя
        for (int x = 0; x < field_size; x++) {
            auto& cell = user.GetField().GetAllCell()[y][x];
            int index_seg = user.GetField().GetAllCell()[y][x].GetIndexSegment();

            if (cell.GetStatus() == CellState::Unknown) {
                cout << "~  ";
            } else if (cell.GetStatus() == CellState::Ship) {
                int id =  cell.GetShipId();
                Ship* ship = user.GetShipManager().SearchShipId(id);
                cell.SetShip(ship);
                if (ship != nullptr){
                    if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::HealthyShipSegment){
                        cout << "2  ";
                    }else if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::DamagedShipSegment){
                        cout << "1  "; 
                    }else if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::DestroyedShipSegment){
                        cout << "x  ";
                    }
                }
            } else if (cell.GetStatus() == CellState::No_ship) {
                cout << "o  ";
            }
        }

        // Отступ между полями
        cout << "  ";
        cout << y+1 << " | ";
        // Отрисовка строки поля врага
        for (int x = 0; x < field_size; x++) {
            int index_seg = bot.GetField().GetAllCell()[y][x].GetIndexSegment();
            auto& cell = bot.GetField().GetAllCell()[y][x];
            
            if (cell.GetStatus() == CellState::Unknown) {
                cout << "~  ";
            } else if (cell.GetStatus() == CellState::Ship){
                int id = cell.GetShipId();
                Ship* ship = bot.GetShipManager().SearchShipId(id);
                cell.SetShip(ship);
                if (ship != nullptr){
                    if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::HealthyShipSegment){
                        cout << "~  "; // блокируем 
                    }else if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::DamagedShipSegment){
                        cout << "1  "; 
                    }else if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::DestroyedShipSegment){
                        cout << "x  ";
                    }
                }
            } else if (cell.GetStatus() == CellState::No_ship) {
                cout << "o  ";
            }
        }
        cout << endl;
    }
}
