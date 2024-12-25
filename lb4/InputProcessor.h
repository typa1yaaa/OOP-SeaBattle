#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <iostream>
#include <string>
#include "CommandMapper.h"

// класс обработки ввода
class InputProcessor{
private:
    std::string filename;
    CommandMapper mapper;
public:
    InputProcessor(const std::string& new_filename = "command.txt");

    Command get_command();
};

#endif //INPUTPROCESSOR_H