#include "Abilities.h"
#include "Field.h"  

DoubleDamage::DoubleDamage(Field& new_field){
    field = &new_field;

};
    
void DoubleDamage::UseAbilities() {
    cout << "DoubleDamage ability applied!" << endl;
    field->DoubleDamageFlag();  // Применяем флаг двойного урона
    cout << "Flag for double damage has been set on the field." << endl;
};//применение в последствии флаг - принимаем и в плеер 

std::string DoubleDamage::GetType() {
    return "DoubleDamage";
}

Scanner::Scanner(Field& new_field){
    field = &new_field;

};

void Scanner::UseAbilities() {
    bool isValidInput = false; // флаг для проверки корректности ввода
    while (!isValidInput) {
        Point coord;
        cout << "Input correct coordinate for scanner 2x2 territory: ";
        // Проверяем ввод пользователя
        if (!(cin >> coord.x >> coord.y)) {
            // Если ввод некорректный (например, строка вместо числа)
            cin.clear(); // сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем буфер ввода
            cout << "Invalid input. Please enter numeric coordinates." << endl;
            continue; // переходим к следующей итерации
        }
        coord.x--;
        coord.y--;
        try {
            // Проверка координат на корректность
            if (coord.x <= 0 || coord.y <= 0 || coord.x > (field->GetFieldSize() - 1) || coord.y > (field->GetFieldSize() - 1)) {
                throw ViolationScannerForField();
            }

            isValidInput = true; // Координаты корректны, устанавливаем флаг

            // Проверка области 2x2
            for (int y = coord.y - 1; y <= coord.y; y++) {
                for (int x = coord.x - 1; x <= coord.x; x++) {
                    if (field->GetAllCell()[y][x].GetStatus() == CellState::Ship) {
                        cout << "Ship detected in area 2x2!" << endl;
                        return;
                    }
                }
            }

            cout << "No ship in area 2x2." << endl;

        } catch (const ViolationScannerForField& e) {
            cout << e.what() << " Please enter the new correct x and y coordinates." << endl;
            isValidInput = false; // сбрасываем флаг для повторного ввода
        }
    }
};

std::string Scanner::GetType() {
    return "Scanner";
}

Bombing::Bombing(Field& new_field){
    field = &new_field;
    
};

void Bombing::UseAbilities() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, field->GetFieldSize() - 1);

    cout << "Bombing ability applied!" << endl;

    while (true) {
        int random_x = distrib(gen);
        int random_y = distrib(gen);

        if (field->GetAllCell()[random_y][random_x].GetStatus() == CellState::Ship) {
            field->AttackCell({random_x, random_y});
            break;
        }
    }
};

std::string Bombing::GetType() {
    return "Bombing";
};