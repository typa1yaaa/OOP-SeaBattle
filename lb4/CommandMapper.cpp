#include "CommandMapper.h"

bool CommandMapper::ValidateMapping(char key, Command command) {
    if (key == '\0') {
        std::cerr << "Error: Key cannot be null or empty." << std::endl;
        return false;
    }

    if (key_to_command.find(key) != key_to_command.end()) {
        return false;
    }

    if (command_to_key.find(command) != command_to_key.end()) {
        return false;
    }

    return true;
}

CommandMapper::CommandMapper() { 
    set_default_commands(); 
}

// задает дефолтное управление
void CommandMapper::set_default_commands(){
    key_to_command['a'] = Command::Attack;
    key_to_command['v'] = Command::ViewAbilities;
    key_to_command['s'] = Command::SaveGame;
    key_to_command['l'] = Command::LoadGame;
    key_to_command['q'] = Command::Exit;
    
    // Обновляем command_to_key
    for (const auto& [key, cmd] : key_to_command){
        command_to_key[cmd] = key;
    }
}

// загружаем управление из файла
void CommandMapper::load_from_file(const std::string& filename){
    std::ifstream file(filename);
    // если не можем загрузить/открыть файл, то просто пишем и выходим
    if (!file || !file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "The command file cannot be opened or is empty. The default commands are used." << std::endl;
        set_default_commands();
        return;
    }

    // иначе очищаем дефолт команды и ключи
    key_to_command.clear();
    command_to_key.clear();
    // и присваиваем ключи и комнады из файлика
    char key;
    std::string command_str;
    while (file >> key >> command_str){
        // преобразуем команду в тип Command
        Command command = string_to_command(command_str);
        // если значениe ок, то добавляем
        if (ValidateMapping(key, command)){
            key_to_command[key] = command;
            command_to_key[command] = key;
        }else{
            std::cerr << "Invalid mapping in file. Skipping: " << key << " -> " << command_str << std::endl;
            continue;
        }
        
    }
    check_full_mapping();
}

void CommandMapper::check_full_mapping() {
    std::vector<Command> all_commands = {Command::Attack, Command::ViewAbilities, Command::SaveGame,
                                            Command::LoadGame, Command::Exit};
    for (Command cmd : all_commands) {
        if (command_to_key.find(cmd) == command_to_key.end()) {
            std::cerr << "Warning: Command is missing a key binding!" << std::endl;
        }
    }
}

Command CommandMapper::string_to_command(const std::string& command_str){
    if (command_str == "Attack" || command_str == "attack") return Command::Attack;
    if (command_str == "ViewAbilities" || command_str == "viewabilities" || command_str == "view_abilities") return Command::ViewAbilities;
    if (command_str == "SaveGame" || command_str == "savegame" || command_str == "save_game") return Command::SaveGame;
    if (command_str == "LoadGame" || command_str == "loadgame" || command_str == "load_game") return Command::LoadGame;
    if (command_str == "Exit" || command_str == "exit") return Command::Exit;
    // если это какая-то неизвестная команда, то возвращаем неизвестность
    return Command::Unknown;
}

Command CommandMapper::get_command(char key) const{
    auto it = key_to_command.find(key);
    if (it != key_to_command.end()) {
        return it->second;
    }
    return Command::Unknown;
}

// вывод всех доступных команд
void CommandMapper::print_available_commands() const {
    std::cout << "Available commands from file\n";
    std::cout << "if the file is not loaded, the default commands will be displayed :)" << std::endl;
    for (const auto& [key, cmd] : key_to_command) {
        std::cout << "Key: " << key << " -> Command: ";
        switch (cmd) {
            case Command::Attack: std::cout << "Attack"; break;
            case Command::ViewAbilities: std::cout << "ViewAbilities"; break;
            case Command::SaveGame: std::cout << "SaveGame"; break;
            case Command::LoadGame: std::cout << "LoadGame"; break;
            case Command::Exit: std::cout << "Exit"; break;
            default: std::cout << "Unknown";
        }
        std::cout << std::endl;
    }
}