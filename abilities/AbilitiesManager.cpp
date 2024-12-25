#include "AbilitiesManager.h"


AbilitiesManager::AbilitiesManager(Field& new_enemy_field)
    : enemy_field(new_enemy_field)
{
    //инициализируем генератор
    random_device generator;
    vector<shared_ptr<Abilities>> AbbilityList;
    AbbilityList.push_back(make_shared<DoubleDamage>(enemy_field));
    AbbilityList.push_back(make_shared<Scanner>(enemy_field));
    AbbilityList.push_back(make_shared<Bombing>(enemy_field));
    
    //перемещиваем способности
    shuffle(AbbilityList.begin(), AbbilityList.end(), generator);
    //добавляем способности в кучу
    for (auto& ability: AbbilityList){
        queue_abilities.push(ability);
    }
};

//использование способности
void AbilitiesManager::ApplicationOfAbilities(){
    try{
        if (queue_abilities.empty()){
            throw NoAbilitiesException();
        }
        // Выводим информацию о поле противника
        std::cout << "Using abilities on enemy field..." << std::endl;

        shared_ptr<Abilities> temp_abil = queue_abilities.front();
        queue_abilities.pop();
        temp_abil->UseAbilities();   
        std::cout << "Abilities have been applied to the enemy's field." << std::endl;     
    }catch(const NoAbilitiesException& e){
        cout << e.what() << "You can't use abilities." << endl;
    }    
};

//добавление случайной способности при уничтожении вражеского корабля
void AbilitiesManager::AddRandomAbility(){
    vector<shared_ptr<Abilities>> new_ability;
    new_ability.push_back(make_shared<DoubleDamage>(enemy_field));
    new_ability.push_back(make_shared<Scanner>(enemy_field));
    new_ability.push_back(make_shared<Bombing>(enemy_field));
    
    //перемещиваем способности
    shuffle(new_ability.begin(), new_ability.end(), generator);

    queue_abilities.push(new_ability.front());
};

//сколько способностей на данный момент доступно:
int AbilitiesManager::CountAbiliti(){
    return queue_abilities.size();
};

// метод, который выводит названия всех абилити
std::string AbilitiesManager::GetAbilitiesNames(){
    std::string names;
    std::queue<std::shared_ptr<Abilities>> temp_queue = queue_abilities;  // создаем копию очереди
    while (!temp_queue.empty()) {
        names += temp_queue.front()->GetType() + " ";  // получаем название способности
        temp_queue.pop();  // удаляем элемент из очереди
    }
    return names;
}

Field& AbilitiesManager::GetField(){
    return enemy_field;
}

void AbilitiesManager::SetField(Field& new_field){
    enemy_field = new_field;
}

void AbilitiesManager::ClearAbilities() {
    // Очистка очереди путем замены на новую пустую очередь
    std::queue<std::shared_ptr<Abilities>> empty_queue;
    std::swap(queue_abilities, empty_queue);
}

void AbilitiesManager::AddAbilities(std::string abil_name) {
    // Восстанавливаем способности по имени
    if (abil_name == "DoubleDamage") {
        queue_abilities.push(make_shared<DoubleDamage>(enemy_field));
    } else if (abil_name == "Scanner") {
        queue_abilities.push(make_shared<Scanner>(enemy_field));
    } else if (abil_name == "Bombing") {
        queue_abilities.push(make_shared<Bombing>(enemy_field));
    } else {
        std::cerr << "Unknown ability: " << abil_name << std::endl;
    }
}
AbilitiesManager AbilitiesManager::Clone(){
    return AbilitiesManager(*this);
}

// Конструктор копирования
AbilitiesManager::AbilitiesManager(const AbilitiesManager& other)
    : enemy_field(other.enemy_field) {  // Копируем поле
    // Копируем очередь способностей
    std::queue<std::shared_ptr<Abilities>> temp_queue = other.queue_abilities;
    while (!temp_queue.empty()) {
        queue_abilities.push(temp_queue.front());  // Копируем каждую способность в новую очередь
        temp_queue.pop();
    }
}

// Оператор присваивания копированием
AbilitiesManager& AbilitiesManager::operator=(const AbilitiesManager& other) {
    if (this == &other) return *this;  // Защита от самоприсваивания
    enemy_field = other.enemy_field;
    queue_abilities = other.queue_abilities;  // Копируем очередь
    return *this;
}

// Оператор присваивания перемещением
AbilitiesManager& AbilitiesManager::operator=(AbilitiesManager&& other) noexcept {
    if (this == &other) return *this;  // Защита от самоприсваивания
    enemy_field = std::move(other.enemy_field);
    queue_abilities = std::move(other.queue_abilities);
    
    // Очищаем очередь источника
    std::queue<std::shared_ptr<Abilities>> empty_queue;
    std::swap(other.queue_abilities, empty_queue);
    return *this;
}


// Конструктор перемещения
AbilitiesManager::AbilitiesManager(AbilitiesManager& other) noexcept
    : enemy_field((other.enemy_field)) {  // Перемещаем поле
    // Перемещаем очередь способностей
    queue_abilities = std::move(other.queue_abilities);

    // Очищаем очередь в объекте-источнике
    std::queue<std::shared_ptr<Abilities>> empty_queue;
    std::swap(other.queue_abilities, empty_queue);
}

// оператор вывода
std::ostream& operator<<(std::ostream& out, AbilitiesManager& abil_manager) {
    out << "["
        << abil_manager.CountAbiliti() << " "  // Количество способностей
        << abil_manager.GetField() << " ";      // Поле (или его состояние)

    // Получаем имена способностей для сохранения
    out << abil_manager.GetAbilitiesNames(); // Выводим каждое имя способности через пробел

    out << "]";
    return out;
}

// оператор ввода
std::istream& operator>>(std::istream& in, AbilitiesManager& abil_manager) {
    char bracket;
    int count_abil;
    Field field;
    // Считываем данные для поля и количества способностей
    in >> bracket >> count_abil >> field;
    abil_manager.SetField(field); // Устанавливаем новое поле
    // Очистим текущую очередь способностей
    abil_manager.ClearAbilities();
    // Считываем способности
    for (int i = 0; i < count_abil; ++i) {
        std::string abil_name;
        in >> abil_name;
        if (in.fail()) {
            std::cerr << "abil_name Ошибка при считывании способности №" << i + 1 << "\n";
            return in;
        }

        abil_manager.AddAbilities(abil_name);
    }
    in >> bracket >> bracket;
    return in;
}