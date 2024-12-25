#include "InputProcessor.h"

InputProcessor::InputProcessor(const std::string& new_filename){
    filename = new_filename; 
    // если у нас невозможно открыть файл
    if (!filename.empty()){
        mapper.load_from_file(filename);
    }else{
        std::cout << "The file is empty. Default commands will be used." << std::endl;
    }   
};

Command InputProcessor::get_command() {
    std::string user_input;  // Строка для ввода
    while (true) {
        try {
            // mapper.print_available_commands();  // Выводим доступные команды
            std::cout << "Enter command: ";
            std::cin >> user_input;
            // Если введенная строка не состоит из одного символа, выбрасываем исключение
            if (user_input.length() != 1) {
                throw std::invalid_argument("Invalid input. Please enter only a single character.");
            }
            char input = user_input[0];  // Извлекаем первый символ
            Command command = mapper.get_command(input);
            // Если команда не распознана, выбрасываем исключение
            if (command == Command::Unknown) {
                throw std::invalid_argument("The entered command is not recognized. Please enter a valid command.");
            }
            // Возвращаем команду, если она валидна
            return command;
        } catch (const std::invalid_argument& e) {
            // Обработка ошибки: выводим сообщение об ошибке и продолжаем запрашивать ввод
            std::cerr << e.what() << std::endl;
            mapper.print_available_commands();  // Выводим доступные команды
        }
    }
}
