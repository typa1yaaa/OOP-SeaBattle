#include "GameState.h"


void GameState::LoadGame(std::shared_ptr<User> user, std::shared_ptr<Bot> bot, int* destroy_user_ship, int* destroy_bot_ship){
    // std::string filename_user = "saved/user_data.txt";
    // std::string filename_bot = "saved/bot_data.txt";
    
    //TODO: сделать проверку на пустой файл и не загружать если он пустой
    // Чтение объекта из файла через оператор ввода
    // Чтение данных из файлов
    std::ifstream ifs1("saved/user_data.txt");
    std::ifstream ifs2("saved/bot_data.txt");

    if (!ifs1 || !ifs2) {
        std::cerr << "Failed to open file for reading" << std::endl;
        return;
    }

    // Проверка на пустой файл
    if (ifs1.peek() == std::ifstream::traits_type::eof() || ifs2.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "File is empty or cannot be opened" << std::endl;
        return;
    }

    // Считываем данные для уничтоженных кораблей
    ifs1 >> *destroy_user_ship;
    ifs2 >> *destroy_bot_ship;

    // Загружаем данные для user и bot через их указатели
    ifs1 >> *user;  // Передаем указатель, чтобы работать с объектом напрямую
    ifs2 >> *bot;   // То же самое для bot

    std::cout << "User data loaded from file" << std::endl;
    std::cout << "Bot data loaded from file" << std::endl;
}

void GameState::SaveGame(std::shared_ptr<User> user, std::shared_ptr<Bot> bot, int* destroy_user_ship, int* destroy_bot_ship){
    // Имя файла
    // std::string filename_user = ;
    // std::string filename_bot = ;

    // Запись объекта в файл через оператор вывода
    std::ofstream ofs1("saved/user_data.txt");
    std::ofstream ofs2("saved/bot_data.txt");

    if (!ofs1 || !ofs2) {
        std::cerr << "Failed to open file for writing" << std::endl;
        return;
    }

    // Запись данных в файлы
    ofs1 << *destroy_user_ship << '\n';
    ofs2 << *destroy_bot_ship << '\n';
    
    ofs1 << *user;  // Записываем данные user в файл
    ofs2 << *bot;   // Записываем данные bot в файл

    std::cout << "User data saved to file: saved/user_data.txt" << std::endl;
    std::cout << "Bot data saved to file: saved/bot_data.txt" << std::endl;
}