#include "Game.h"

Game::Game(){
    std::cout << "Yo-ho-ho, welcome to the sea battle, young sailors!\nThis game will help show you who's the real pirate around here." << endl;
    std::cout << "First, enter the size of the sea field where the great battle will be fought:" << endl;
    int field_size;
    std::cin >> field_size;
    while (true){
    try {
        // Проверка размера поля
        if (field_size < 6 || field_size > 100) {
            throw InvalidFieldSize();
        }

        break; // Выходим из цикла при корректном вводе

    } catch (const InvalidFieldSize& e) {
        cout << e.what() << "Ошибка " << endl;
        std::cin.clear(); // Сбрасываем состояние ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
        cout << "Enter a new correct value (>6 or <100): " << endl;
        cin >> field_size;
    }}

    // создаем поле игрока и ботика
    auto user_field = std::make_shared<Field>(field_size);
    auto botik_field = std::make_shared<Field>(field_size);
    
    //делаем шип менеджер для игрока
    std::vector<int> all_ship_len;
    std::vector<int> all_ship_count;
    
    // потом генерим шип менеджер для бота исходя из длин кораблей
    std::cout << "Enter the length of the ship and their number (e.g. '3 2')" << std::endl;
    std::cout << "To finish input, enter '-1 -1'.\n";

    int length, count;
    while (true) {
        std::cout << "Enter length and count: ";

        // Проверяем ввод
        if (!(std::cin >> length >> count)) {
            std::cout << "Input error. Please enter two numbers separated by a space.\n";

            // Очищаем поток ввода от ошибок
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Проверяем команду завершения
        if (length == -1 && count == -1 ) {
            break;
        }

        // Проверяем корректность значений
        if (length < 1 || count < 0 || length >= 5 || count > field_size) {
            std::cout << "Error: ship length must be >= 1  and < 5 and count >= 0. Repeat the entry.\n";
            continue;
        }

        // Сохраняем корректные данные
        all_ship_len.push_back(length);
        all_ship_count.push_back(count);
    }

    // Очищаем поток ввода от остатка, чтобы предотвратить пропуски
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Создаем ShipManager с помощью std::make_shared
    auto user_shipmanager = std::make_shared<ShipManager>(all_ship_count, all_ship_len);
    auto botik_shipmanager = std::make_shared<ShipManager>(all_ship_count, all_ship_len);

    user = std::make_shared<User>(user_field, botik_field, user_shipmanager);
    botik = std::make_shared<Bot>(botik_field, user_field, botik_shipmanager);

    destroy_bot_ship = 0;
    destroy_user_ship = 0;

}

void Game::UpdateGame() {
    // Обнуляем количество уничтоженных кораблей у пользователя
    destroy_user_ship = 0;
    // Создаем новое поле для бота
    // auto new_botikfield = std::make_shared<Field>(user->GetField().GetFieldSize());
    botik->GetField().UpdateField();
    // Создаем новый менеджер кораблей
    std::vector<int> all_ships_length = {1, 2, 3, 4};
    std::vector<int> all_ships_count = {0, 0, 0, 0};

    auto all_ships = user->GetShipManager().GetAllShips();
    for (int i = 0; i<all_ships.size(); i++){
        // Извлекли длины кораблей
        auto len = all_ships[i].GetLength();
        all_ships_count[len-1]++;
        
    }
    auto new_ship_manager = std::make_shared<ShipManager>(all_ships_count, all_ships_length);
    // Обновляем состояние игрока-бота
    botik = std::make_shared<Bot>(botik->GetFieldPtr(), user->GetFieldPtr(), new_ship_manager);
    user->SetEnemyField(botik->GetFieldPtr());
    notify_observers();
}

void Game::StartGame(){
    std::cout << "The sea battle has begun! Have fun!" <<endl;
    // ЕСЛИ ПОЛЕ ЮЗЕРА ПУСТОЕ, ТО СТАВИМ КОРАБЛИ, ЕСЛИ НЕТ - скипаем этот шаг
    
    if (user->GetField().IsEmpty()){
        // для начала перед боем нужно расставить корабли, как вы хотите это сделать - рандомно или сами
        std::cout << "Let's set up your ships before the battle. Do you want to set them up in random order or by yourself?\nEnter “0” if you want automatic ship placement and “1” if you want to place your ships on the field yourself." << endl;
        while(true){
            try{
                int choise_placeship;
                std::cin >> choise_placeship;
                if (choise_placeship != 0 || choise_placeship !=1){
                    exception invalid_argument;
                } 
                if (choise_placeship == 0){
                    // если 0 - автоматически
                    // notify_observers();
                    user->RandomPlaceShips();  
                    break;
                }else if (choise_placeship == 1){
                    // если 1 - сам 
                    // notify_observers();
                    user->PlaceShips(); 
                    break;
                } // Выход из цикла при успешной расстановке
            } catch (const std::invalid_argument& e) {
            std::cout << "Error: you have entered incorrect values. Try again. " << endl;
            }      
        }
    }
    
    std::cout << "The ships have been successfully deployed!" << endl;
    // расставляем рандомно корабли для бота
    botik->RandomPlaceShips();
    // визуализация
    notify_observers();
}

void Game::AttackRound() {

    bool validInput = false;
    while (!validInput) {
        try {
            // Ход пользователя
            int count_abil = user->GetAbilCount();
            std::cout << "Your move. Do you want to use the ability? (You have " << count_abil << " abilities) y/n" << std::endl;

            char choice;
            std::cin >> choice;

            // Проверка корректности ввода
            if (choice != 'y' && choice != 'n') {
                throw std::invalid_argument("Invalid input. Please enter 'y' or 'n'.");
            }

            // Если ввод корректный
            validInput = true;

            // Использование способности
            if (choice == 'y') {
                if (count_abil > 0) {
                    user->UsingAbilities();
                    std::cout << "Ability applied successfully! Proceeding with the attack." << std::endl;
                } else {
                    std::cout << "You have no abilities left. Proceeding with the attack." << std::endl;
                }
            }

            // Выполнение атаки
            notify_observers();
            if (user->AttackOpponent()) {
                destroy_user_ship++;
                std::cout << "You destroyed an enemy ship!" << std::endl;
                // Проверка окончания игры
                if (botik->GetCountShips() == destroy_user_ship) {
                    EndGame(1); // Победа пользователя
                }
            }

            // Ход бота
            std::cout << "Bot's move. Execution of the attack." << std::endl;
            if (botik->AttackOpponent()) {
                destroy_bot_ship++;
                std::cout << "Bot destroyed your ship!" << std::endl;

                // Проверка окончания игры
                if (user->GetCountShips() == destroy_bot_ship) {
                    EndGame(0); // Победа бота
                }
            }

            notify_observers();

        } catch (const std::invalid_argument& e) {
            // Сообщение об ошибке выводится только один раз
            std::cout << "Error: " << e.what() << " Try again." << std::endl;
            continue;
        } catch (const std::exception& e) {
            // Обработка неожиданных ошибок
            std::cout << "Unexpected error: " << e.what() << std::endl;
            break;
        }
    }
}

void Game::EndGame(int win_flag) {
    // при завершении игры передаем флаг, какой из игроков победил - бот - 0 или юзер 1
    if (win_flag == 0) {
        std::cout << "Alas, the bot has defeated you. But do not despair, next time you will definitely win!" << std::endl;

        // Запрашиваем у пользователя, хочет ли он начать новую игру
        char choise;
        while (true) {
            try {
                std::cout << "Do you want to start a new game? y/n: ";
                std::cin >> choise;

                // Проверяем корректность ввода
                if (choise != 'y' && choise != 'n') {
                    throw std::invalid_argument("Invalid input. Please enter 'y' or 'n'.");
                }

                // Если ввод корректный, выходим из цикла
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << " Try again." << std::endl;
            }
        }

        // Если пользователь хочет продолжить, то запускаем игру заново
        if (choise == 'y') {
            this->StartGame();
        } else {
            std::cout << "I hope you enjoyed this game! We look forward to seeing you again! Have a nice day!" << std::endl;
            exit(0); // Успешно завершаем игру
        }
        
    } else {
        std::cout << "Congratulations, you've won!" << std::endl;
        // При победе начинаем новую игру, но сохраняем положение кораблей у пользователя
        // У бота обновляем корабли
        char choise;
        while (true) {
            try {
                std::cout << "Do you want to continue the game with your ships and an updated bot? y/n: ";
                std::cin >> choise;

                // Проверяем корректность ввода
                if (choise != 'y' && choise != 'n') {
                    throw std::invalid_argument("Invalid input. Please enter 'y' or 'n'.");
                }

                // Если ввод корректный, выходим из цикла
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << " Try again." << std::endl;
            }
        }

        // Если пользователь хочет продолжить со своими кораблями и новым ботом, то запускаем игру заново
        if (choise == 'y') {
            // Обновляем игру
            this->UpdateGame();
            // Запускаем игру
            this->StartGame();
        } else {
            std::cout << "I hope you enjoyed this game! We look forward to seeing you again! Have a nice day!" << std::endl;
            exit(0); // Успешно завершаем игру
        }
    }
}

int Game::RetDestroyUserShip(){
    return destroy_user_ship;
}

int Game::RetDestroyBotShip(){
    return destroy_bot_ship;
}

void Game::DrawFields() {
    int field_size = user->GetField().GetFieldSize();
    cout << "\n"<< string((field_size * 1.5 + 3), ' ') << "--- The playing fields ---" << endl;
    cout  <<"User's Field" << string((field_size+1) * 2, ' ') << "Enemy's Field" << endl;

    for (int y = 0; y < field_size; y++) {
        // Отрисовка строки поля пользователя
        for (int x = 0; x < field_size; x++) {

            auto& cell = user->GetField().GetAllCell()[y][x];
            int index_seg = user->GetField().GetAllCell()[y][x].GetIndexSegment();

            if (cell.GetStatus() == CellState::Unknown) {
                cout << "~  ";
            } else if (cell.GetStatus() == CellState::Ship) {
                Ship* ship = cell.GetShip();

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
        cout << "     ";

        // Отрисовка строки поля врага
        for (int x = 0; x < field_size; x++) {
            int index_seg = botik->GetField().GetAllCell()[y][x].GetIndexSegment();
            auto& cell = botik->GetField().GetAllCell()[y][x];
            
            if (cell.GetStatus() == CellState::Unknown) {
                cout << "~  ";
            } else if (cell.GetStatus() == CellState::Ship){
                Ship* ship = cell.GetShip();
                // cout << index_seg << endl;
                // cout << ship->GetLength() << endl;
                // cout << static_cast<int>(ship->GetSegmentState(index_seg).GetStatus()) << endl;
                // cout << static_cast<int>(cell.GetShip()->GetSegmentState(index_seg).GetStatus()) << endl;
                if (ship != nullptr){
                    if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::HealthyShipSegment){
                        cout << "2  "; // блокируем 
                    }else if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::DamagedShipSegment){
                        cout << "1  "; 
                    }else if (ship->GetSegmentState(index_seg).GetStatus() == ConditionState::DestroyedShipSegment){
                        cout << "x  ";
                    }else {
                        cout << (cell.GetShip()->GetSegmentState(index_seg)) << "  ";
                    }
                }
                
            } else if (cell.GetStatus() == CellState::No_ship) {
                cout << "o  ";
            }
        }

        cout << endl;
    }
}

User& Game::GetUser(){
    return *user;
}

void Game::SetUser(User& new_user){
    user = std::make_shared<User>(new_user);
}

Bot& Game::GetBot(){
    return *botik;
}

void Game::SetBot(Bot& new_bot){
    botik = std::make_shared<Bot>(new_bot);
}


//обновление дестрой шипов
void Game::SetDestrShips(int dest_user, int dest_bot){
    destroy_bot_ship = dest_bot;
    destroy_user_ship = dest_user;
}

// Сохранение игры
void Game::SaveGame(){
    game_state->SaveGame(user, botik, &destroy_user_ship, &destroy_user_ship);
    notify_observers();     
}

// Загрузка игры
void Game::LoadGame() {
    game_state->LoadGame(user, botik, &destroy_user_ship, &destroy_user_ship);
    notify_observers();    
}

// Оператор вывода
std::ostream& operator<<(std::ostream& out, Game& game) {
    out << game.RetDestroyUserShip() << '\n';
    out << game.RetDestroyBotShip() << '\n' ;
    out << game.GetUser(); // Предполагается, что для User уже реализован оператор вывода
    out << game.GetBot(); // Предполагается, что для Bot уже реализован оператор вывода

    return out;
}

// Оператор ввода
std::istream& operator>>(std::istream& in, Game& game) {
    int destroy_user_ship, destroy_bot_ship;
    
    // Вводим количество уничтоженных кораблей
    in >> destroy_user_ship;
    in >> destroy_bot_ship;
    game.SetDestrShips(destroy_user_ship, destroy_bot_ship);

    // Вводим объекты User и Bot
    in >> game.GetUser();  // Используем существующие объекты
    in >> game.GetBot();   // Используем существующие объекты

    return in;
}

