#ifndef COMMANDMAPPER_H
#define COMMANDMAPPER_H

#include <vector>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// перечисление команд
enum class Command {Attack = 'a',
                    ViewAbilities = 'v', 
                    SaveGame = 's', 
                    LoadGame = 'l', 
                    Exit = 'q',
                    Unknown = 'u'};

class CommandMapper{
private:
    std::unordered_map<char, Command> key_to_command;
    std::unordered_map<Command, char> command_to_key;
    // проверка дублирования команд и клавиш
    bool ValidateMapping(char key, Command command);

public:
    CommandMapper();

    // задает дефолтное управление
    void set_default_commands();

    // загружаем управление из файла
    void load_from_file(const std::string& filename);

    void check_full_mapping();

    Command string_to_command(const std::string& command_str);

    Command get_command(char key) const;

    // вывод всех доступных команд
    void print_available_commands() const;
};

#endif //COMMANDMAPPER_H